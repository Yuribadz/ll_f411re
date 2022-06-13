/*
 * generic_button.h
 *
 *  Created on: Jun 13, 2022
 *      Author: yurib
 */

#ifndef INC_DEVICES_BUTTON_GENERIC_BUTTON_H_
#define INC_DEVICES_BUTTON_GENERIC_BUTTON_H_

#include "main.h"
#include "device_config.h"

#define B1_Pin LL_GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI15_10_IRQn
#define B1_AHB LL_AHB1_GRP1_PERIPH_GPIOC
#define B1_PRIORITY 5U
#define B1_SUBPRIORITY 0U

extern uint8_t button_init(void);
extern uint8_t button_deinit(void);
extern device_config_t button;

#endif /* INC_DEVICES_BUTTON_GENERIC_BUTTON_H_ */
