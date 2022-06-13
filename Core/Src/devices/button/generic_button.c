#include "generic_button.h"

device_config_t button = { &button_init, &button_deinit };

uint8_t button_init(void) {
	uint8_t ret = 0U;
	LL_EXTI_InitTypeDef EXTI_InitStruct = { 0 };
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	// Check and enable clock
	if (LL_AHB1_GRP1_IsEnabledClock(B1_AHB) == false) {
		LL_AHB1_GRP1_EnableClock(B1_AHB);
	}

	GPIO_InitStruct.Pin = B1_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	ret = LL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);
	// Enable interrupts for button
	LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC, LL_SYSCFG_EXTI_LINE13);
	EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_13;
	EXTI_InitStruct.LineCommand = ENABLE;
	EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
	EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_FALLING;
	LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_13);
	ret = LL_EXTI_Init(&EXTI_InitStruct);

	NVIC_SetPriority(EXTI15_10_IRQn,
			NVIC_EncodePriority(NVIC_GetPriorityGrouping(), B1_PRIORITY,
			B1_SUBPRIORITY));
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	return ret;

}

uint8_t button_deinit(void) {
	uint8_t ret = 0U;
	LL_EXTI_InitTypeDef EXTI_InitStruct = { 0 };
	if (LL_AHB1_GRP1_IsEnabledClock(B1_AHB) == true) {
		LL_AHB1_GRP1_DisableClock(B1_AHB);
	}
	EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_13;
	EXTI_InitStruct.LineCommand = DISABLE;
	EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
	EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_FALLING;
	NVIC_DisableIRQ(EXTI15_10_IRQn);
	ret = LL_EXTI_Init(&EXTI_InitStruct);
	return ret;
}


