/*
 * generic_led.h
 *
 *  Created on: Jun 13, 2022
 *      Author: yurib
 */

#ifndef INC_DEVICES_LED_GENERIC_LED_H_
#define INC_DEVICES_LED_GENERIC_LED_H_

#include "main.h"
#include "device_config.h"
#define LD1_Pin LL_GPIO_PIN_5
#define LD1_GPIO_Port GPIOA
#define LD4_Pin LL_GPIO_PIN_5
#define LD4_GPIO_Port GPIOC
#define LD3_Pin LL_GPIO_PIN_8
#define LD3_GPIO_Port GPIOC
#define LD2_Pin LL_GPIO_PIN_9
#define LD2_GPIO_Port GPIOC
#define LD_AHB_1 LL_AHB1_GRP1_PERIPH_GPIOC
#define LD_AHB_2 LL_AHB1_GRP1_PERIPH_GPIOA



extern uint8_t led_init(void);
extern uint8_t led_deinit(void);
extern device_config_t leds;

#endif /* INC_DEVICES_LED_GENERIC_LED_H_ */
