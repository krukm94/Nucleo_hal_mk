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

#define SET_TX_EN					gpio_set(GPIOA , GPIO_PIN_0)		//SET TX_EN pin nRF
#define SET_TX_CE					gpio_set(GPIOA , GPIO_PIN_10)		//SET TX_CE pin nRF 

#define RESET_TX_EN				gpio_reset(GPIOA , GPIO_PIN_0)	//RESET TX_EN pin nRF
#define RESET_TX_CE				gpio_reset(GPIOA , GPIO_PIN_10)	//RESET TX_CE pin nRF

#define SET_TX_CE_nRF_RX	gpio_set(GPIOA , GPIO_PIN_7)	 	//SET TX_CE pin nRF rx
#define RESET_TX_CE_nRF_RX gpio_reset(GPIOA , GPIO_PIN_7)	//RESET TX_CE pin nRF rx

//======================================== nRF registers ===================================================================

#define nRF_TX_REG				0x20										 //TX nRF register

// ======================================= FUNCTIONS =======================================================================

uint8_t spi2_nRF_init(void);											 //SPI2 init
uint8_t spi3_nRF_init(void);											 //SPI3 init

void gpio_init_for_spi2(void);				  					 //GPIO INIT FOR SPI2
void gpio_init_for_spi3(void);										 //GPIO INIT FOR SPI3

void gpio_nRF_init(void);													 //GPIO INIT FOR nRF tx pins like ( TX_EN , TX_CE , DR)
void gpio_nRF_rx_init(void);											 //GPIO INIT FOR nRF rx pins like (DR, TX_CE)

void gpio_it_nRF_tx_init(void);										 //GPIO IT INIT FOR nRF tx pin DR
void gpio_it_nRF_rx_init(void);										 //GPIO IT INIT FOR nRF rx pin DR
	
void spi2_transmit(uint8_t *pData_tx , uint16_t Size); // SPI2 TRANSMIT
void spi3_recive(uint8_t *pData_rx , uint16_t Size);	 // SPI3 RECIVE

void nRF_transmit(uint8_t *pData_tx, uint16_t Size);	 // nRF TRANSMIT

void nRF_recive(void);	 // nRF RECIVE


#endif // __nRF905_H__

/* ========================================================================================================================

																													END OF FILE
																													
   =========================================================================================================================
*/
//

