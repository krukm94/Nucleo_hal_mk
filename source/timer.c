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

/* ---------------------> FUNCTIONS */

/* ---------------------> VARIABLES */


/* zmienne od obliczania obciazenia uC */
//volatile float procent;
//char buf_procent[16];
//uint8_t obc;
//volatile float procent_priv;
//odniesienie to wartosc inkrementowanej zmiennej po czasie 1 [s]
//uint32_t odniesienie = 7968310;


/* zmienne do mierzenia czasu przy pomocy TIM5 */
volatile uint32_t tim5_updates;									//ilosc przepelnien timera
volatile uint16_t tim5_cnt;											//wartosc cnt timera

/* ====================================*/

/* ---------------------> Deklaracja uchwytów */

	TIM_HandleTypeDef			TIM2_HandleStruct;
	TIM_HandleTypeDef			TIM5_HandleStruct;
	TIM_HandleTypeDef			TIM3_HandleStruct;

// ===========================================================================================================================================================================

//																						INICJALIZACJA TIM 2

//  ===========================================================================================================================================================================

uint8_t tim2_init(void){
		
		/* zmienna zwracana przez funkcje */
		uint8_t tim2_return;
		tim2_return = TIM_INIT_ERROR;
		
		/* ENABLE CLOCK FOR TIM1 */
		__HAL_RCC_TIM2_CLK_ENABLE();

		/* wypelnianie struktury do inicjalizacji */
		TIM2_HandleStruct.Instance = TIM2;
		TIM2_HandleStruct.Init.CounterMode = TIM_COUNTERMODE_UP;
		TIM2_HandleStruct.Init.Prescaler = 20000 - 1;
		TIM2_HandleStruct.Init.Period = 4000  - 1;

		// INIT OF TIM2
		tim2_return =	HAL_TIM_Base_Init(&TIM2_HandleStruct);

		// ENABLE TIM2
		__HAL_TIM_ENABLE(&TIM2_HandleStruct);
		
		/* Ustawienie Nvic */
		HAL_NVIC_SetPriority(TIM2_IRQn, 0, 2);
		HAL_NVIC_EnableIRQ(TIM2_IRQn);
		
		/*Wlaczenie przerwan od TIM2 */
		__HAL_TIM_ENABLE_IT(&TIM2_HandleStruct, TIM_IT_UPDATE);
			
		return tim2_return;
}

/*
// ===========================================================================================================================================================================

//																							PRZERWANIE OD TIM 2

//  ===========================================================================================================================================================================
*/

// Przerwania z timera ustawione na co 1 s
void TIM2_IRQHandler(void)
{		
		if(__HAL_TIM_GET_FLAG(&TIM2_HandleStruct, TIM_SR_UIF)){
				__HAL_TIM_CLEAR_FLAG(&TIM2_HandleStruct, TIM_SR_UIF);

				
				ledToggle();

			  /* procedura przekazywania zmiennej do obliczania obciazenia uC */
			//	procent_priv = procent;
			//	procent = 0;
			//	obciazenie_uC();
				/* ============================================================= */
			}
	
}

// ===========================================================================================================================================================================

//																						INICJALIZACJA TIM 3
																							//do wyzwalania

//  ===========================================================================================================================================================================

uint8_t tim3_init(void){
		
		/* zmienna zwracana przez funkcje */
		uint8_t tim3_return;
		tim3_return = TIM_INIT_ERROR;
		
		/* ENABLE CLOCK FOR TIM3 */
		__HAL_RCC_TIM3_CLK_ENABLE();

		/* wypelnianie struktury do inicjalizacji */
		TIM3_HandleStruct.Instance = TIM3;
		TIM3_HandleStruct.Init.CounterMode = TIM_COUNTERMODE_UP;
		TIM3_HandleStruct.Init.Prescaler = 20000 - 1;
		TIM3_HandleStruct.Init.Period = 400  - 1;		//Przerwania co 100 ms
		

		// INIT OF TIM3
		tim3_return =	HAL_TIM_Base_Init(&TIM3_HandleStruct);

		// ENABLE TIM3
		__HAL_TIM_ENABLE(&TIM3_HandleStruct);
		
		/* Ustawienie Nvic */
		HAL_NVIC_SetPriority(TIM3_IRQn, 0, 2);
		HAL_NVIC_EnableIRQ(TIM3_IRQn);
		
		/*Wlaczenie przerwan od TIM3 */
		__HAL_TIM_ENABLE_IT(&TIM3_HandleStruct, TIM_IT_UPDATE);
			
		return tim3_return;
}

/*
// ===========================================================================================================================================================================

//																							PRZERWANIE OD TIM 3

//  ===========================================================================================================================================================================
*/

void TIM3_IRQHandler(void){
		
			if(__HAL_TIM_GET_FLAG(&TIM3_HandleStruct, TIM_SR_UIF)){
				__HAL_TIM_CLEAR_FLAG(&TIM3_HandleStruct, TIM_SR_UIF); 
			//Insert code
			nRF_recive();
			}
}

/*
// ===========================================================================================================================================================================

//																							TIM 3 CALLBACK

//  ===========================================================================================================================================================================
*/



/*
// ===========================================================================================================================================================================

																							  Inicjalizacja TIM 5 do pomiaru czasu
																								That timer is for time measurment

																								TIM 5 32b APB1 max 80 MHz

																								0,1862645 ps / LSB 

//  ===========================================================================================================================================================================
*/
uint8_t tim5_init(void){
	
		/* zmienna zwracana przez funkcje */
		uint8_t tim5_return;
		tim5_return = TIM_INIT_ERROR;
		
		/* ENABLE CLOCK FOR TIM5 */
		__HAL_RCC_TIM5_CLK_ENABLE();

		/* wypelnianie struktury do inicjalizacji */
		TIM5_HandleStruct.Instance = TIM5;
		TIM5_HandleStruct.Init.CounterMode = TIM_COUNTERMODE_UP;
		TIM5_HandleStruct.Init.Prescaler = 1; // Przerwania co 0,8 ms	
		TIM5_HandleStruct.Init.Period 	 = 64000 - 1;	// Nie ustawiajac Period TIM nie dziala poprawnie

		// INIT OF TIM5
		tim5_return =	HAL_TIM_Base_Init(&TIM5_HandleStruct);
		
		// IF INIT ERROR
		if(tim5_return != TIM_INIT_OK) {
			usart2_WriteS("\n\r####: ERROR IN TIM5 INIT \n\r");
			error_function();
		}
		
		// ENABLE TIM5
		__HAL_TIM_ENABLE(&TIM5_HandleStruct);
		
		/* Ustawienie Nvic */
		HAL_NVIC_SetPriority(TIM5_IRQn, 0, 4);
		HAL_NVIC_EnableIRQ(TIM5_IRQn);
		
		/*Wlaczenie przerwan od TIM5 */
		__HAL_TIM_ENABLE_IT(&TIM5_HandleStruct, TIM_IT_UPDATE);
			
		return tim5_return;
}

/*
// ===========================================================================================================================================================================

//																							PRZERWANIE OD TIM 5

//  ===========================================================================================================================================================================
*/

// Przerwania z timera ustawione na co 1 s
void TIM5_IRQHandler(void)
{		
				HAL_TIM_IRQHandler(&TIM5_HandleStruct);
}							// 	end of TIM5_IRQHandler(void)


/*
// ===========================================================================================================================================================================

//																							CALLBACK

//  ===========================================================================================================================================================================
*/

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	
				tim5_updates++;
}		// end of void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)

/*
// ===========================================================================================================================================================================

//																							Funkcja rozpoczynajaca pomiar czasu

//  ===========================================================================================================================================================================
*/

void start_tim_meas(void){
		
	//Reset variables
	tim5_updates = 0;
	tim5_cnt = 0;
	

}							//end of void start_tim_meas(void)

/*
// ===========================================================================================================================================================================

//																							Funkcja lapiaca czas (zwraca wynik pomiaru czasu)

//  ===========================================================================================================================================================================
*/

double get_tim_meas(uint8_t display_result){

	double time_meas;
	double updates_quantity;												//Ilosc przepelnien
	double cnt_quantity;														//Wartosc rejestru CNT
	
	__HAL_TIM_DISABLE(&TIM5_HandleStruct);
	
	time_meas = 0.0;
	
	//get tim5 updates quantity
	updates_quantity = ((double)(tim5_updates * 0.8));
	
	//get tim5 counter value
	cnt_quantity = (double)(timeLSB * __HAL_TIM_GET_COUNTER(&TIM5_HandleStruct));
	
	time_meas = (updates_quantity + cnt_quantity);

	//Zerowanie rejestru CNT po dokonaniu obliczen.
	__HAL_TIM_SET_COUNTER(&TIM5_HandleStruct, 0);
	
	__HAL_TIM_ENABLE(&TIM5_HandleStruct);
	
			// Jezelie display_result = 1 wyswietl wynik
			if(display_result){
				char tim_measurment_buf[40];																					//Deklaracja bufora
				sprintf(tim_measurment_buf , "\n\r\n\r TIME MEASURMENT RESULT: %f [ns] " , time_meas);
				usart2_WriteS(tim_measurment_buf);
				
			}
	return time_meas;

}             // end of
/*
// ===========================================================================================================================================================================

//																							Funkcja obliczajaca i wyswietlajaca obciazenie uC

//  ===========================================================================================================================================================================
*/

void obciazenie_uC(void){
				/* wyliczanie procent obciazenia uC */
			//	obc = (100 - ((procent_priv*100)/odniesienie));
				/* konwersja obc do bufora znakowego */
			//	itoa(obc,buf_procent,10);
				/*wyswietlanie wyniku obciazenia */	
			//	usart2_WriteS("\n\r--Wykorzystanie procesora: ");
			//	usart2_WriteS(buf_procent);
			//	usart2_WriteS(" % \n\r");
}
/*
// ===========================================================================================================================================================================

//																							KONIEC PLIKU

//  ===========================================================================================================================================================================
*/
