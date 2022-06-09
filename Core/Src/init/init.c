/*
 * init.c
 *
 *  Created on: 24 трав. 2022 р.
 *      Author: yurib
 */
#include "init.h"
#include "cmsis_os.h"
#include "clock_config.h"
#include "dma_config.h"
#include "gpio_config.h"
#include "usart_config.h"
#include "tim4_config.h"
#include "tasks.h"



uint8_t init(void) {

	uint8_t ret = 0U;
	//HAL_Init();

	SystemClock_Config();
	GPIO_Init();
	DMA_Init();
	USART2_UART_Init();
	TIM4_Init();
	LL_TIM_EnableCounter(TIM4);
	osKernelInitialize();
	rotaryUpdateHandle = osThreadNew(rotaryUpdateTask, NULL, &rotaryUpdate_attributes);
	/* creation of display */
	//displayHandle = osThreadNew(displayTask, NULL, &display_attributes);
	/* creation of esp */
	//espHandle = osThreadNew(espTask, NULL, &esp_attributes);
	/* creation of output */
	outputHandle = osThreadNew(outputTask, NULL, &output_attributes);

	/* Start scheduler */
	osKernelStart();
	return ret;
}
