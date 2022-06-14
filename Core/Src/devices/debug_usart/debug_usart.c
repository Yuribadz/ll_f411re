/*
 * debug_usart.c
 *
 *  Created on: Jun 14, 2022
 *      Author: yurib
 */

#include "debug_usart.h"

lwrb_t usart2_tx_buff;
uint8_t usart2_tx_buff_data[1024];
volatile size_t usart2_tx_dma_current_len;

//static osMessageQueueId_t usart_rx_dma_queue_id;

device_config_t debug_usart = {&debug_usart_init, &debug_usart_deinit};
uint8_t debug_usart_init(void) {

	uint8_t ret = 0U;
	usart2_tx_dma_current_len = 0U;
	memset((void*)usart2_tx_buff_data, 0, 1024);
	LL_USART_InitTypeDef USART_InitStruct = { 0 };

	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* Init with LL driver */
	/* DMA controller clock enable */
	if ((LL_APB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_DMA1) == false)) {
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
	}
	if ((LL_APB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_GPIOA) == false)) {
		LL_APB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	}
	/* Peripheral clock enable */
	if ((LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_USART2) == false)) {
		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
	}
	/**USART2 GPIO Configuration
	 PA2   ------> USART2_TX
	 PA3   ------> USART2_RX
	 */
	GPIO_InitStruct.Pin = USART_TX_Pin | USART_RX_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
	ret = LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* USART2 DMA Init */
	/* DMA interrupt init */
	/* DMA1_Stream5_IRQn interrupt configuration */
	NVIC_SetPriority(DMA1_Stream5_IRQn,
			NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 5, 0));
	NVIC_EnableIRQ(DMA1_Stream5_IRQn);
	/* DMA1_Stream6_IRQn interrupt configuration */
	NVIC_SetPriority(DMA1_Stream6_IRQn,
			NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 5, 0));
	NVIC_EnableIRQ(DMA1_Stream6_IRQn);

	/* USART2_RX Init */
	LL_DMA_SetChannelSelection(DMA1, LL_DMA_STREAM_5, LL_DMA_CHANNEL_4);

	LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_STREAM_5,
	LL_DMA_DIRECTION_PERIPH_TO_MEMORY);

	LL_DMA_SetStreamPriorityLevel(DMA1, LL_DMA_STREAM_5,
	LL_DMA_PRIORITY_MEDIUM);

	LL_DMA_SetMode(DMA1, LL_DMA_STREAM_5, LL_DMA_MODE_NORMAL);

	LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_STREAM_5, LL_DMA_PERIPH_NOINCREMENT);

	LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_STREAM_5, LL_DMA_MEMORY_INCREMENT);

	LL_DMA_SetPeriphSize(DMA1, LL_DMA_STREAM_5, LL_DMA_PDATAALIGN_BYTE);

	LL_DMA_SetMemorySize(DMA1, LL_DMA_STREAM_5, LL_DMA_MDATAALIGN_BYTE);

	LL_DMA_DisableFifoMode(DMA1, LL_DMA_STREAM_5);

	/* USART2_TX Init */
	LL_DMA_SetChannelSelection(DMA1, LL_DMA_STREAM_6, LL_DMA_CHANNEL_4);

	LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_STREAM_6,
	LL_DMA_DIRECTION_MEMORY_TO_PERIPH);

	LL_DMA_SetStreamPriorityLevel(DMA1, LL_DMA_STREAM_6, LL_DMA_PRIORITY_LOW);

	LL_DMA_SetMode(DMA1, LL_DMA_STREAM_6, LL_DMA_MODE_NORMAL);

	LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_STREAM_6, LL_DMA_PERIPH_NOINCREMENT);

	LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_STREAM_6, LL_DMA_MEMORY_INCREMENT);

	LL_DMA_SetPeriphSize(DMA1, LL_DMA_STREAM_6, LL_DMA_PDATAALIGN_BYTE);

	LL_DMA_SetMemorySize(DMA1, LL_DMA_STREAM_6, LL_DMA_MDATAALIGN_BYTE);

	LL_DMA_DisableFifoMode(DMA1, LL_DMA_STREAM_6);

	LL_DMA_SetPeriphAddress(DMA1, LL_DMA_STREAM_6,
			LL_USART_DMA_GetRegAddr(USART2));
	LL_DMA_EnableIT_TC(DMA1, LL_DMA_STREAM_6);

	/* USER CODE BEGIN USART2_Init 1 */

	/* USER CODE END USART2_Init 1 */
	USART_InitStruct.BaudRate = 115200;
	USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
	USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
	USART_InitStruct.Parity = LL_USART_PARITY_NONE;
	USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
	USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
	ret = LL_USART_Init(USART2, &USART_InitStruct);
	LL_USART_ConfigAsyncMode(USART2);
	LL_USART_EnableDMAReq_TX(USART2);

	/* USART2 interrupt Init */
	NVIC_SetPriority(USART2_IRQn,
			NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 5, 1));
	NVIC_EnableIRQ(USART2_IRQn);
	LL_USART_Enable(USART2);
	ret = lwrb_init(&usart2_tx_buff, usart2_tx_buff_data,
			sizeof(usart2_tx_buff_data));
	return ret;

}

uint8_t debug_send_msg(const char* msg)
{
	usart_send_string(DMA1, LL_DMA_STREAM_6, &usart2_tx_dma_current_len, &usart2_tx_buff, msg);
	return 0U;
}

uint8_t debug_usart_deinit(void) {
	uint8_t ret = 0U;
	ret = LL_USART_DeInit(USART2);
	ret = (uint8_t)LL_DMA_DeInit(DMA1, LL_DMA_STREAM_5);
	ret = (uint8_t)LL_DMA_DeInit(DMA1, LL_DMA_STREAM_6);
	return ret;
}

void DMA1_Stream6_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream6_IRQn 0 */
    /* Check transfer-complete interrupt */
    if (LL_DMA_IsEnabledIT_TC(DMA1, LL_DMA_STREAM_6) && LL_DMA_IsActiveFlag_TC6(DMA1)) {
        LL_DMA_ClearFlag_TC6(DMA1);             /* Clear transfer complete flag */
        lwrb_skip(&usart2_tx_buff, usart2_tx_dma_current_len);/* Data sent, ignore these */
        usart2_tx_dma_current_len = 0;
        LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_6);
        usart_start_tx_dma_transfer(DMA1, LL_DMA_STREAM_6, &usart2_tx_dma_current_len, &usart2_tx_buff);
    }
}

/**
  * @brief This function handles DMA1 stream5 global interrupt.
  */
void DMA1_Stream5_IRQHandler(void)
{
}

