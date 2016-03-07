/*
 ===========================================================================================================================================================================
																																			Header FILE
																																			COMPAS DRIVER
																																			NUCLEO L476RG
																																			

  ===========================================================================================================================================================================
*/ 


#ifndef __kompas_H__
#define __kompas_H__

/* --------------------> INCLUDES */
#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"

#include "i2c.h"

/* --------------------> MACROS */
#define READ_ADR		0x3D
#define WRITE_ADR		0x3C

#define MEMORY_SIZE 1 						//Rozmiar rejestrow urzadzenia

#define MODE_REG		0x02					//ADres rejestru zmiany trybu pracy

#define CH_X_ADR 		0x03					// CH_X zaiwera sie w dwuch rejestrach 0x03 i 0x04 to samo przy innych kanalach
#define CH_Y_ADR		0x07
#define CH_Z_ADR 		0x05

/* --------------------> FUNCTIONS */

//funkcja sprawdza gotowosc urzadzenia
uint8_t is_device_ready(uint16_t adr);
uint16_t chanel_X(void);
uint16_t chanel_Z(void);
uint16_t chanel_Y(void);

//funkcja ustawia tryb pomiaru ciaglego
void const_mode(void);



#endif // __kompas_H__
