/*
 ===========================================================================================================================================================================
																																			SOURCE FILE
																																			MPU-6050 DRIVER
																																			NUCLEO L476RG
																																			MICHAL KRUK

  ===========================================================================================================================================================================
*/ 


/* --------------------> INCLUDES */
#include "mpu-6050.h"

/* -------------------->  HANDLE_STRUCTUREs */
	I2C_HandleTypeDef I2C1_HandleStruct;
/* --------------------> VARIABLES */


/* --------------------> FUNCTIONS */

uint8_t i2c1_init(void){
	
	//zmienna do zwracania statusu funkcji
	uint8_t i2c_status;
	
	//inicjalizacja struktur od GPIO
	GPIO_InitTypeDef     GPIO_InitStruct;
	
	i2c_status = I2C_INIT_ERROR;
	
		//Enable Clock for GPIOB
		__HAL_RCC_GPIOB_CLK_ENABLE();
		//Enable Clock for I2C 1
		__HAL_RCC_I2C1_CLK_ENABLE();
	
		//GPIO Configuration 
		
				/* Configure GPIO as I2C1_SDA */
				GPIO_InitStruct.Pin = GPIO_PIN_7;
				GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
				GPIO_InitStruct.Pull = GPIO_PULLUP;
				GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
				GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
				HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
			
				/* Configure GPIO as I2C1_SCL */
				GPIO_InitStruct.Pin = GPIO_PIN_6;
				GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
				GPIO_InitStruct.Pull = GPIO_PULLUP;
				GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
				GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
				HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
				//Priorytet przerwania
				
		//I2C Configuration
				
				I2C1_HandleStruct.Instance 		= I2C1;
				I2C1_HandleStruct.Init.Timing =	0x00000000;
				I2C1_HandleStruct.Init.OwnAddress1 = 0;
				I2C1_HandleStruct.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
				I2C1_HandleStruct.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
				I2C1_HandleStruct.Init.OwnAddress2 = 0;
				I2C1_HandleStruct.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
				I2C1_HandleStruct.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
				
				i2c_status = HAL_I2C_Init(&I2C1_HandleStruct);
				
				//Configure Analogue filter
				HAL_I2CEx_AnalogFilter_Config(&I2C1_HandleStruct, I2C_ANALOGFILTER_ENABLED);
				
				return i2c_status;
}


uint8_t i2c1_test(void){
	uint8_t i2c1_device;
	i2c1_device = HAL_I2C_IsDeviceReady(&I2C1_HandleStruct, 0x69 , 10,0);
	
	return i2c1_device;
	
}


uint8_t mpu_6050_read_AX(void){
	
			uint8_t *buf;
			HAL_I2C_Mem_Read(&I2C1_HandleStruct, 0x69, 0x3B, 256, buf, 16,100);
			
			return *buf;
}
