/*
 * usart_lib.h
 *
 *  Created on: May 21, 2022
 *      Author: yurib
 */

#ifndef INC_LIB_USART_LIB_H_
#define INC_LIB_USART_LIB_H_

#include "stm32f4xx_ll_usart.h"
#include "stm32f4xx_ll_dma.h"
#include "lwrb.h"

/* USART related functions */
#define ARRAY_LEN(x)            (sizeof(x) / sizeof((x)[0]))



extern void usart_send_string(DMA_TypeDef *Dma, uint32_t Stream, volatile size_t*  usart_tx_dma_current_len, lwrb_t* usart_tx_buff, const char *str);
extern uint8_t usart_start_tx_dma_transfer(DMA_TypeDef *Dma, uint32_t Stream, volatile size_t* usart_tx_dma_current_len, lwrb_t* usart_tx_buff);


#endif /* INC_LIB_USART_LIB_H_ */
