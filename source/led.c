
/*  ===========================================================================================================================================================================
																																										LED DRIVER 
																																										SOURCE FILE
																																										MICHAL KRUK
    ===========================================================================================================================================================================
*/



/* -----------------------> includes */
#include "led.h"

/* -----------------------> variables*/
/* -----------------------> macros*/

/* -----------------------> funcktions */ 

/*
 ===========================================================================================================================================================================

																																			inicjalizacja odpowiedniego portu GPIO

  ===========================================================================================================================================================================
*/ 
void led_port_init(void)
{
		GPIO_InitTypeDef    GPIO;
	
	// set RCC for GPIOI
	__HAL_RCC_GPIOA_CLK_ENABLE();				
	
	// set GPIO pin 
	GPIO.Pin = GPIO_PIN_5;
	// set GPIO mode
	GPIO.Mode = GPIO_MODE_OUTPUT_PP;
	//
	GPIO.Pull = GPIO_PULLUP;
	//
	GPIO.Speed = GPIO_SPEED_FAST;
	
	//przesyBanie inicjalizacji 
	HAL_GPIO_Init(GPIOA, &GPIO);
}

/*
 ===========================================================================================================================================================================

																																					Zapalanie diody
	
  ===========================================================================================================================================================================
*/ 
void ledOn( void )
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
}

/*
 ===========================================================================================================================================================================

																																						Gaszenie diody

  ===========================================================================================================================================================================
*/ 
void ledOff( void )
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
	
}

/*
 ===========================================================================================================================================================================

																																							Miganie Dioda

  ===========================================================================================================================================================================
*/ 
void ledToggle( void)
{
	HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);

}

/*
 ===========================================================================================================================================================================

																																							KONIEC PLIKU

  ===========================================================================================================================================================================
*/ 
