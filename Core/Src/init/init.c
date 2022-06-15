/*
 * init.c
 *
 *  Created on: 24 трав. 2022 р.
 *      Author: yurib
 */
#include "init.h"


device_config_t* devices[DEVICES_NUM] = {
		&button, &leds, &debug_usart, &i2c1_device
};



uint8_t init(void) {

	uint8_t ret = 0U;
	//HAL_Init();
	SystemClock_Config();
//	SEGGER_SYSVIEW_Conf();
//	SEGGER_SYSVIEW_Start();
	for(uint8_t i = 0; i < DEVICES_NUM; ++i)
	{
		devices[i]->init_Device();
	}
	uint8_t buffer[1] = {0x21};
	Handle_I2C_Master(0x70,buffer, 1);
	buffer[0] = 0x81;
	Handle_I2C_Master(0x70,buffer, 1);
	LL_mDelay(500);
	buffer[0] = 0x80;
	Handle_I2C_Master(0x70,buffer, 1);
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
