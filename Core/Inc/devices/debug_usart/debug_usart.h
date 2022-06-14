/*
 * debug_usart.h
 *
 *  Created on: Jun 14, 2022
 *      Author: yurib
 */

#ifndef INC_DEVICES_DEBUG_USART_DEBUG_USART_H_
#define INC_DEVICES_DEBUG_USART_DEBUG_USART_H_

#include "main.h"


#include "lwrb.h"
#include "cmsis_os2.h"
#include "usart_lib.h"
#include "device_config.h"

#define DEBUG_PRINT(msg) debug_send_msg(msg)
extern device_config_t debug_usart;
/**usart2_tx_dma_current_len
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
extern uint8_t debug_usart_init(void);
extern uint8_t debug_usart_deinit(void);
extern uint8_t debug_send_msg(const char* msg);
void DMA1_Stream5_IRQHandler(void);
void DMA1_Stream6_IRQHandler(void);

#endif /* INC_DEVICES_DEBUG_USART_DEBUG_USART_H_ */
