/*
 ===========================================================================================================================================================================
																																			SOURCE FILE
																																			COMPAS DRIVER
																																			NUCLEO L476RG
																																			MICHAL KRUK

  ===========================================================================================================================================================================
*/ 


/* ------------------> INCLUDES */
#include "kompas.h"



/* --------------------> FUNCTIONS */


/*
 ===========================================================================================================================================================================
																																			
															FUNKCJA SPRAWDZAJACA GOTOWOSC URZADZENIA

  ===========================================================================================================================================================================
*/ 

uint8_t is_device_ready(uint16_t adr){
	
// deklaracja zwracanego parametru
uint8_t device_stat;

		device_stat = i2c1_is_device_ready(adr);
	
	return device_stat;	
}

/*
 ===========================================================================================================================================================================
																																			
															ODCZYTUJACA ZAWARTOSC KANALU x

  ===========================================================================================================================================================================
*/ 

uint16_t chanel_X(void){

//bufor do odbioru z I2C
uint8_t 	ch_x_buf[2];
//	
uint16_t 	ch_x_rx;
	
	read_mem(READ_ADR,CH_X_ADR,MEMORY_SIZE,ch_x_buf,2);
	
	ch_x_rx = (ch_x_buf[0] << 8);
	ch_x_rx = ch_x_buf[1];
	
	return ch_x_rx;
}
/*
 ===========================================================================================================================================================================
																																			
															ODCZYTUJACA ZAWARTOSC KANALU Z

  ===========================================================================================================================================================================
*/ 

uint16_t chanel_Z(void){

//bufor do odbioru z I2C
uint8_t 	ch_z_buf[2];
//	
uint16_t 	ch_z_rx;
	
	read_mem(READ_ADR,CH_Z_ADR,MEMORY_SIZE,ch_z_buf,2);
	
	ch_z_rx = (ch_z_buf[0] << 8);
	ch_z_rx = ch_z_buf[1];
	
	return ch_z_rx;
}
/*
 ===========================================================================================================================================================================
																																			
															ODCZYTUJACA ZAWARTOSC KANALU Y

  ===========================================================================================================================================================================
*/ 

uint16_t chanel_Y(void){

//bufor do odbioru z I2C
uint8_t 	ch_y_buf[2];
//	
uint16_t 	ch_y_rx;
	
	read_mem(READ_ADR,CH_Y_ADR,MEMORY_SIZE,ch_y_buf,2);
	
	ch_y_rx = (ch_y_buf[0] << 8);
	ch_y_rx = ch_y_buf[1];
	
	return ch_y_rx;
}
/*
 ===========================================================================================================================================================================
																																			
															FUNKCJA USTAWIA TRYB POMIARU CIAGLEGO

  ===========================================================================================================================================================================
*/ 

void const_mode(void){
	//bufor potrzebny do przeslania komeny 
	uint8_t write_buf[2];
	
		write_buf[0] = 0;
		write_buf[1] = 0;
	
			write_mem(WRITE_ADR,MODE_REG,MEMORY_SIZE,write_buf,1);
	
}

