/*
 ===========================================================================================================================================================================
																																			Header FILE
																																			UART DRIVER
																																			NUCLEO L476RG
																																			MICHAL KRUK

  ===========================================================================================================================================================================
*/ 

#ifndef __uart_H__
#define __uart_H__


/* -------------------------->	includes */
#include <string.h>
#include "init.h"

#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_gpio.h"
#include "stm32l4xx_hal_uart.h"


/* -------------------------->	defines*/

/* driver configuration */

#define USART1_ON 1
#define USART1_IT_RX_ON 1

#define USART2_ON 1
#define USART2_IT_RX_ON 0

#define USART3_ON 1
#define USART3_IT_RX_ON 1

#define UART4_ON 1
#define UART4_IT_RX_ON 0

#define UART5_ON 0
#define UART5_IT_RX_ON 0

/* return macros */
#define UART_INIT_OK 			0x00
#define UART_INIT_ERROR		0x01


/* BAUDRATES */
#define BAUDRATE_USART2   2000000
#define BAUDRATE_USART1		9600
#define BAUDRATE_USART3		9600

#define BAUDRATE_UART4		115200
#define BAUDRARE_UART5		9600



/* -------------------------->  functions */
uint8_t 	usart1_init(void);
void			usart1_Write(char data);
void			usart1_WriteS(char *s);
void 			usart1_odczyt(uint8_t rx);

uint8_t		usart2_init(void);
void 			usart2_Write(char data);
void 			setIrqFunc(void (*pFunc)(char data));
void 			usart2_WriteS(char *s);

uint8_t 	usart3_init(void);
void			usart3_Write(char data);
void			usart3_WriteS(char *s);
void 			usart3_odczyt(uint8_t rx);

uint8_t 	uart4_init(void);
void 			uart4_Write(char data);
void 			uart4_WriteS(char *s);

uint8_t 	uart5_init(void);
void 			uart5_Write(char data);
void 			uart5_WriteS(char *s);



#endif // __uart_H__

