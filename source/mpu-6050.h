/*
 ===========================================================================================================================================================================
																																			Header FILE
																																			MPU-6050 DRIVER
																																			NUCLEO L476RG
																																			MIROSLAW KARDAS

  ===========================================================================================================================================================================
*/ 


#ifndef __hal_H__
#define __hal_H__

/* --------------------> INCLUDES */
#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"

/* --------------------> MACROS */
#define I2C_INIT_OK 		0x00;
#define I2C_INIT_ERROR 	0x01;

/* --------------------> FUNCTIONS */
uint8_t i2c1_init(void);
uint8_t i2c1_test(void);
uint8_t mpu_6050_read_AX(void);

#endif // __mpu-6050_H__