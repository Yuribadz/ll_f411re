/*
 * gpio_device_config.c
 *
 *  Created on: Jun 13, 2022
 *      Author: yurib
 */

#include <device_config.h>

uint8_t init_devices(device_config_t* devices, uint32_t num)
{
	uint8_t ret = 0U;
	for(uint32_t i = 0; i < num; ++i)
	{
		ret = devices->init_Device();
	}
	return ret;
}
uint32_t deinit_devices(device_config_t* devices, uint32_t num)
{
	uint8_t ret = 0U;
	for(uint32_t i = 0; i < num; ++i)
	{
		ret = devices->deinit_Device();
	}
	return ret;
}
