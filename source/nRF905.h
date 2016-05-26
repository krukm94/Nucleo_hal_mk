/* ========================================================================================================================

																													nRF905 module for 433 MHz comunication DRIVER
																													Autor: MK
																													Data: 24.05.2016
																													rev: 1.0 (24.05.2016)
   =========================================================================================================================
*/

#ifndef __nRF905_H__
#define __nRF905_H__

// ======================================= INCLUDES ========================================================================
#include "init.h"


// ======================================= DEFINES =========================================================================

#define SPI_INIT_OK				0x00
#define SPI_INIT_ERROR		0x01

#define SET_TX_EN					gpio_set(GPIOA , GPIO_PIN_4)		//SET TX_EN pin nRF
#define SET_TX_CE					gpio_set(GPIOA , GPIO_PIN_10)		//SET TX_CE pin nRF 

#define RESET_TX_EN				gpio_reset(GPIOA , GPIO_PIN_4)	//RESET TX_EN pin nRF
#define RESET_TX_CE				gpio_reset(GPIOA , GPIO_PIN_10)	//RESET TX_CE pin nRF

//======================================== nRF registers ===================================================================

#define nRF_TX_REG				0xE7										//TX nRF register

// ======================================= FUNCTIONS =======================================================================

uint8_t spi2_nRF_init(void);											 //SPI init
void gpio_init_for_spi(void);				  						 //GPIO INIT FOR SPI
void gpio_nRF_init(void);													 //GPIO INIT FOR nRF pins like ( TX_EN , TX_CE , DR)
void gpio_it_init(void);													 //GPIO IT INIT FOR nRF pin RD
	
void spi_transmit(uint8_t *pData , uint16_t Size); // SPI TRANSMIT

void nRF_transmit(uint8_t *pData, uint16_t Size);	 // nRF TRANSMIT


#endif // __nRF905_H__

/* ========================================================================================================================

																													END OF FILE
																													
   =========================================================================================================================
*/
//

