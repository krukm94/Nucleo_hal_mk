/*
=================================================================================================================================
																													NUCLEO L476RG  
																													MCU: STM32L476RGT6U

																													Michal Kruk
																													21.12.2015r

=================================================================================================================================
*/

#include "init.h"

/* ------------------------> global variables */


/* zmienna do wyliczania obciazenia uC */
extern volatile float procent;
volatile uint8_t i2c1_response;

int main(void){
	
	uint16_t acc_X,acc_Y,acc_Z,mag_X,mag_Z,mag_Y,gyro_X,gyro_Z,gyro_Y;
	char i2c1_buf[16];
	char acc_X_buf[16];
	char acc_Y_buf[16];
	char acc_Z_buf[16];
	char mag_X_buf[16];
	char mag_Y_buf[16];
	char mag_Z_buf[16];
	char gyro_X_buf[16];
	char gyro_Y_buf[16];
	char gyro_Z_buf[16];
	/*wywolanie hala stm */
	HAL_Init();
	/*wywolanie inicjalizacji hala */
	HAL ->Init();
		//ustawienie trybu ciaglego
//		const_mode();
			
			//	i2c1_response = HAL -> i2c1_is_device_ready(0xD7);
				itoa(i2c1_response, i2c1_buf , 10);
				HAL -> usart2_WriteS("\n\rI2C RESPONSE: ");
				HAL -> usart2_WriteS(i2c1_buf);

				lsm_config();
			/* -------------------------------------> main loop */
			while(1){
				HAL_Delay(200);
				
				
				acc_X = accelerometer_x();
				acc_Y = accelerometer_y();
				acc_Z = accelerometer_z();			
				
				mag_X = magnetometr_x();
				mag_Y = magnetometr_y();
				mag_Z = magnetometr_z();
				
				gyro_X = gyro_x();
				gyro_Y = gyro_y();
				gyro_Z = gyro_z();
				
				itoa(acc_X,acc_X_buf,10);
				itoa(acc_Y,acc_Y_buf,10);
				itoa(acc_Z,acc_Z_buf,10);
				
				itoa(mag_X,mag_X_buf,10);
				itoa(mag_Y,mag_Y_buf,10);
				itoa(mag_Z,mag_Z_buf,10);
				
				itoa(gyro_X,gyro_X_buf,10);
				itoa(gyro_Y,gyro_Y_buf,10);
				itoa(gyro_Z,gyro_Z_buf,10);
				
				tr_cls(0);
				tr_locate(0,0);
				HAL->usart2_WriteS("\n\r----ACCELEROMETER----");
				
				HAL -> usart2_WriteS("\n\r\n\r --> X: ");
				HAL -> usart2_WriteS(acc_X_buf);
				
				HAL -> usart2_WriteS(" [] \n\r --> Y: ");
				HAL -> usart2_WriteS(acc_Y_buf);
				
				HAL -> usart2_WriteS(" [] \n\r --> Z: ");
				HAL -> usart2_WriteS(acc_Z_buf);
				HAL -> usart2_WriteS(" []");
				
				HAL->usart2_WriteS("\n\r\n\r----MAGNETOMETER----");
				
				HAL -> usart2_WriteS("\n\r\n\r --> X: ");
				HAL -> usart2_WriteS(mag_X_buf);
				
				HAL -> usart2_WriteS(" [] \n\r --> Y: ");
				HAL -> usart2_WriteS(mag_Y_buf);
				
				HAL -> usart2_WriteS(" [] \n\r --> Z: ");
				HAL -> usart2_WriteS(mag_Z_buf);
				HAL -> usart2_WriteS(" []");
				
				
				HAL->usart2_WriteS("\n\r\n\r----GYROSCOPE----");
				
				HAL -> usart2_WriteS("\n\r\n\r --> X: ");
				HAL -> usart2_WriteS(gyro_X_buf);
				
				HAL -> usart2_WriteS(" [] \n\r --> Y: ");
				HAL -> usart2_WriteS(gyro_Y_buf);
				
				HAL -> usart2_WriteS(" [] \n\r --> Z: ");
				HAL -> usart2_WriteS(gyro_Z_buf);
				HAL -> usart2_WriteS(" []");
				/* zmienna do wyliczania obciazenia uC */
				procent++;

			}
}
/*
=================================================================================================================================
																													

																													END OF FILE
																													

=================================================================================================================================
*/
