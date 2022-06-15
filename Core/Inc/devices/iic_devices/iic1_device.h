/*
 * iic1_device.h
 *
 *  Created on: Jun 15, 2022
 *      Author: yurib
 */

#ifndef INC_DEVICES_IIC1_DEVICE_H_
#define INC_DEVICES_IIC1_DEVICE_H_

#include "main.h"
#include "device_config.h"

#endif /* INC_DEVICES_IIC1_DEVICE_H_ */
#define I2C_REQUEST_WRITE                       0x00
#define I2C_REQUEST_READ                        0x01
extern uint8_t init_device(void);
extern uint8_t deinit_device(void);
extern device_config_t i2c1_device;
extern void I2C1_EV_IRQHandler(void);
extern void I2C1_ER_IRQHandler(void);
extern void DMA1_Stream1_IRQHandler(void);
extern void DMA1_Stream5_IRQHandler(void);
extern void DMA1_Transfer_Complete_Callback(void);
extern void DMA1_Transfer_Error_Callback(void);
extern void Handle_I2C_Master(uint8_t addr , uint8_t *pTransmitBuffer,
		__IO uint8_t ubNbDataToTransmit);
