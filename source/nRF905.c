/* ========================================================================================================================

																													nRF905 module for 433 MHz comunication DRIVER
																													Autor: MK
																													Data: 24.05.2016
																													rev: 1.0 (24.05.2016)
																													
   =========================================================================================================================
*/


#include "nRF905.h"

/* ================================================== INIT STRUCTURES ========================================================
*/ 

GPIO_InitTypeDef gpio_init_struct;		//Struct for gpio init
SPI_HandleTypeDef	spi2_init_handle;		//Handle for spi init

/* ======================================================= FUNCTIONS ========================================================
*/ 

/* ======================================================= SPI INIT  ==============================================================
*/

/** 
  * @brief 
	*		SPI 2 INIT Return HAL status
	*		Config:
	*		Prescaler: 2
	*		Direction: 2 lines
	*   8 bit data
	*		Phase 1 edge
	*		Polarity LOW
	*		CRC Disabled
	*		First bit MSB
	*		NSS SOFT
  * @{
  */
uint8_t spi2_nRF_init(void){
		
		
		uint8_t spi_status = SPI_INIT_ERROR;					//Przypisanie wartosci error na poczatku
	
		__HAL_RCC_SPI2_CLK_ENABLE();									//SET CLOCK FOR SPI2
	
		gpio_init_for_spi();													//GPIO Init for SPI
		
		gpio_nRF_init();															//GPIO Init for nRF pins like (TX_EN , TX_CE , DR)
	
		gpio_it_init();																//GPIO IT init for nRF pin RD
	
		/* ==============================================================
				NOTATKI DO CONFIGURACJI SPI
				Wstepnie ustawiam na FULL Duplex master
	
				Bez sumy kontrolnej
				8 Bit danych
				Direction 2 lines
				Prescaler 64
				SPI PHASE 1 EDGE
			 ==============================================================
		*/
		spi2_init_handle.Instance 				 			= SPI2;
		spi2_init_handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;  // 80MHz / 64 = 1250000 Hz
		spi2_init_handle.Init.DataSize					= SPI_DATASIZE_8BIT;
		spi2_init_handle.Init.Direction				  = SPI_DIRECTION_2LINES;	
		spi2_init_handle.Init.Mode							= SPI_MODE_MASTER;
		spi2_init_handle.Init.CLKPhase					= SPI_PHASE_1EDGE;
		spi2_init_handle.Init.CLKPolarity			  = SPI_POLARITY_LOW;
		spi2_init_handle.Init.CRCCalculation		= SPI_CRCCALCULATION_DISABLED;
		spi2_init_handle.Init.FirstBit					=	SPI_FIRSTBIT_MSB;
		spi2_init_handle.Init.NSS							  = SPI_NSS_HARD_OUTPUT;
	  spi2_init_handle.Init.TIMode 						= SPI_TIMODE_DISABLED;
		spi2_init_handle.Init.CRCPolynomial 		= 7;
		spi2_init_handle.Init.CRCLength 				= SPI_CRC_LENGTH_DATASIZE;
		spi2_init_handle.Init.NSSPMode 					= SPI_NSS_PULSE_ENABLE;
		
		spi_status = HAL_SPI_Init(&spi2_init_handle);							//INIT SPI2
							
		if(spi_status != 0){																			//IF ERROR OCURS
			usart2_WriteS("\n#ERROR IN SPI INIT!");
			error_function();
		}
		
		return spi_status;																				//RETURN SPI INIT STATUS
}

/* ================================================== GPIO INIT FOR SPI ========================================================
*/
/** 
  * @brief 
	*		Inicjalization GPIO port for SPI2
	*		Config pins
	*		MODE AF PP
	*		NO PULL
	*		SPEED FAST
	*		
	*		PB 12 SS PIN
	*		PB 10 SCK PIN
	*		PC 2  MISO PIN
	*		PC 3 	MOSI PIN
  * @{
  */
void gpio_init_for_spi(void){

	__HAL_RCC_GPIOB_CLK_ENABLE();									//SET CLOCK FOR GPIOB
	__HAL_RCC_GPIOC_CLK_ENABLE();									//SET CLOCK FOR GPIOC
		
																								//FILL GPIO STRUCT
	
																								//INIT GPIO SCK(PIN10) and NSS FOR SPI2
	gpio_init_struct.Mode = GPIO_MODE_AF_PP;
	gpio_init_struct.Pin  = GPIO_PIN_10|GPIO_PIN_12;
	gpio_init_struct.Pull = GPIO_NOPULL;
  gpio_init_struct.Speed = GPIO_SPEED_HIGH;
	gpio_init_struct.Alternate = GPIO_AF5_SPI2;		//GPIO AF5
	
	HAL_GPIO_Init(GPIOB , &gpio_init_struct);			
	
																								//INIT GPIO MISO(PIN2) and MOSI(PIN3) FOR SPI2
	gpio_init_struct.Mode = GPIO_MODE_AF_PP;
	gpio_init_struct.Pin  = GPIO_PIN_2|GPIO_PIN_3;
	gpio_init_struct.Pull = GPIO_NOPULL;
  gpio_init_struct.Speed = GPIO_SPEED_HIGH;
	gpio_init_struct.Alternate = GPIO_AF5_SPI2;		//GPIO AF5
	
	HAL_GPIO_Init(GPIOC , &gpio_init_struct);			
	
}
/* ================================================== GPIO INIT FOR nRF ========================================================
*/
/** 
  * @brief 
	*		Init GPIO for DATA READY, TX_EN , TX_CE
  * @{
  */

void gpio_nRF_init(void){
	
	gpio_init(GPIOA , GPIO_PIN_4 , GPIO_MODE_OUTPUT_PP , GPIO_PULLUP);		//PIN PA4 as TX_EN
	
	gpio_init(GPIOA , GPIO_PIN_1 , GPIO_MODE_IT_RISING , GPIO_NOPULL);		//PIN PA1 as DATA READY PIN  INTERRUPT ON RISSING

	gpio_init(GPIOA , GPIO_PIN_10, GPIO_MODE_OUTPUT_PP , GPIO_PULLUP); 		//PIN PA10 as TX_CE
	
}
/* ================================================== GPIO INIT IT ========================================================
*/
/** 
  * @brief 
	*		Init IT for GPIO ( FOR RD PIN, if Pin set high = transmision complited)
  * @{
  */
void gpio_it_init(void){
	
	HAL_NVIC_SetPriority(EXTI1_IRQn , 0 , 0);												//malo wazne przerwanie z pinu RD 
	HAL_NVIC_EnableIRQ(EXTI1_IRQn);
	
}
/* ================================================== GPIO INTERUPT FUNC ========================================================
*/
/** 
  * @brief 
	*		Gpio interrupt func for RD PIN ( PA 1  if Pin set high = transmision complited)
  * @{
  */
void EXTI1_IRQHandler(void){
	
	//HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
	
	if(__HAL_GPIO_EXTI_GET_FLAG(GPIO_PIN_1)){
		__HAL_GPIO_EXTI_CLEAR_FLAG(GPIO_PIN_1);
		
		RESET_TX_EN;														//Reset Pinu TX_EN nRF
		RESET_TX_CE;														//Reset Pinu TX_CE nRF
	}

}

/* ================================================== SPI TRANSMIT ========================================================
*/
/** 
  * @brief 
	*		Sending inf by SPI
  * @{
  */
void spi_transmit(uint8_t *pData , uint16_t Size){
	
	HAL_SPI_Transmit(&spi2_init_handle , pData , Size , 100);
}

/* ================================================== nRF TRANSMIT ========================================================
*/
/** 
  * @brief 
	*		Transmiton nRF 
	*		pData is your data to send
	*		Size is size of your data in bytes
  * @{
  */

void nRF_transmit(uint8_t *pData, uint16_t Size){
	
	SET_TX_EN;																			// Ustawienie pinu TX_EN na logiczne 1
	
	spi_transmit( (uint8_t*)nRF_TX_REG , 1);				// Wysylanie adresu TX nRF'a
	spi_transmit( pData , Size); 										// Load data to payload
																								
	SET_TX_CE;																			// UStawienie pinu TX_CE na logiczne 1 

}


/* ========================================================================================================================

																													END OF FILE
																													
   =========================================================================================================================
*/
//


