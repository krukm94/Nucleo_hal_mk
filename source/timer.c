/*
 ===========================================================================================================================================================================
																																			SOURCE FILE
																																			TIMER DRIVER
																																			NUCLEO L476RG
																																			MICHAL KRUK

  ===========================================================================================================================================================================
*/ 

/* ---------------------> INCLUDES */
#include "timer.h"
/* ---------------------> MACROS */
#define TIM_INIT_ERROR 2;
/* ---------------------> FUNCTIONS */

/* ---------------------> VARIABLES */
uint16_t diode_cnt;
uint32_t gps_disp_cnt;
extern volatile uint8_t buf_usart1[1000];
extern volatile uint8_t buf_usart3[1000];

volatile uint16_t uart4_cr1;

/* ---------------------> Deklaracja uchwytów */
	TIM_HandleTypeDef			TIM2_HandleStruct;
/*
// ===========================================================================================================================================================================

//																																						INICJALIZACJA TIM 2

//  ===========================================================================================================================================================================
*/
uint8_t tim2_init(void){
		
		/* zmienna zwracana przez funkcje */
		uint8_t tim2_return;
		tim2_return = TIM_INIT_ERROR;
		
		/* ENABLE CLOCK FOR TIM1 */
		__HAL_RCC_TIM2_CLK_ENABLE();
				/* Ustawienie Nvic */
				NVIC_SetPriority(TIM2_IRQn, 0);
				NVIC_EnableIRQ(TIM2_IRQn);
	
				/* wypelnianie struktury do inicjalizacji */
				TIM2_HandleStruct.Instance = TIM2;
				TIM2_HandleStruct.Init.CounterMode = TIM_COUNTERMODE_UP;
				TIM2_HandleStruct.Init.Prescaler = 20000 - 1;
				TIM2_HandleStruct.Init.Period = 2  - 1;
				// INIT OF TIM2
				
				tim2_return =	HAL_TIM_Base_Init(&TIM2_HandleStruct);
	
				// ENABLE TIM2
				__HAL_TIM_ENABLE(&TIM2_HandleStruct);
				/*Wlaczenie przerwan od TIM2 */
				__HAL_TIM_ENABLE_IT(&TIM2_HandleStruct, TIM_IT_UPDATE);
		return tim2_return;
}
/*
// ===========================================================================================================================================================================

//																																						PRZERWANIE OD TIM 2

//  ===========================================================================================================================================================================
*/

void TIM2_IRQHandler(void)
{		
		if(TIM2 -> SR & TIM_SR_UIF){
			TIM2 -> SR &=~ TIM_SR_UIF;
			
			/* miganie dioda*/
			diode_cnt++;
			gps_disp_cnt++;
			if(diode_cnt == 2000){
				ledToggle();
				diode_cnt = 0;

			}
					if(gps_disp_cnt == 2000){

						gps_disp_cnt = 0;
					}
		}
}
		
/*
// ===========================================================================================================================================================================

//																																								KONIEC PLIKU

//  ===========================================================================================================================================================================
*/
