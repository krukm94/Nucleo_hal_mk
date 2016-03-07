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
#include "kompas.h"
/* ------------------------> global variables */



/* zmienna do wyliczania obciazenia uC */
extern volatile float procent;

int main(void){
	uint16_t ch_X,ch_Y,ch_Z;
	char ch_X_buf[16];
	char ch_Y_buf[16];
	char ch_Z_buf[16];

	/*wywolanie hala stm */
	HAL_Init();
	/*wywolanie inicjalizacji hala */
	HAL ->Init();
		//ustawienie trybu ciaglego
		const_mode();
			/* -------------------------------------> main loop */
			while(1){
				HAL_Delay(1000);
				
				ch_X = chanel_X();
				ch_Y = chanel_Y();
				ch_Z = chanel_Z();				
				
				itoa(ch_X,ch_X_buf,10);
				itoa(ch_Y,ch_Y_buf,10);
				itoa(ch_Z,ch_Z_buf,10);
				
				tr_cls(0);
				tr_locate(0,0);
				
				HAL -> usart2_WriteS("\n\r\n\r --> X: ");
				HAL -> usart2_WriteS(ch_X_buf);
				
				HAL -> usart2_WriteS(" [deg] \n\r --> Y: ");
				HAL -> usart2_WriteS(ch_Y_buf);
				
				HAL -> usart2_WriteS(" [deg] \n\r --> Z: ");
				HAL -> usart2_WriteS(ch_Z_buf);
				HAL -> usart2_WriteS(" [deg]");
				
				/* zmienna do wyliczania obciazenia uC */
				procent++;

			}
}
/*
=================================================================================================================================
																													

																													END OF FILE
																													

=================================================================================================================================
*/
