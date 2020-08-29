/*
* Encoder.c
*
* Created: 03/05/2019 16:39:10
*  Author: scaron
*/


#include <stdint.h>
#include <stdbool.h>
#include <atmel_start.h>
#include <main.h>
#include <atomic.h>
#include "i2c_register.h"
#include "Encoder.h"
#include "Configuration.h"


uint8_t pb_fsm = ENCODER_WAITPUSH;
int8_t pb_cnt = 0;
uint16_t double_push_cnt = 0;
uint16_t double_push_delay = 0;

uint16_t enc_deb_cnt = 0;

volatile int32_t e_cval=1;
volatile int32_t e_cmax=0;
volatile int32_t e_cmin=0;
volatile int32_t e_istep=0;

volatile uint8_t enc_status;

void Encoder_TimerB_START(void){
	EVSYS.ASYNCSTROBE=0x01;
	TCB0.CNT = 0x0;
}



void Encoder_AB_Interrupt(void){
	int32_t temp;
	
	enc_status = (enc_status<<2);
	enc_status= enc_status | ((VPORTA.IN & 0xC0)>>6);
	enc_status= enc_status & 0x0f;
	
	temp=CVAL.val;
	
	if((enc_status==X1_p)||(enc_status==X2_p)||(enc_status==X4_pp)||(enc_status==X4_p)){
		temp=temp + ISTEP.val;
		Int_set(S_RINC);
		}else{
		
		if((enc_status==X1_n)||(enc_status==X2_n)||(enc_status==X4_nn)||(enc_status==X4_n)){
			temp=temp - ISTEP.val;
			Int_set(S_RDEC);
		}
	}
	
	if(wrap==1){
		if(temp>CMAX.val){
			CVAL.val=CMIN.val;
			Int_set(S_RMAX);
			}else{
			if(temp<CMIN.val){
				CVAL.val=CMAX.val;
				Int_set(S_RMIN);
				}else{
				CVAL.val=temp;
			}
		}
		}else{
		if(temp>CMAX.val){
			CVAL.val=CMAX.val;
			Int_set(S_RMAX);
			}else{
			if(temp<CMIN.val){
				CVAL.val=CMIN.val;
				Int_set(S_RMIN);
				}else{
				CVAL.val=temp;
			}
		}
		
	}
	
	Ext_Int_Set();

}




bool EncoderSwitch_GetValueFiltered(void) {
	static bool pb_status = false;

	if (SW_get_level() == false) {
		if (pb_cnt++ >= PB_DEBOUNCE) {
			pb_cnt = PB_DEBOUNCE;
			pb_status = true;
		}
		} else {
		if (pb_cnt-- <= 0) {
			pb_cnt = 0;
			pb_status = false;
		}
	}

	return pb_status;
}


void Encoder_PushButton_FSM(void) {

	if (double_push_cnt > DoublePush) {
		pb_fsm = ENCODER_TIMEOUT;
		} else {
		double_push_cnt++;
	}

	switch (pb_fsm) {
		case ENCODER_WAITPUSH:
		double_push_cnt = 0;
		if (EncoderSwitch_GetValueFiltered() == true) {
			pb_fsm = ENCODER_WAITRELEASE;
		}
		break;


		case ENCODER_WAITRELEASE:
		if (EncoderSwitch_GetValueFiltered() == false) {
			pb_fsm = ENCODER_WAITDOUBLEPUSH;
		}
		break;

		case ENCODER_WAITDOUBLEPUSH:
		if (EncoderSwitch_GetValueFiltered() == true) {
			pb_fsm = ENCODER_WAITDOUBLERELEASED;
		}
		break;

		case ENCODER_WAITDOUBLERELEASED:
		if (EncoderSwitch_GetValueFiltered() == false) {
			double_push_cnt = 0;
			double_push_delay=0;
			pb_fsm = ENCODER_DOUBLEDELAY;
			Int_set(S_PUSHD);
			Ext_Int_Set();
		}
		break;

		case ENCODER_DOUBLEDELAY:
		double_push_cnt = 0;
		if (double_push_delay > DoublePush) {
			pb_fsm = ENCODER_WAITPUSH;
			} else {
			double_push_delay++;
		}
		break;

		case ENCODER_TIMEOUT:
		double_push_cnt = 0;
		Int_set(S_PUSHP);
		if (EncoderSwitch_GetValueFiltered() == true) {
			pb_fsm = ENCODER_PUSHRESET;
			if(DoublePush!=0)
				Int_set(S_PUSHL);
			} else {
			pb_fsm = ENCODER_WAITPUSH;
			Int_set(S_PUSHR);
		}
		Ext_Int_Set();
		break;

		case ENCODER_PUSHRESET:
		double_push_cnt = 0;
		if (EncoderSwitch_GetValueFiltered() == false) {
			Int_set(S_PUSHR);
			Ext_Int_Set();
			pb_fsm = ENCODER_WAITPUSH;
		}
		break;
	}
}
