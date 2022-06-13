/*
 * button_configuration.h
 *
 *  Created on: Jun 13, 2022
 *      Author: yurib
 */

#ifndef INC_LIB_DEVICE_CONFIG_H_
#define INC_LIB_DEVICE_CONFIG_H_

#include "main.h"

#define DEVICE_OUTPUT false
#define DEVICE_INPUT true

typedef struct gpio_device_configuration {
	uint8_t(*init_Device)(void);
	uint8_t(*deinit_Device)(void);
} device_config_t;

uint8_t init_devices(device_config_t* devices, uint32_t num);
uint32_t deinit_devices(device_config_t* devices, uint32_t num);
#endif /* INC_LIB_DEVICE_CONFIG_H_ */
