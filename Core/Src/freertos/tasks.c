/*
 * tasks.c
 *
 *  Created on: 24 трав. 2022 р.
 *      Author: yurib
 */

#include "tasks.h"
#include <stdio.h>
/* Definitions for rotaryUpdate */
osThreadId_t rotaryUpdateHandle;
uint32_t rotaryUpdateBuffer[ 128 ];
osStaticThreadDef_t rotaryUpdateControlBlock;
const osThreadAttr_t rotaryUpdate_attributes = {
  .name = "rotaryUpdate",
  .cb_mem = &rotaryUpdateControlBlock,
  .cb_size = sizeof(rotaryUpdateControlBlock),
  .stack_mem = &rotaryUpdateBuffer[0],
  .stack_size = sizeof(rotaryUpdateBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for display */
osThreadId_t displayHandle;
uint32_t displayBuffer[ 64 ];
osStaticThreadDef_t displayControlBlock;
const osThreadAttr_t display_attributes = {
  .name = "display",
  .cb_mem = &displayControlBlock,
  .cb_size = sizeof(displayControlBlock),
  .stack_mem = &displayBuffer[0],
  .stack_size = sizeof(displayBuffer),
  .priority = (osPriority_t) osPriorityNormal1,
};
/* Definitions for esp */
osThreadId_t espHandle;
uint32_t espBuffer[ 64 ];
osStaticThreadDef_t espControlBlock;
const osThreadAttr_t esp_attributes = {
  .name = "esp",
  .cb_mem = &espControlBlock,
  .cb_size = sizeof(espControlBlock),
  .stack_mem = &espBuffer[0],
  .stack_size = sizeof(espBuffer),
  .priority = (osPriority_t) osPriorityNormal3,
};
/* Definitions for output */
osThreadId_t outputHandle;
uint32_t outputBuffer[ 64 ];
osStaticThreadDef_t outputControlBlock;
const osThreadAttr_t output_attributes = {
  .name = "output",
  .cb_mem = &outputControlBlock,
  .cb_size = sizeof(outputControlBlock),
  .stack_mem = &outputBuffer[0],
  .stack_size = sizeof(outputBuffer),
  .priority = (osPriority_t) osPriorityLow,
};


/**
 * @brief  Function implementing the rotaryUpdate thread.
 * @param  argument: Not used
 * @retval None
 */
void rotaryUpdateTask(void *argument) {
	/* USER CODE BEGIN 5 */
	/* Infinite loop */
	uint32_t count;
	char buffer[100];
	for (;;) {
		count = LL_TIM_GetCounter(TIM4);
		snprintf(buffer, 100,  "Count = %lu\r\n", count);
		SEND_DBG_MSG(buffer);
		osDelay(1000U);
		LL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);

	}
	/* USER CODE END 5 */
}

/**
 * @brief Function implementing the display thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_displayTask */
void displayTask(void *argument) {
	for (;;) {
		osDelay(2000U);
		LL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

	}
}

/**
 * @brief Function implementing the esp thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_espTask */
void espTask(void *argument) {
	for (;;) {
		osDelay(3000U);
		LL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);

	}
}

/**
 * @brief Function implementing the output thread.
 * @param argument: Not used
 * @retval None
 */
void outputTask(void *argument) {
	static const char long_string[] =
			""
					"Miusov, as a man man of breeding and deilcacy,"
					"could not but feel some inwrd qualms, when he reached the Father Superior's with Ivan:"
					"he felt ashamed of havin lost his temper."
					"He felt that he ought to have disdaimed that despicable wretch,"
					"Fyodor Pavlovitch, too much to have been upset by him in Father Zossima's cell,"
					"and so to have forgotten himself. \"Teh monks were not to blame,"
					"in any case,\" he reflected, on the steps."
					"\"And if they\'re decent people here (and the Father Superior,"
					"I understand, is a nobleman) why not be friendly and courteous withthem?"
					"I won't argue, I'll fall in with everything, I'll win them by politness,"
					"and show them that I've nothing to do with that Aesop, thta buffoon,"
					"that Pierrot, and have merely been takken in over this affair, just as they have.\r\n"
					"";
	for (;;) {
		SEND_DBG_MSG(long_string);
		SEND_DBG_MSG("press f to pay respects\r\n");
		osDelay(1000U);
		LL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);

	}
}
