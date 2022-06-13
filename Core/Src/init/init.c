/*
 * init.c
 *
 *  Created on: 24 трав. 2022 р.
 *      Author: yurib
 */
#include "init.h"


device_config_t* devices[] = {
		&button, &leds
};



uint8_t init(void) {

	uint8_t ret = 0U;
	//HAL_Init();

	SystemClock_Config();
	for(uint8_t i = 0; i < 2; ++i)
	{
		devices[i]->init_Device();
	}

	DMA_Init();
	USART2_UART_Init();
	TIM4_Init();
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
