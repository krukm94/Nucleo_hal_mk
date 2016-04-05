/*
 ===========================================================================================================================================================================
																																			HEADER FILE
																																			LSM9DS0 DRIVER
																																			NUCLEO L476RG
																																			MICHAL KRUK
 ===========================================================================================================================================================================
*/ 

#ifndef __lsm9ds0_H__
#define __lsm9ds0_H__

// -------------------------> INCLUDES 
#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"
#include "i2c.h"
#include "timer.h"
// -------------------------> MACROS
#define READ_ADR_LSM 				0xD7
#define WRITE_ADR_LSM				0xD6
#define MEMORY_SIZE_LSM 		1

//CTRL_REG1
#define CTRL_REG1_G_ADR			0x20
//Tryby prcy
#define NORMAL_MODE					0x0F

#define GYRO_X_ADR 					0x28
#define GYRO_Y_ADR					0x2A
#define GYRO_Z_ADR 					0x2C
	
#define ACCELEROMETER_X_ADR		0x28
#define ACCELEROMETER_Y_ADR		0x2A
#define ACCELEROMETER_Z_ADR		0x2C

#define MAGNETOMETER_X_ADR	0x08
#define MAGNETOMETER_Y_ADR	0x0A
#define MAGNETOMETER_Z_ADR	0x0C

// -------------------------> FUNCTIONS
uint16_t gyro_x(void);
uint16_t gyro_z(void);
uint16_t gyro_y(void);

uint16_t accelerometer_x(void);
uint16_t accelerometer_z(void);
uint16_t accelerometer_y(void);

uint16_t magnetometr_x(void);
uint16_t magnetometr_z(void);
uint16_t magnetometr_y(void);

void lsm_config(void);

/*
 ===========================================================================================================================================================================
																																			END OF FILE
  ===========================================================================================================================================================================
*/ 

#endif // __kompas_H__
