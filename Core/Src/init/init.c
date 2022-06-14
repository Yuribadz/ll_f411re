/*
 * init.c
 *
 *  Created on: 24 трав. 2022 р.
 *      Author: yurib
 */
#include "init.h"


device_config_t* devices[DEVICES_NUM] = {
		&button, &leds, &debug_usart
};



uint8_t init(void) {

	uint8_t ret = 0U;
	//HAL_Init();

	SystemClock_Config();
	for(uint8_t i = 0; i < DEVICES_NUM; ++i)
	{
		devices[i]->init_Device();
	}
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
