/*
 * usart_config.c
 *
 *  Created on: 24 трав. 2022 р.
 *      Author: yurib
 */

/**
 * @brief USART2 Initialization Function
 * @param None
 * @retval None
 */
#include "usart_config.h"

void USART2_UART_Init(void) {

	/* USER CODE BEGIN USART2_Init 0 */

	/* USER CODE END USART2_Init 0 */

	LL_USART_InitTypeDef USART_InitStruct = { 0 };

	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* Peripheral clock enable */
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
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
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* USART2 DMA Init */

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
	LL_USART_Init(USART2, &USART_InitStruct);
	LL_USART_ConfigAsyncMode(USART2);
	LL_USART_EnableDMAReq_TX(USART2);

	/* USART2 interrupt Init */
	NVIC_SetPriority(USART2_IRQn,
			NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 5, 1));
	NVIC_EnableIRQ(USART2_IRQn);
	LL_USART_Enable(USART2);
	lwrb_init(&usart2_tx_buff, usart2_tx_buff_data,
			sizeof(usart2_tx_buff_data));
	/* USER CODE BEGIN USART2_Init 2 */

	/* USER CODE END USART2_Init 2 */

}
