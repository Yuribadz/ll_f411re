/*
 * usart2_config.c
 *
 *  Created on: May 21, 2022
 *      Author: yurib
 */

#include "usart2_config.h"
lwrb_t usart2_tx_buff;
uint8_t usart2_tx_buff_data[1024];
volatile size_t usart2_tx_dma_current_len;
extern osMessageQueueId_t usart_rx_dma_queue_id;
