/*
 * Encoder.h
 *
 * Created: 03/05/2019 16:38:54
 *  Author: scaron
 */ 


#ifndef ENCODER_H_
#define ENCODER_H_

#define PB_DEBOUNCE 50

enum AB_STATE{
	A_NONE,
	A_LOW,
	A_HIGH,
	B_LOW,
	B_HIGH,
	B_NONE,
};


/** FSM for the push button **/
typedef enum {
	ENCODER_WAITPUSH,
	ENCODER_WAITRELEASE,
	ENCODER_WAITDOUBLEPUSH,
	ENCODER_WAITDOUBLERELEASED,
	ENCODER_DOUBLEDELAY,
	ENCODER_TIMEOUT,
	ENCODER_PUSHRESET,
} ENCODER_SWITCH_STATUS;

extern volatile int32_t e_cval;
extern volatile int32_t e_cmax;
extern volatile int32_t e_cmin;
extern volatile int32_t e_istep;

void Encoder_TimerB_START(void);
void Encoder_AB_Interrupt(void);
bool EncoderSwitch_GetValueFiltered(void);
void Encoder_PushButton_FSM(void);

#endif /* ENCODER_H_ */