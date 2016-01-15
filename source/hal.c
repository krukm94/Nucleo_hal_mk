/*
 ===========================================================================================================================================================================
																																			SOURCE FILE
																																			HAL DRIVER
																																			NUCLEO L476RG
																																			MICHAL KRUK

  ===========================================================================================================================================================================
*/ 

#include "hal.h"

// global variables
volatile uint8_t usart_stat;
volatile uint8_t tim2_stat;

//===================================================================================================================================================
void halLib_Init(void){
  
	/* Inicjalizacjia zegarów */
		SystemClock_Config();
	
	/* Inicjalizacja portu LED */
		led_port_init();
	
	/* Inicjalizacja uartu2 */
		usart2_init();
	
	/* USART 1 */
		usart1_init();
	
	/*USART 3 */
		usart3_init();
	
		/*UART 4 */
		usart_stat = uart4_init();
	
		/*UART 5 */
	//	usart_stat = uart5_init();
	
	/* TIM2 */	
	tim2_stat =	tim2_init();
		
		usart2_WriteS("\n\r--> NUCLEO L4 <--\n\r TESTUJEMY: MKelectronic \n\r"); 
		usart2_WriteS(__TIME__);
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
		 
};
t_halLib *HAL=(t_halLib *)&halLib;




/*===================================================================================================================================================
*/
/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 80000000
  *            HCLK(Hz)                       = 80000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            HSI Frequency(Hz)              = 16000000
  *            PLL_M                          = 1
  *            PLL_N                          = 10
  *            PLL_R                          = 2
  *            PLLSAI_N                       = 384
  *            PLLSAI_P                       = 8
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode			<--- O co z tym chodzi?
  *            Flash Latency(WS)              = 4								<--- Tego tez nie kminie.
  * @param  None
  * @retval None
  */
	
	
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_PeriphCLKInitTypeDef PeriphClkInit;
	
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4);

	  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART3
                              |RCC_PERIPHCLK_UART4|RCC_PERIPHCLK_UART5;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
  PeriphClkInit.Uart4ClockSelection = RCC_UART4CLKSOURCE_PCLK1;
  PeriphClkInit.Uart5ClockSelection = RCC_UART5CLKSOURCE_PCLK1;
	PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;

  __PWR_CLK_ENABLE();

  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/*===================================================================================================================================================*/
