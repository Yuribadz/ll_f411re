/*
 * usart2_config.h
 *
 *  Created on: May 21, 2022
 *      Author: yurib
 */

#ifndef INC_LIB_USART2_CONFIG_H_
#define INC_LIB_USART2_CONFIG_H_

#include "lwrb.h"
#include "cmsis_os2.h"

extern lwrb_t usart2_tx_buff;
extern uint8_t usart2_tx_buff_data[1024];
extern volatile size_t usart2_tx_dma_current_len;
/* Message queue ID */
extern osMessageQueueId_t usart_rx_dma_queue_id;


#endif /* INC_LIB_USART2_CONFIG_H_ */
