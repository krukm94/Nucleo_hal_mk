/*
 ===========================================================================================================================================================================
																																			SOURCE FILE
																																			HAL DRIVER
																																			NUCLEO L476RG
																																			MICHAL KRUK

  ===========================================================================================================================================================================
*/ 

#include "hal.h"



//===================================================================================================================================================
void halLib_Init(void){
	/* Inicjalizacjia zegarów */
	SystemClock_Config();
	
	/* Inicjalizacja portu LED */
	led_port_init();
	
	/* Inicjalizacja uartu2 */
	usart2_init();

	//Powitanie
	usart2_WriteS("-->> NUCLEO L46 <<--\n\rTEST\n\rCompile time: ");
	usart2_WriteS(__TIME__);
	
	/* USART 1 */
	//		usart1_init();
	
	/*USART 3 */
	//	usart3_init();
	
		/*UART 4 */
	//	usart_stat = uart4_init();
	
		/*UART 5 */
	//	usart_stat = uart5_init();
	
	/* TIM2 */
	//procent++;
	tim2_stat =	tim2_init();
	
	/* TIM5 INIT */
	tim5_stat = tim5_init();

	/* I2C1 INIT */
	//i2c1_status =	i2c_init(I2C1, 0x00702991 , I2C1_PORT_SDA , I2C1_PIN_SDA , I2C1_PORT_SCL, I2C1_PIN_SCL , I2C1_GPIO_AF);

	/*GPIO INIT FOR TIME MESURE */
	gpio_init(GPIOB , GPIO_PIN_8 , GPIO_MODE_OUTPUT_PP , GPIO_PULLUP);
}


//===================================================================================================================================================
const t_halLib halLib /*__attribute__((at(0x8010100)))*/ ={
		//system
		halLib_Init,               //void     (*Init)(void);
		
		//LED
		led_port_init,						 //void			(*led_port_init)(void);
		ledOn,										 //void			(*ledOn)				(void);
		ledOff,										 //void			(*ledOff)				(void);
		ledToggle,								 //void 		(*ledToggle)		(void);
		
		//USART1
		usart1_init,								 //uint8_t	(*usart1_init)		(void);
		usart1_Write,								 //void			(*usart1_Write)		(char data);
		usart1_WriteS,							 //void			(*usart1_WriteS)		(char *s);
	 
		//USART2
		usart2_init,								 //uint8_t	(*usart2_init)		(void);
		usart2_Write,								 //void			(*usart2_Write)		(char data);
		usart2_WriteS,							 //void			(*usart2_WriteS)		(char *s);
		
		//USART3
		usart3_init,								 //uint8_t	(*usart3_init)		(void);
		usart3_Write,								 //void			(*usart3_Write)		(char data);
		usart3_WriteS,							 //void			(*usart3_WriteS)		(char *s);		
	  
		//uart4
		uart4_init,							 	 //uint8_t  (*uart4_init)	(void);
		uart4_Write,							 //void			(*uart4_Write)	(void);
		uart4_WriteS,						 	 //void 		(*uart4_WriteS)(char *s);
		
		//uart5
		uart5_init,							 	 //uint8_t  (*uart5_init)	(void);
		uart5_Write,							 //void			(*uart5_Write)	(void);
		uart5_WriteS,						 	 //void 		(*uart5_WriteS)(char *s);		
		
		//TIM2
		 tim2_init,									 //uint8_t  (*tim2_init)			(void);
		
		//I2C
		i2c_init,										//uint8_t	  (*i2c_init)									(I2C_TypeDef* I2Cx);
		i2c1_is_device_ready,				//uint8_t 	(*i2c1_is_device_ready) 		(uint16_t adr);
		read_mem,										//void			(*read_mem)									(uint16_t dev_adr,uint16_t mem_adr,uint16_t mem_size, uint8_t *data, uint16_t size);
		write_mem,									//void			(*write_mem)								(uint16_t dev_adr,uint16_t mem_adr,uint16_t mem_size, uint8_t *data, uint16_t size);
};
t_halLib *HAL=(t_halLib *)&halLib;






/*===================================================================================================================================================
*/


/*===================================================================================================================================================*/
