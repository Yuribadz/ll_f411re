#include "generic_led.h"

device_config_t leds = {
		&led_init, &led_deinit
};

uint8_t led_init(void) {
	uint8_t ret = 0U;
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	// Check and enable clock
	if (LL_AHB1_GRP1_IsEnabledClock(LD_AHB_2) == false) {
		LL_AHB1_GRP1_EnableClock(LD_AHB_1);
	}
	if (LL_AHB1_GRP1_IsEnabledClock(LD_AHB_2) == false) {
		LL_AHB1_GRP1_EnableClock(LD_AHB_2);
	}
	// Reset output pins
	/**/
	LL_GPIO_ResetOutputPin(LD1_GPIO_Port, LD1_Pin);

	/**/
	LL_GPIO_ResetOutputPin(GPIOC, LD4_Pin | LD3_Pin | LD2_Pin);

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
	return ret;
}
uint8_t led_deinit(void) {
	return 0;
}
