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
#include "usart2_config.h"
#include "lwrb.h"

/* USART related functions */
#define ARRAY_LEN(x)            (sizeof(x) / sizeof((x)[0]))
#define SEND_DBG_MSG(msg)       usart_send_string(DMA1, LL_DMA_STREAM_6, &usart2_tx_dma_current_len, &usart2_tx_buff, msg);


//void init_thread(void *arg);
//void usart_rx_dma_thread(void *arg);


/**
 * \brief           USART DMA check thread
 * \param[in]       arg: Thread argument
 */
//void usart_rx_dma_thread(void *arg);
void usart_send_string(DMA_TypeDef *Dma, uint32_t Stream, volatile size_t*  usart_tx_dma_current_len, lwrb_t* usart_tx_buff, const char *str);
uint8_t usart_start_tx_dma_transfer(DMA_TypeDef *Dma, uint32_t Stream, volatile size_t* usart_tx_dma_current_len, lwrb_t* usart_tx_buff);
//void usart_init(USART_TypeDef* usart);
//void usart_rx_check(USART_TypeDef *usart, DMA_TypeDef *dma, uint32_t Stream);
//void usart_process_data(USART_TypeDef *usart, const void *data, size_t len);

#endif /* INC_LIB_USART_LIB_H_ */
