/*
 * clock_config.c
 *
 *  Created on: 24 трав. 2022 р.
 *      Author: yurib
 */

/**
 * @brief System Clock Configuration
 * @retval None
 */

#include "clock_config.h"



void SystemClock_Config(void) {
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
	while (LL_FLASH_GetLatency() != LL_FLASH_LATENCY_2) {
	}
	LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
	LL_RCC_HSI_SetCalibTrimming(16);
	LL_RCC_HSI_Enable();

	/* Wait till HSI is ready */
	while (LL_RCC_HSI_IsReady() != 1) {

	}
	LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_16, 336,
			LL_RCC_PLLP_DIV_4);
	LL_RCC_PLL_Enable();

	/* Wait till PLL is ready */
	while (LL_RCC_PLL_IsReady() != 1) {

	}
	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
	LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

	/* Wait till System clock is ready */
	while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL) {

	}
	LL_SetSystemCoreClock(84000000);

	/* Update the time base */
	if (HAL_InitTick(TICK_INT_PRIORITY) != HAL_OK) {
		Error_Handler();
	}
	LL_RCC_SetTIMPrescaler(LL_RCC_TIM_PRESCALER_TWICE);
}
