/*
 * dma_irq.c
 *
 *  Created on: May 21, 2022
 *      Author: yurib
 */

#include "lwrb.h"
#include "usart_lib.h"
#include "usart2_config.h"
void DMA1_Stream6_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream6_IRQn 0 */
    /* Check transfer-complete interrupt */
    if (LL_DMA_IsEnabledIT_TC(DMA1, LL_DMA_STREAM_6) && LL_DMA_IsActiveFlag_TC6(DMA1)) {
        LL_DMA_ClearFlag_TC6(DMA1);             /* Clear transfer complete flag */
        lwrb_skip(&usart2_tx_buff, usart2_tx_dma_current_len);/* Data sent, ignore these */
        usart2_tx_dma_current_len = 0;
        LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_6);
        usart_start_tx_dma_transfer(DMA1, LL_DMA_STREAM_6, &usart2_tx_dma_current_len, &usart2_tx_buff);
    }

    /* Implement other events when needed */
  /* USER CODE END DMA1_Stream6_IRQn 0 */

  /* USER CODE BEGIN DMA1_Stream6_IRQn 1 */

  /* USER CODE END DMA1_Stream6_IRQn 1 */
}

/**
  * @brief This function handles DMA1 stream5 global interrupt.
  */
void DMA1_Stream5_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream5_IRQn 0 */

  /* USER CODE END DMA1_Stream5_IRQn 0 */

  /* USER CODE BEGIN DMA1_Stream5_IRQn 1 */

  /* USER CODE END DMA1_Stream5_IRQn 1 */
}
