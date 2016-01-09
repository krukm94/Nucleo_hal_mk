/*
 ===========================================================================================================================================================================
																																			HEADER FILE
																																			HAL DRIVER
																																			NUCLEO L476RG
																																			MICHAL KRUK

  ===========================================================================================================================================================================
*/ 

#ifndef __hal_H__
#define __hal_H__

#include <stdint.h> 
#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"

/* private includes */
#include "led.h"
#include "uart.h"
#include "timer.h"
#include "itoa.h"

typedef struct{
   //system	
   void     (*Init)(void);
	 //led
	 void			(*led_port_init)(void);
	 void			(*ledOn)				(void);
	 void			(*ledOff)				(void);
	 void 		(*ledToggle)		(void);
	 //usart1
	 uint8_t	(*usart1_init)		(void);
	 void			(*usart1_Write)		(char data);
	 void			(*usart1_WriteS)	(char *s);
	 //usart2
	 uint8_t	(*usart2_init)		(void);
	 void			(*usart2_Write)		(char data);
	 void			(*usart2_WriteS)	(char *s);
	 //usart3
	 uint8_t	(*usart3_init)		(void);
	 void			(*usart3_Write)		(char data);
	 void			(*usart3_WriteS)	(char *s);	 
	//uart4
	 uint8_t 	(*uart4_init)		(void);
	 void			(*uart4_Write)	(char data);
	 void 		(*uart4_WriteS)	(char *s);
	//uart5
	 uint8_t 	(*uart5_init)		(void);
	 void			(*uart5_Write)	(char data);
	 void 		(*uart5_WriteS)	(char *s);
	 //TIM2
		uint8_t  (*tim2_init)			(void);
		
	
}t_halLib;
extern t_halLib *HAL;
//#define HAL ((t_evblLib *) 0x8010100)

/* functions */

void SystemClock_Config(void);

#endif // __hal_H__
