/*
=================================================================================================================================
																													NUCLEO L476RG  
																													MCU: STM32L476RGT6U

																													Michal Kruk
																													21.12.2015r

=================================================================================================================================
*/

#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"



/* ------------------------> private includes */
#include "hal.h"
#include "mpu-6050.h"
/* ------------------------> global variables */
volatile uint8_t i2c1_init_stat;
volatile uint8_t device_ready;

int main(void){

//  uint8_t buf;
//	char AX[16];
//	char init_stat_buf[16];
//	char device_ready_buf[16];
	
	/*wywolanie hala stm */
	HAL_Init();
	/*wywolanie inicjalizacji hala */
	HAL ->Init();

//		i2c1_init_stat = i2c1_init();
//		
//		device_ready = i2c1_test();
//	
//		
//		itoa(i2c1_init_stat,init_stat_buf,10);
//		itoa(device_ready,device_ready_buf,10);
//	
//		HAL -> usart2_WriteS("\n\r Init: ");
//		HAL -> usart2_WriteS(init_stat_buf);
//		HAL -> usart2_WriteS("\n\r Test: ");
//		HAL -> usart2_WriteS(device_ready_buf);
	


			/* -------------------------------------> main loop */
			while(1){


			}
}

