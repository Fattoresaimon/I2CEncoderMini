/*
* Configuration.c
*
* Created: 22/06/2019 15:18:29
*  Author: Saimon
*/
#include <stdint.h>
#include <stdbool.h>
#include <atmel_start.h>
#include <avr/wdt.h>
#include <main.h>
#include <atomic.h>
#include "Configuration.h"
#include "i2c_register.h"
#include "Encoder.h"


volatile uint8_t X1_p; // X1/X2 mode increment
volatile uint8_t X1_n; // X1/X2 mode decrement
volatile uint8_t X2_n;// X2 mode decrement
volatile uint8_t X2_p; // X2 mode increment
volatile uint8_t X4_n;// X4 mode decrement
volatile uint8_t X4_p; // X4 mode increment
volatile uint8_t X4_nn;// X4 mode decrement
volatile uint8_t X4_pp; // X4 mode increment



volatile uint8_t wrap;

void Gconf_process(void){
	
	if((GCONF&WRAPE)!=0)
	wrap=1;
	else
	wrap=0;
	
	if((GCONF&IPULL)!=0)
	INT_set_pull_mode(PORT_PULL_UP);
	else
	INT_set_pull_mode(PORT_PULL_OFF);
	
	if((GCONF&RESET_BOARD)==RESET_BOARD){
		CCP=0xD8;
		RSTCTRL.SWRR = 1;	
	}
	
	Encoder_Config();
	
}


void Encoder_Config(void){
	
	// set the direction
	if((GCONF&DIRE)!=0){
		X1_p=4;
		X1_n=8;
		
		X2_p=11;
		X2_n=7;
		
	    X4_p=2;
		X4_pp=13;
		X4_n=1;
		X4_nn=14;
		
	}
	else
	{
		X1_p=8;
		X1_n=4;
		
		X2_p=7;
		X2_n=11;
		
		X4_p=1;
		X4_pp=14;
		X4_n=2;
		X4_nn=13;
	}
	
	// set the X1 or X2 or X4 mode
	switch(GCONF&RMOD){
		case 0:
			X2_n=0xff;
			X2_p=0xff;
		
			X4_p=0xff;
			X4_pp=0xff;
			X4_n=0xff;
			X4_nn=0xff;
		break;
		
		case 8:
			X4_p=0xff;
			X4_pp=0xff;
			X4_n=0xff;
			X4_nn=0xff;
		break;
		
	}	
}

void Int_set(uint8_t stat){
	
	ESTATUS |= (uint8_t) stat;


}

void Ext_Int_Set(void){
	if((ESTATUS&INTCONF)==0)
	return;
	INT_set_dir(PORT_DIR_OUT);
	INT_set_level(false);
}

void Ext_Int_Reset(void){
	ESTATUS=0;
	INT_set_dir(PORT_DIR_IN);
	
	if((GCONF&IPULL)!=0)
	INT_set_pull_mode(PORT_PULL_UP);
	else
	INT_set_pull_mode(PORT_PULL_OFF);
}