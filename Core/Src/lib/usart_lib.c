#include "usart_lib.h"

/**
 * \brief           Send debug string over UART
 * \param[in]       str: String to send
 */
void usart_send_string(DMA_TypeDef *Dma, uint32_t Stream, volatile size_t* usart_tx_dma_current_len, lwrb_t* usart_tx_buff, const char *str) {
	size_t len = strlen(str);

	if (lwrb_get_free(usart_tx_buff) >= len) {
		lwrb_write(usart_tx_buff, str, len);
		usart_start_tx_dma_transfer(Dma, Stream, usart_tx_dma_current_len , usart_tx_buff);
	}
}
/**
 * \brief           Checks for data in buffer and starts transfer if not in progress
 */
uint8_t usart_start_tx_dma_transfer(DMA_TypeDef *Dma, uint32_t Stream, volatile size_t* usart_tx_dma_current_len, lwrb_t* usart_tx_buff) {
	uint32_t primask;
	uint8_t started = 0;

	/*
	 * First check if transfer is currently in-active,
	 * by examining the value of usart_tx_dma_current_len variable.
	 *
	 * This variable is set before DMA transfer is started and cleared in DMA TX complete interrupt.
	 *
	 * It is not necessary to disable the interrupts before checking the variable:
	 *
	 * When usart_tx_dma_current_len == 0
	 *    - This function is called by either application or TX DMA interrupt
	 *    - When called from interrupt, it was just reset before the call,
	 *         indicating transfer just completed and ready for more
	 *    - When called from an application, transfer was previously already in-active
	 *         and immediate call from interrupt cannot happen at this moment
	 *
	 * When usart_tx_dma_current_len != 0
	 *    - This function is called only by an application.
	 *    - It will never be called from interrupt with usart_tx_dma_current_len != 0 condition
	 *
	 * Disabling interrupts before checking for next transfer is advised
	 * only if multiple operating system threads can access to this function w/o
	 * exclusive access protection (mutex) configured,
	 * or if application calls this function from multiple interrupts.
	 *
	 * This example assumes worst use case scenario,
	 * hence interrupts are disabled prior every check
	 */
	primask = __get_PRIMASK();
	__disable_irq();
	if (*usart_tx_dma_current_len == 0 && (*usart_tx_dma_current_len =
			lwrb_get_linear_block_read_length(usart_tx_buff)) > 0) {
		/* Limit maximal size to transmit at a time */
		if (*usart_tx_dma_current_len > 64) {
			*usart_tx_dma_current_len = 64;
		}

		/* Configure DMA */
		LL_DMA_SetDataLength(Dma, Stream, *usart_tx_dma_current_len);
		LL_DMA_SetMemoryAddress(Dma, Stream,
				(uint32_t) lwrb_get_linear_block_read_address(usart_tx_buff));

		/* Clear all flags */
		LL_DMA_ClearFlag_TC6(Dma);
		LL_DMA_ClearFlag_HT6(Dma);
		LL_DMA_ClearFlag_DME6(Dma);
		LL_DMA_ClearFlag_FE6(Dma);
		LL_DMA_ClearFlag_TE6(Dma);

		/* Start transfer */
		LL_DMA_EnableStream(Dma, Stream);
		started = 1;
	}
	__set_PRIMASK(primask);
	return started;
}

