#ifndef __INIT_H_
#define __INIT_H_

//=============================================================================================

#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"

//============================================= MY INCLUDES ===================================


#include "lsm9ds0.h"
#include "led.h"
#include "uart.h"
#include "timer.h"
#include "itoa.h"
#include "gpio_mk.h"
#include "i2c.h"
#include "discovery_boards.h"
#include "nRF905.h"

//=============================================================================================

// ---------------------------> DEFINES
#define TIM_MEAS_PORT GPIOB
#define TIM_MEAS_PIN  8

// ---------------------------> FUNCTIONS
void SystemClock_Config(void);
void init(void);
void error_function(void);

#endif //__INIT_H_
