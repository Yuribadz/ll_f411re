/*
 * init.h
 *
 *  Created on: 24 трав. 2022 р.
 *      Author: yurib
 */

#ifndef SRC_INIT_INIT_H_
#define SRC_INIT_INIT_H_

#include "main.h"
#include "cmsis_os.h"
#include "clock_config.h"
#include "tim4_config.h"
#include "tasks.h"
#include "device_config.h"
#include "generic_button.h"
#include "generic_led.h"
#include "debug_usart.h"

#define DEVICES_NUM 3U
extern device_config_t* devices[DEVICES_NUM];

uint8_t init(void);

#endif /* SRC_INIT_INIT_H_ */
