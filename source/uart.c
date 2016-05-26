/*
 ===========================================================================================================================================================================
																																			SOURCE FILE
																																			UART DRIVER
																																			NUCLEO L476RG
																																			MICHAL KRUK

  ===========================================================================================================================================================================
*/ 

/* ------------------->	includes*/
#include "uart.h"

/* -------------------> variables*/

/* ========= zmienne do callback'ow ======== */
volatile uint8_t temp;
//static void (*uartRE)(char data);


/* ========= zmienne do usart1 (GPS FGPMMOPA6B) ======== */
uint8_t usart1_rx;
int cnt_usart1 = 0;
volatile uint8_t buf_usart1[1000];
//volatile uint8_t buf_usart1_save[1000];
uint8_t last_line_usart1 = 0;

/* ========= zmienne do usart3 (GPS UP-500)    ======== */
uint8_t usart3_rx;
int cnt_usart3 = 0;
volatile uint8_t buf_usart3[1000];
//volatile uint8_t buf_usart3_save[1000];
uint8_t last_line_usart3 = 0;




/* deklaracja uchwytów */
	UART_HandleTypeDef  USART1_HandleStruct;
	
	UART_HandleTypeDef  USART2_HandleStruct; // Kiedy uzywalem uchwytu USART_HandleTypeDef to nie dzialaly przerwania.
	
	UART_HandleTypeDef  USART3_HandleStruct;
	
	UART_HandleTypeDef  UART4_HandleStruct;
	
	UART_HandleTypeDef  UART5_HandleStruct;



/*
// ===========================================================================================================================================================================

//																																						FUNKCJE DLA USARTU 1

//  ===========================================================================================================================================================================
*/ 

#ifdef USART1_ON
uint8_t usart1_init(void) 
{

	
	//zmienna do zwracania statusu funkcji
	uint8_t usart_status;
	
	//inicjalizacja struktur od GPIO
	GPIO_InitTypeDef     GPIO_InitStruct;
	
	usart_status = UART_INIT_ERROR;
 
/* Enable GPIO clock */
	__HAL_RCC_GPIOA_CLK_ENABLE();

 
// Enable clock for USART1 peripheral
	__HAL_RCC_USART1_CLK_ENABLE();
	

	
/* Configure USART Tx as alternate function */
		GPIO_InitStruct.Pin = GPIO_PIN_9;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
/* Configure USART Rx as alternate function */
		GPIO_InitStruct.Pin = GPIO_PIN_10;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		//Priorytet przerwania
		
		NVIC_SetPriority(USART1_IRQn, 2);

		NVIC_EnableIRQ(USART1_IRQn);

//Handle
		USART1_HandleStruct.Instance = USART1;
		USART1_HandleStruct.Init.BaudRate = BAUDRATE_USART1;
		USART1_HandleStruct.Init.StopBits = USART_STOPBITS_1;
		USART1_HandleStruct.Init.Parity = USART_PARITY_NONE;
		USART1_HandleStruct.Init.Mode = USART_MODE_TX_RX;
		
	
//Init
		usart_status = HAL_UART_Init(&USART1_HandleStruct);
	
		
//USART2 enable	
		__HAL_UART_ENABLE(&USART1_HandleStruct);

			#ifdef USART1_IT_RX_ON
			USART1 -> CR1 |= USART_CR1_RXNEIE;
			#endif
			
		return usart_status;
}
#endif

/*
 ===========================================================================================================================================================================

																																						WYSYLANIE CHARA USART 1

  ===========================================================================================================================================================================
*/ 
void usart1_Write(char data)
{	
	while(!(__HAL_USART_GET_FLAG(&USART1_HandleStruct, USART_FLAG_TXE)));	
	USART1 ->TDR = data;
}
/*
 ===========================================================================================================================================================================

																																						WYSYLANIE STRINGU  USART 1

  ===========================================================================================================================================================================
*/ 

void usart1_WriteS(char *s)
{
	while(*s)
	{
		while(!(__HAL_USART_GET_FLAG(&USART2_HandleStruct, USART_FLAG_TC)));
		usart1_Write(*s++);
		
	}
}
/*
 ===========================================================================================================================================================================

																																			 FUNKCJa PRZERWANIA USART 1

  ===========================================================================================================================================================================
*/ 

void USART1_IRQHandler(void)
{		
		if(USART1 -> ISR & USART_FLAG_RXNE){		//sprawzanie flagi RXNE
				usart1_rx = USART1 -> RDR;
					usart1_odczyt(usart1_rx);
		}
}


/*
 ===========================================================================================================================================================================

																								funckja zapisuje osatnio odebrane informacjie do zmiennej globalnej

  ===========================================================================================================================================================================
*/ 
void usart1_odczyt(uint8_t rx){
	
		buf_usart1[cnt_usart1] = rx;

	
		//Przeszukuje odebrany bufor szukajac frazy "GTV"
		if(buf_usart1[cnt_usart1] == 71){	//G
			if(buf_usart1[cnt_usart1 - 1] == 84){	//T
				if(buf_usart1[cnt_usart1 - 2] == 86){	//V

								last_line_usart1 = 1; //flaga wykrycia ostatniej lini
				}
			}
		}

		
		// wyszukiwanie znaku New Line		
		if(last_line_usart1){
				if(buf_usart1[cnt_usart1] == 10){
					
					uint16_t i;
					// - 1 poniewaz na koncu funkcji jest cnt++ a chcemy wejsc wchodizc w funkcjie z wartoscia 0;
					cnt_usart1 = -1;
					last_line_usart1 = 0;
				
					//uart4_WriteS(buf_usart1);
					// niezbedne wyczyszczenie smieci z buforu
						for(i=0;i<1000;i++){
							buf_usart1[i] = 0;
						}
				}
		}
		cnt_usart1++;

}

/*
// ===========================================================================================================================================================================

//																																						KONIEC FUNKCJI DLA UsART 1

//  ===========================================================================================================================================================================
*/ 




/*
 ===========================================================================================================================================================================

																																							FUNKCE DLA USART 2

  ===========================================================================================================================================================================
*/ 

/*
 ===========================================================================================================================================================================

																																							INICJALIZACJA USART 2 

  ===========================================================================================================================================================================
*/ 

#ifdef USART2_ON
uint8_t usart2_init(void) 
{
	//zmienna do zwracania statusu funkcji
	uint8_t usart_status;
	
	//inicjalizacja struktur od GPIO
	GPIO_InitTypeDef     GPIO_InitStruct;
	
	usart_status = UART_INIT_ERROR;
	
/* Enable GPIO clock */
	__HAL_RCC_GPIOA_CLK_ENABLE();

// Enable clock for USART1 peripheral
	__HAL_RCC_USART2_CLK_ENABLE();
	
/* Configure USART Tx as alternate function */
		GPIO_InitStruct.Pin = GPIO_PIN_2;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
/* Configure USART Rx as alternate function */
		GPIO_InitStruct.Pin = GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		
		//Priorytet przerwania
	//	HAL_NVIC_SetPriority(USART2_IRQn , 0 , 1);
	//	HAL_NVIC_EnableIRQ(USART2_IRQn);
		
//Handle
		USART2_HandleStruct.Instance = USART2;
		USART2_HandleStruct.Init.BaudRate = BAUDRATE_USART2;
		USART2_HandleStruct.Init.StopBits = USART_STOPBITS_1;
		USART2_HandleStruct.Init.Parity = USART_PARITY_NONE;
		USART2_HandleStruct.Init.Mode = USART_MODE_TX_RX;
		
//Init
		usart_status = HAL_UART_Init(&USART2_HandleStruct);
	
//USART2 enable	
		__HAL_UART_ENABLE(&USART2_HandleStruct);

		//Przerwania od RX ON
			#ifdef USART2_IT_RX_ON
		//	USART2 -> CR1 |= USART_CR1_RXNEIE;
			#endif
			
		return usart_status;
}

#endif
/*
 ===========================================================================================================================================================================

																																						WYSYLANIE CHARA USART 2

  ===========================================================================================================================================================================
*/ 
void usart2_Write(char data)
{	
	while(!(__HAL_USART_GET_FLAG(&USART2_HandleStruct, USART_FLAG_TXE)));	
	USART2 ->TDR = data;
}
/*
 ===========================================================================================================================================================================

																																						Funkcja z CALLBACKIEM USART 2
  ===========================================================================================================================================================================
*/ 

//void setIrqFunc(void (*pFunc)(char data))
//{
//	if(pFunc)
//	{
//		uartRE = pFunc;
//		
//		__HAL_USART_ENABLE_IT(&USART_HandleStruct,USART_IT_RXNE);
//		//USART1 ->CR1 |= USART_CR1_RXNEIE;
//	}
//	else
//	{
//		__HAL_USART_DISABLE_IT(&USART_HandleStruct,USART_IT_RXNE);
//		//USART1 ->CR1 &= ~USART_CR1_RXNEIE;
//		
//		uartRE = NULL;
//	}
//}


//void setIrqFunc(void (*pFunc)(char data))
//{
//	if(pFunc)
//	{
//		USART1 ->CR1 |= USART_CR1_RXNEIE;
//	}
//	else
//	{
//		USART1 ->CR1 &= ~USART_CR1_RXNEIE;
//		
//		uartRE = NULL;
//	}
//}

/*
 ===========================================================================================================================================================================

																																			 FUNKCJa PRZERWANIA USART 2

  ===========================================================================================================================================================================
*/ 

void USART2_IRQHandler(void)
{		

}
/*
 ===========================================================================================================================================================================

																																						WYSYLANIE STRINGU  USART2

  ===========================================================================================================================================================================
*/ 
void usart2_WriteS(char *s)
{
	while(*s)
	{
		while(!(__HAL_USART_GET_FLAG(&USART2_HandleStruct, USART_FLAG_TC)));
		usart2_Write(*s++);
		
	}
}


/*
 ===========================================================================================================================================================================

																																				KONIEC FUNKCJI DLA USART 2

  ===========================================================================================================================================================================
*/ 
	
	
	
/*
// ===========================================================================================================================================================================

//																																						FUNKCJE DLA USARTU 3

//  ===========================================================================================================================================================================
*/ 
#ifdef USART3_ON
uint8_t usart3_init(void) 
{

	
	//zmienna do zwracania statusu funkcji
	uint8_t usart_status;

	//inicjalizacja struktur od GPIO
	GPIO_InitTypeDef     GPIO_InitStruct;
	
	usart_status = UART_INIT_ERROR;
 
/* Enable GPIO clock */
	__HAL_RCC_GPIOC_CLK_ENABLE();
 
// Enable clock for USART1 peripheral
	__HAL_RCC_USART3_CLK_ENABLE();
	
	
/* Configure USART Tx as alternate function */
		GPIO_InitStruct.Pin = GPIO_PIN_4;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
/* Configure USART Rx as alternate function */
		GPIO_InitStruct.Pin = GPIO_PIN_5;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
		//Priorytet przerwania
		
		NVIC_SetPriority(USART3_IRQn, 1);
		NVIC_EnableIRQ(USART3_IRQn);

//Handle
		USART3_HandleStruct.Instance = USART3;
		USART3_HandleStruct.Init.BaudRate = BAUDRATE_USART3;
		USART3_HandleStruct.Init.StopBits = USART_STOPBITS_1;
		USART3_HandleStruct.Init.Parity = USART_PARITY_NONE;
		USART3_HandleStruct.Init.Mode = USART_MODE_TX_RX;
		
	
//Init
		usart_status = HAL_UART_Init(&USART3_HandleStruct);
	
		
//USART2 enable	
		__HAL_UART_ENABLE(&USART3_HandleStruct);

			#ifdef USART3_IT_RX_ON
			USART3 -> CR1 |= USART_CR1_RXNEIE;
			#endif
			
		return usart_status;
}
#endif

/*
 ===========================================================================================================================================================================

																																						WYSYLANIE CHARA USART 3

  ===========================================================================================================================================================================
*/ 
void usart3_Write(char data)
{	
	while(!(__HAL_USART_GET_FLAG(&USART3_HandleStruct, USART_FLAG_TXE)));	
	USART3 ->TDR = data;
}
/*
 ===========================================================================================================================================================================

																																						WYSYLANIE STRINGU  USART 3

  ===========================================================================================================================================================================
*/ 

void usart3_WriteS(char *s)
{
	while(*s)
	{
		while(!(__HAL_USART_GET_FLAG(&USART3_HandleStruct, USART_FLAG_TC)));
		usart3_Write(*s++);
		
	}
}
/*
 ===========================================================================================================================================================================

																																			 FUNKCJa PRZERWANIA USART 3

  ===========================================================================================================================================================================
*/ 

void USART3_IRQHandler(void)
{		
		if(USART3 -> ISR & USART_FLAG_RXNE){		//sprawzanie flagi RXNE
				usart3_rx = USART3 -> RDR;
					usart3_odczyt(usart3_rx);
		}
}


/*
 ===========================================================================================================================================================================

																								funckja zapisuje osatnio odebrane informacjie do zmiennej globalnej

  ===========================================================================================================================================================================
*/ 
void usart3_odczyt(uint8_t rx){

		buf_usart3[cnt_usart3] = rx;

	
		//Przeszukuje odebrany bufor szukajac frazy "RMC" (To zawsze ostatnia linia nadawana przez ten GPS)
		if(buf_usart3[cnt_usart3] == 67){	//C
			if(buf_usart3[cnt_usart3 - 1] == 77){	//M
				if(buf_usart3[cnt_usart3 - 2] == 82){	//R

								last_line_usart3 = 1;
				}
			}
		}

		
		// wyszukiwanie znaku New Line		
		if(last_line_usart3){
				if(buf_usart3[cnt_usart3] == 10){
					
					uint16_t i;
					// - 1 poniewaz na koncu funkcji jest cnt++;
					cnt_usart3 = -1;
					last_line_usart3 = 0;
					
					//	usart2_WriteS(buf_usart3);
					// niezbedne wyczyszczenie smieci z buforu
					
						for(i=0;i<1000;i++){
							buf_usart3[i] = 0;
						}

				}
		}
		cnt_usart3++;

}
/*
// ===========================================================================================================================================================================

//																																						KONIEC FUNKCJI DLA UsART 3

//  ===========================================================================================================================================================================
*/ 

/*
 ===========================================================================================================================================================================

																																					FUNKCJE DLA UART 4

  ===========================================================================================================================================================================
*/ 

/*
 ===========================================================================================================================================================================

																																					UART4 INIT

  ===========================================================================================================================================================================
*/ 

#ifdef UART4_ON
uint8_t uart4_init(void) 
{

	
	//zmienna do zwracania statusu funkcji
	uint8_t uart_status;
	//inicjalizacja struktur od GPIO i USART
	GPIO_InitTypeDef     GPIO_InitStruct;

	uart_status = UART_INIT_ERROR;
 
/* Enable GPIO clock */
	__HAL_RCC_GPIOA_CLK_ENABLE();

// Enable clock for UART4 peripheral
	__HAL_RCC_UART4_CLK_ENABLE();
	
/* Configure USART Tx as alternate function */
GPIO_InitStruct.Pin = GPIO_PIN_0;
GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
/* Configure USART Rx as alternate function */
GPIO_InitStruct.Pin = GPIO_PIN_1;
GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
GPIO_InitStruct.Pull = GPIO_PULLUP;
GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

NVIC_SetPriority(UART4_IRQn, 1);
NVIC_EnableIRQ(UART4_IRQn);

//Handle
		UART4_HandleStruct.Instance = UART4;
		UART4_HandleStruct.Init.BaudRate = 115200;
		UART4_HandleStruct.Init.StopBits = UART_STOPBITS_1;
		UART4_HandleStruct.Init.WordLength = UART_WORDLENGTH_8B;
		UART4_HandleStruct.Init.Parity = UART_PARITY_NONE;
		UART4_HandleStruct.Init.Mode = UART_MODE_TX_RX;

//Init
uart_status = HAL_UART_Init(&UART4_HandleStruct);
//UART4 enable
__HAL_UART_ENABLE(&UART4_HandleStruct);


//Wlaczenie przerwan od RX dla UART4
#ifdef UART4_IT_RX_ON
UART4 -> CR1 |= USART_CR1_RXNEIE;
#endif
		return uart_status;
}
#endif
/*
// ===========================================================================================================================================================================

//																																						PRZERWANIE UART4

//  ===========================================================================================================================================================================
*/ 

void UART4_IRQHandler(void)
{		
			if(UART4 -> ISR & USART_FLAG_RXNE){		//sprawzanie flagi RXNE
					usart2_WriteS("elo\n\r");
		}	
}

/*
// ===========================================================================================================================================================================

//																																						WYSYLANIE CHARA UART4

//  ===========================================================================================================================================================================
*/ 

void uart4_Write(char data)
{
	while(!(UART4-> ISR & USART_ISR_TXE)); 
	UART4 ->TDR = data;
}

/*
// ===========================================================================================================================================================================

//																																						WYSYLANIE STRINGU UART 4

//  ===========================================================================================================================================================================
*/ 
void uart4_WriteS(char *s)
{
	while(*s)
	{
		while(!(__HAL_USART_GET_FLAG(&UART4_HandleStruct, USART_FLAG_TC)));
		uart4_Write(*s++);
		
	}
}
/*
 ===========================================================================================================================================================================

																																						KONIEC FUNKCJI DLA UART 4

  ===========================================================================================================================================================================
*/ 

/*
 ===========================================================================================================================================================================

																																						FUNKCJE DLA UART 5

  ===========================================================================================================================================================================
*/ 
#ifdef UART5_ON
uint8_t uart5_init(void) 
{

	
	//zmienna do zwracania statusu funkcji
	uint8_t uart_status;

	//inicjalizacja struktur od GPIO i USART
	GPIO_InitTypeDef     GPIO_InitStruct;
	
		uart_status = UART_INIT_ERROR;
	
/* Enable GPIO clock */
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
 
// Enable clock for UART5 peripheral
	__HAL_RCC_UART5_CLK_ENABLE();
	

	
/* Configure USART Tx as alternate function */
GPIO_InitStruct.Pin = GPIO_PIN_12;
GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
GPIO_InitStruct.Alternate = GPIO_AF8_UART5;
HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
/* Configure USART Rx as alternate function */
GPIO_InitStruct.Pin = GPIO_PIN_2;
GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
GPIO_InitStruct.Alternate = GPIO_AF8_UART5;
HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

NVIC_SetPriority(UART5_IRQn, 1);
NVIC_EnableIRQ(UART5_IRQn);

		UART5_HandleStruct.Instance = UART5;
		UART5_HandleStruct.Init.BaudRate = BAUDRARE_UART5;
		UART5_HandleStruct.Init.StopBits = USART_STOPBITS_1;
		UART5_HandleStruct.Init.Parity = USART_PARITY_NONE;
		UART5_HandleStruct.Init.Mode = USART_MODE_TX_RX;

//Init
uart_status = HAL_UART_Init(&UART5_HandleStruct);
//UART5 enable
__HAL_UART_ENABLE(&UART5_HandleStruct);

//Wlaczenie przerwan od RX dla UART4
#ifdef UART5_IT_RX_ON
UART5 -> CR1 |= USART_CR1_RXNEIE;
#endif
		return uart_status;
}
#endif

/*
// ===========================================================================================================================================================================

//																																						WYSYLANIE CHARA UART 5

//  ===========================================================================================================================================================================
*/ 

void uart5_Write(char data)
{
	while(!(UART5-> ISR & USART_ISR_TXE)); 
	UART5 ->TDR = data;
}

/*
// ===========================================================================================================================================================================

//																																						WYSYLANIE STRINGU UART 5

//  ===========================================================================================================================================================================
*/ 
void uart5_WriteS(char *s)
{
	while(*s)
	{
		while(!(__HAL_USART_GET_FLAG(&UART5_HandleStruct, USART_FLAG_TC)));
		uart5_Write(*s++);
		
	}
}
/*
// ===========================================================================================================================================================================

//																																						KONIEC FUNKCJI DLA UART 5

//  ===========================================================================================================================================================================
*/ 

/*
// ===========================================================================================================================================================================

//																																								KONIEC PLIKU

//  ===========================================================================================================================================================================
*/ 

