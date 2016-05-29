/* ==================================================================================================================================

																				INIT C
																				MK
									
 ====================================================================================================================================
 */	
#include "init.h"

// ---------------------------> VARIABLES 
// global variables
volatile uint8_t usart_stat;
volatile uint8_t tim2_stat;
volatile uint8_t i2c1_status;
volatile uint8_t tim5_stat;
volatile uint8_t tim3_stat;

//extern volatile uint32_t procent;


/* ==================================================================================================================================

																				init function
									
 ====================================================================================================================================
 */	
void init(void){
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
	
	/* TIM3 */
	tim3_stat = tim3_init();
	
	/* TIM5 INIT */
	//tim5_stat = tim5_init();

	/* I2C1 INIT */
	//i2c1_status =	i2c_init(I2C1, 0x00702991 , I2C1_PORT_SDA , I2C1_PIN_SDA , I2C1_PORT_SCL, I2C1_PIN_SCL , I2C1_GPIO_AF);

	/*GPIO INIT FOR TIME MESURE */
	//gpio_init(GPIOB , GPIO_PIN_8 , GPIO_MODE_OUTPUT_PP , GPIO_PULLUP);
	
	/* INIT SPI */
	spi2_nRF_init();
	spi3_nRF_init();
	
}


/*
 ===========================================================================================================================================================================
																																			
													ERROR FUNCTION(That function is executed when error occurs)

  ===========================================================================================================================================================================
*/ 
void error_function(void){

		while(1){
			ledToggle();	
			HAL_Delay(100);
		}
}

/* ==================================================================================================================================

													CLOCK CONFIG
									
 ====================================================================================================================================
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



/* ==================================================================================================================================

													END OF FILE
									
 ====================================================================================================================================
 */	

//

