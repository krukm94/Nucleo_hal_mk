/*
 * mk_term.c
 *
 *  Created on: 30-04-2013
 *      Author: Miros³aw Kardaœ
 */

#include "mk_term.h"


// aby mieæ polskie ogonki w PUTTY ----> ustawiæ WINDOW / Translation / Win1250

 char UCLS[] = { "\x1b""[2J" };

 char UHOME[] = { "\x1b""[;H" };

 char UCUR_HIDE[] = { "\x1b""[?25l" };
 char UCUR_SHOW[] = { "\x1b""[?25h" };

 char U_ATTR_OFF[] = { "\x1b""[m" };



void tr_cursor_hide( uint8_t hide ) {
	if(hide) usart2_WriteS( UCUR_HIDE );
	else usart2_WriteS( UCUR_SHOW );
}


void tr_cls(uint8_t cur_onoff) {

	usart2_WriteS( U_ATTR_OFF );
	tr_cursor_hide(cur_onoff);
	usart2_WriteS( UCLS );

	usart2_WriteS( UHOME );

}


void tr_attr( uint8_t atr, uint8_t fg, uint8_t bg ) {
	usart2_Write( 0x1b );		// <ESC>[0;32;44m
	usart2_Write( '[' );
	usart2_Write( atr+'0' );
	usart2_Write( ';' );
	usart2_Write( '3' );
	usart2_Write( fg+'0' );
	usart2_Write( ';' );
	usart2_Write( '4' );
	usart2_Write( bg+'0' );
	usart2_Write( 'm' );
}


void tr_pen_color( uint8_t cl ) {
	usart2_Write( 0x1b );		// <ESC>[34m
	usart2_Write( '[' );
	usart2_Write( '3' );
	usart2_Write( cl+'0' );
	usart2_Write( 'm' );
}

void tr_brush_color( uint8_t cl ) {
	usart2_Write( 0x1b );		// <ESC>[44m
	usart2_Write( '[' );
	usart2_Write( '4' );
	usart2_Write( cl+'0' );
	usart2_Write( 'm' );
}


void tr_locate( uint8_t y, uint8_t x ) {

	usart2_Write( 0x1b );	// <ESC>[y;xH
	usart2_Write( '[' );
	usart2_Write( y);
	usart2_Write( ';' );
	usart2_Write( x);
	usart2_Write( 'H' );
}


