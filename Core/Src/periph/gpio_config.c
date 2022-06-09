/*
 * gpio_config.c
 *
 *  Created on: 24 трав. 2022 р.
 *      Author: yurib
 */

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */

#include "gpio_config.h"
void GPIO_Init(void) {
	LL_EXTI_InitTypeDef EXTI_InitStruct = { 0 };
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOH);
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);

	/**/
	LL_GPIO_ResetOutputPin(LD1_GPIO_Port, LD1_Pin);

	/**/
	LL_GPIO_ResetOutputPin(GPIOC, LD4_Pin | LD3_Pin | LD2_Pin);

	/**/
	LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC, LL_SYSCFG_EXTI_LINE13);

	/**/
	EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_13;
	EXTI_InitStruct.LineCommand = ENABLE;
	EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
	EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_FALLING;
	LL_EXTI_Init(&EXTI_InitStruct);

	/**/
	LL_GPIO_SetPinPull(B1_GPIO_Port, B1_Pin, LL_GPIO_PULL_NO);

	/**/
	LL_GPIO_SetPinMode(B1_GPIO_Port, B1_Pin, LL_GPIO_MODE_INPUT);

	/**/
	GPIO_InitStruct.Pin = LD1_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(LD1_GPIO_Port, &GPIO_InitStruct);

	/**/
	GPIO_InitStruct.Pin = LD4_Pin | LD3_Pin | LD2_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/* EXTI interrupt init*/
	NVIC_SetPriority(EXTI15_10_IRQn,
			NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 5, 0));
	NVIC_EnableIRQ(EXTI15_10_IRQn);

}
