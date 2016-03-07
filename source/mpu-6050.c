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
volatile uint8_t recive_stat;
volatile uint8_t buf1_vol[16];
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
				GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
				GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
				HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
			
				/* Configure GPIO as I2C1_SCL */
				GPIO_InitStruct.Pin = GPIO_PIN_6;
				GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
				GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
				GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
				HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
				//Priorytet przerwania
				
		//I2C Configuration
				
				I2C1_HandleStruct.Instance 		= I2C1;
				//konfigurqacja rejestru timing, f I2C , rise and fall time 
				I2C1_HandleStruct.Init.Timing =	0x00702991; //100kHz 0x30A54E69
				I2C1_HandleStruct.Init.OwnAddress1 = 0x0;	//Own Address potrzebne sa do pracy w trybie slave mode.
				I2C1_HandleStruct.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
				I2C1_HandleStruct.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
				I2C1_HandleStruct.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
				I2C1_HandleStruct.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
				I2C1_HandleStruct.Init.NoStretchMode = I2C_NOSTRETCH_DISABLED;
				
				i2c_status = HAL_I2C_Init(&I2C1_HandleStruct);
							
				//Configure Analogue filter (Filtry szumowe musza byc zawsze skonfigurowane przed wlaczniem I2C
				HAL_I2CEx_AnalogFilter_Config(&I2C1_HandleStruct, I2C_ANALOGFILTER_ENABLED);
				
				
				__HAL_I2C_ENABLE(&I2C1_HandleStruct);	
				return i2c_status;
				
				  /* Peripheral interrupt init*/
//				HAL_NVIC_SetPriority(I2C1_EV_IRQn, 0, 0);
//				HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
//				HAL_NVIC_SetPriority(I2C1_ER_IRQn, 0, 0);
//				HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
}


uint8_t i2c1_test(void){
	uint8_t i2c1_device;

	i2c1_device = HAL_I2C_IsDeviceReady(&I2C1_HandleStruct, 0x3D , 10,100);


	return i2c1_device;
	
}


uint8_t mpu_6050_read_AX(void){
	
			uint8_t *buf;
			HAL_I2C_Mem_Read(&I2C1_HandleStruct, 0x3D, 0x75, 16, buf, 16,100);
			
			return *buf;
}

void recive_test(void){
	uint8_t buf1[16];
	recive_stat =	HAL_I2C_Mem_Read(&I2C1_HandleStruct, 0x3D, 0x03, 1, buf1, 1,100);
	*buf1_vol = (*buf1<<8);
	HAL_I2C_Mem_Read(&I2C1_HandleStruct, 0x3D, 0x04, 1, buf1, 1,100);
	*buf1_vol = (*buf1<<0);
		//HAL_I2C_Master_Receive(&I2C1_HandleStruct, 0xD3,buf1,8,100);
		//HAL_I2C_Master_Transmit(&I2C1_HandleStruct, 0xD3,0,0,100);
	
}
