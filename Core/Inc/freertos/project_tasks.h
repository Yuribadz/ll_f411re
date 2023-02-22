/*
 * tasks.h
 *
 *  Created on: 24 трав. 2022 р.
 *      Author: yurib
 */

#ifndef INC_FREERTOS_PROJECT_TASKS_H_
#define INC_FREERTOS_PROJECT_TASKS_H_
#include "main.h"
#include "cmsis_os.h"
#include "usart_lib.h"

typedef StaticTask_t osStaticThreadDef_t;

extern osThreadId_t rotaryUpdateHandle;
extern osThreadId_t displayHandle;
extern osThreadId_t espHandle;
extern osThreadId_t outputHandle;

extern const osThreadAttr_t rotaryUpdate_attributes;
extern const osThreadAttr_t display_attributes;
extern const osThreadAttr_t esp_attributes;
extern const osThreadAttr_t output_attributes;

extern osStaticThreadDef_t rotaryUpdateControlBlock;
extern osStaticThreadDef_t displayControlBlock;
extern osStaticThreadDef_t espControlBlock;
extern osStaticThreadDef_t outputControlBlock;

extern void rotaryUpdateTask(void *argument);
extern void displayTask(void *argument);
extern void espTask(void *argument);
extern void outputTask(void *argument);
#endif /* INC_FREERTOS_PROJECT_TASKS_H_ */
