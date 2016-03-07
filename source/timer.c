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

/* bufory zbierajace dane z GPS */
extern volatile uint8_t buf_usart1[1000];
extern volatile uint8_t buf_usart3[1000];

/* zmienne od obliczania obciazenia uC */
volatile float procent;
char buf_procent[16];
uint8_t obc;
volatile float procent_priv;
//odniesienie to wartosc inkrementowanej zmiennej po czasie 1 [s]
uint32_t odniesienie = 7968310;

/* ====================================*/
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
				HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
				HAL_NVIC_EnableIRQ(TIM2_IRQn);
	
				/* wypelnianie struktury do inicjalizacji */
				TIM2_HandleStruct.Instance = TIM2;
				TIM2_HandleStruct.Init.CounterMode = TIM_COUNTERMODE_UP;
				TIM2_HandleStruct.Init.Prescaler = 20000 - 1;
				TIM2_HandleStruct.Init.Period = 4000  - 1;
	
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
		if(__HAL_TIM_GET_FLAG(&TIM2_HandleStruct, TIM_SR_UIF)){
				__HAL_TIM_CLEAR_FLAG(&TIM2_HandleStruct, TIM_SR_UIF);

				ledToggle();
				
			  /* procedura przekazywania zmiennej do obliczania obciazenia uC */
				procent_priv = procent;
				procent = 0;
			//	obciazenie_uC();
				/* ============================================================= */
			}
	
}
		/*
// ===========================================================================================================================================================================

//																							Funkcja obliczajaca i wyswietlajaca obciazenie uC

//  ===========================================================================================================================================================================
*/

void obciazenie_uC(void){
				/* wyliczanie procent obciazenia uC */
				obc = (100 - ((procent_priv*100)/odniesienie));
				/* konwersja obc do bufora znakowego */
				itoa(obc,buf_procent,10);
				/*wyswietlanie wyniku obciazenia */	
				usart2_WriteS("\n\r--Wykorzystanie procesora: ");
				usart2_WriteS(buf_procent);
				usart2_WriteS(" % \n\r");
}
/*
// ===========================================================================================================================================================================

//																																								KONIEC PLIKU

//  ===========================================================================================================================================================================
*/
