/*
 * iic1_device.c
 *
 *  Created on: Jun 15, 2022
 *      Author: yurib
 */

#include "iic1_device.h"

#define USE_TIMEOUT 1
#if (USE_TIMEOUT == 1)
#define DMA_SEND_TIMEOUT_TC_MS               5
#define I2C_SEND_TIMEOUT_TXE_MS              5
#define I2C_SEND_TIMEOUT_SB_MS               5
#define I2C_SEND_TIMEOUT_ADDR_MS             5
#endif /* USE_TIMEOUT */

/**
 * @brief I2C devices settings
 */
/* I2C SPEEDCLOCK define to max value: Fast Mode @400kHz */
#define I2C_SPEEDCLOCK                       400000
#define I2C_DUTYCYCLE                        LL_I2C_DUTYCYCLE_2

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
#if (USE_TIMEOUT == 1)
uint32_t Timeout = 0; /* Variable used for Timeout management */
#endif /* USE_TIMEOUT */

/**
 * @brief Variables related to MasterTransmit process
 */
__IO uint8_t ubMasterTransferComplete = 0U;

device_config_t i2c1_device = { &init_device, &deinit_device };
static void enable_device_clocks(void) {
	if (LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_DMA1) == false) {
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
	}
	if (LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_GPIOB) == false) {
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
	}

	/* Peripheral clock enable */
	if (LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_I2C1) == false) {
		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);
	}
}

static void enable_device_gpio(void) {
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin = LL_GPIO_PIN_8 | LL_GPIO_PIN_9;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_4;
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

static void enable_dma_nvic(void) {
	NVIC_SetPriority(DMA1_Stream0_IRQn,
			NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 5, 0));
	NVIC_EnableIRQ(DMA1_Stream0_IRQn);
	/* DMA1_Stream1_IRQn interrupt configuration */
	NVIC_SetPriority(DMA1_Stream1_IRQn,
			NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 5, 0));
	NVIC_EnableIRQ(DMA1_Stream1_IRQn);

	/* (3) Configure the DMA1 functional parameters */
	LL_DMA_SetChannelSelection(DMA1, LL_DMA_STREAM_5, LL_DMA_CHANNEL_1);

	LL_DMA_ConfigTransfer(DMA1, LL_DMA_STREAM_5,
	LL_DMA_DIRECTION_PERIPH_TO_MEMORY |
	LL_DMA_PRIORITY_HIGH |
	LL_DMA_MODE_NORMAL |
	LL_DMA_PERIPH_NOINCREMENT |
	LL_DMA_MEMORY_INCREMENT |
	LL_DMA_PDATAALIGN_BYTE |
	LL_DMA_MDATAALIGN_BYTE);
//	LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_5, ubNbDataToTransmit);
//	LL_DMA_ConfigAddresses(DMA1, LL_DMA_STREAM_5,
//			(uint32_t) LL_I2C_DMA_GetRegAddr(I2C1),
//			(uint32_t) &(aReceiveBuffer),
//			LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_STREAM_5));

	/* (4) Configure the DMA1_Channel1 functional parameters */

	LL_DMA_SetChannelSelection(DMA1, LL_DMA_STREAM_1, LL_DMA_CHANNEL_0);

	LL_DMA_ConfigTransfer(DMA1, LL_DMA_STREAM_1,
	LL_DMA_DIRECTION_MEMORY_TO_PERIPH |
	LL_DMA_PRIORITY_HIGH |
	LL_DMA_MODE_NORMAL |
	LL_DMA_PERIPH_NOINCREMENT |
	LL_DMA_MEMORY_INCREMENT |
	LL_DMA_PDATAALIGN_BYTE |
	LL_DMA_MDATAALIGN_BYTE);

	/* (4) Enable DMA interrupts complete/error */
//	LL_DMA_EnableIT_TC(DMA1, LL_DMA_STREAM_5);
//	LL_DMA_EnableIT_TE(DMA1, LL_DMA_STREAM_5);
	LL_DMA_EnableIT_TC(DMA1, LL_DMA_STREAM_1);
	LL_DMA_EnableIT_TE(DMA1, LL_DMA_STREAM_1);
}

static void enable_device_i2c() {
	LL_RCC_ClocksTypeDef rcc_clocks;
	/* Disable I2C1 prior modifying configuration registers */
	LL_I2C_Disable(I2C1);
	/* Retrieve Clock frequencies */
	LL_RCC_GetSystemClocksFreq(&rcc_clocks);

	/* Configure the SCL Clock Speed */
	LL_I2C_ConfigSpeed(I2C1, rcc_clocks.PCLK1_Frequency, I2C_SPEEDCLOCK,
	I2C_DUTYCYCLE);
	LL_I2C_SetMode(I2C1, LL_I2C_MODE_I2C);
	LL_I2C_SetDutyCycle(I2C1, LL_I2C_DUTYCYCLE_2);
	LL_I2C_SetOwnAddress1(I2C1, 0, LL_I2C_OWNADDRESS1_7BIT);
	LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_ACK);
	LL_I2C_SetOwnAddress2(I2C1, 0);
	LL_I2C_EnableDMAReq_TX(I2C1);
	LL_I2C_Enable(I2C1);
	/* (2) Enable I2C1 transfer event/error interrupts:
	 *  - Enable Events interrupts
	 *  - Enable Errors interrupts
	 */
//	LL_I2C_EnableIT_EVT(I2C1);
//	LL_I2C_EnableIT_ERR(I2C1);
}
uint8_t init_device(void) {

	uint8_t ret = 0U;

	enable_device_clocks();
	/**I2C1 GPIO Configuration
	 PB6   ------> I2C1_SCL
	 PB7   ------> I2C1_SDA
	 */
	enable_device_gpio();
	/* I2C1 DMA Init */
	enable_dma_nvic();

	/** I2C Initialization
	 */
	enable_device_i2c();

	/* USER CODE BEGIN I2C1_Init 2 */

	/* USER CODE END I2C1_Init 2 */
	return ret;

}

uint8_t deinit_device(void) {
	return 0;
}

void Handle_I2C_Master(uint8_t addr , uint8_t *pTransmitBuffer,
__IO uint8_t ubNbDataToTransmit) {
	LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_1);
	/* (1) Enable DMA transfer **************************************************/
	LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_1, ubNbDataToTransmit);
	LL_DMA_ConfigAddresses(DMA1, LL_DMA_STREAM_1, (uint32_t) pTransmitBuffer,
			(uint32_t) LL_I2C_DMA_GetRegAddr(I2C1),
			LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_STREAM_1));
	LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_1);
	/* (2) Prepare acknowledge for Master data reception ************************/
	LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_ACK);

	/* (3) Initiate a Start condition to the Slave device ***********************/
	/* Master Generate Start condition */
	LL_I2C_GenerateStartCondition(I2C1);

	/* (4) Loop until Start Bit transmitted (SB flag raised) ********************/

	Timeout = I2C_SEND_TIMEOUT_SB_MS;

	/* Loop until SB flag is raised  */
	while (!LL_I2C_IsActiveFlag_SB(I2C1)) {
		/* Check Systick counter flag to decrement the time-out value */
		if (LL_SYSTICK_IsActiveCounterFlag()) {
			if (Timeout-- == 0) {
				/* Time-out occurred. Set LED2 to blinking mode */
			}
		}
	}

	/* (5) Send Slave address with a 7-Bit SLAVE_OWN_ADDRESS for a write request */
	LL_I2C_TransmitData8(I2C1, addr << 1 | I2C_REQUEST_WRITE);

	/* (6) Loop until Address Acknowledgement received (ADDR flag raised) *******/

	Timeout = I2C_SEND_TIMEOUT_ADDR_MS;

	/* Loop until ADDR flag is raised  */LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_1);
	while (!LL_I2C_IsActiveFlag_ADDR(I2C1)) {
		/* Check Systick counter flag to decrement the time-out value */
		if (LL_SYSTICK_IsActiveCounterFlag()) {
			if (Timeout-- == 0) {
				/* Time-out occurred. Set LED2 to blinking mode */
			}
		}
	}

	/* (7) Clear ADDR flag and loop until end of transfer completed (DMA TC raised) */

	/* Clear ADDR flag value in ISR register */
	LL_I2C_ClearFlag_ADDR(I2C1);

	Timeout = DMA_SEND_TIMEOUT_TC_MS;

	/* Loop until DMA transfer complete event */
	while (!ubMasterTransferComplete) {
		/* Check Systick counter flag to decrement the time-out value */
		if (LL_SYSTICK_IsActiveCounterFlag()) {
			if (Timeout-- == 0) {
				/* Time-out occurred. Set LED2 to blinking mode */
			}
		}
	}

	/* (8) Loop until end of master transfer completed (TXE flag raised) then generate STOP condition
	 *             -8.1- Data consistency are checking into Slave process. */

	Timeout = I2C_SEND_TIMEOUT_TXE_MS;

	/* Loop until end of master transfer completed (TXE flag raised) */
	while (!LL_I2C_IsActiveFlag_TXE(I2C1)) {
		/* Check Systick counter flag to decrement the time-out value */
		if (LL_SYSTICK_IsActiveCounterFlag()) {
			if (Timeout-- == 0) {
				/* Time-out occurred. Set LED2 to blinking mode */
			}
		}
	}

	/* Generate Stop condition */
	LL_I2C_GenerateStopCondition(I2C1);
}

void DMA1_Stream5_IRQHandler(void) {
	if (LL_DMA_IsActiveFlag_TC5(DMA1)) {
		LL_DMA_ClearFlag_TC5(DMA1);
		DMA1_Transfer_Complete_Callback();
	} else if (LL_DMA_IsActiveFlag_TE5(DMA1)) {
		DMA1_Transfer_Error_Callback();
	}
}

/**
 * @brief  This function handles DMA1_Stream1 interrupt request.
 * @param  None
 * @retval None
 */
void DMA1_Stream1_IRQHandler(void) {
	if (LL_DMA_IsActiveFlag_TC1(DMA1)) {
		LL_DMA_ClearFlag_TC1(DMA1);
		DMA1_Transfer_Complete_Callback();
	} else if (LL_DMA_IsActiveFlag_TE1(DMA1)) {
		DMA1_Transfer_Error_Callback();
	}
}

/**
 * @brief  Function called from DMA1 IRQ Handler
 * @note   This function is executed when the transfer complete interrupt
 *         is generated
 * @retval None
 */
void DMA1_Transfer_Complete_Callback() {
	/* DMA transfer completed */
	ubMasterTransferComplete = 1;
}

/**
 * @brief  Function called from DMA1 IRQ Handler
 * @note   This function is executed when the transfer error interrupt
 *         is generated during DMA transfer
 * @retval None
 */
void DMA1_Transfer_Error_Callback() {
	/* Disable DMA1_Stream1_IRQn */
	NVIC_DisableIRQ(DMA1_Stream1_IRQn);
	/* Error detected during DMA transfer */
}

/**
 * @brief  Function called in case of error detected in I2C IT Handler
 * @param  None
 * @retval None
 */
void Error_Callback(void) {
	/* Disable DMA1_Stream5_IRQn and DMA1_Stream1_IRQn */
	NVIC_DisableIRQ(DMA1_Stream5_IRQn);
	NVIC_DisableIRQ(DMA1_Stream1_IRQn);

	/* Unexpected event : Set LED2 to Blinking mode to indicate error occurs */
}
