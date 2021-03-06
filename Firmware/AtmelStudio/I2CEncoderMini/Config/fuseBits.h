/*
 * fuseBits.h
 *
 * Created: 12/08/2019 23:00:39
 *  Author: Saimon
 */ 


#ifndef FUSEBITS_H_
#define FUSEBITS_H_

FUSES = {
	0x00, // WDTCFG{PERIOD=OFF, WINDOW=OFF}
	0x00, // BODCFG{SLEEP=DIS, ACTIVE=DIS, SAMPFREQ=1KHz, LVL=BODLEVEL0}
	0x7E, // OSCCFG{FREQSEL=20MHZ, OSCLOCK=CLEAR}
	0x00, // Reserved
	0x00, // TCD0CFG{CMPA=CLEAR, CMPB=CLEAR, CMPC=CLEAR, CMPD=CLEAR, CMPAEN=CLEAR, CMPBEN=CLEAR, CMPCEN=CLEAR, CMPDEN=CLEAR}
	0xF6, // SYSCFG0{EESAVE=CLEAR, RSTPINCFG=UPDI, CRCSRC=NOCRC}
	0xFF, // SYSCFG1{SUT=64MS}
	0xFF, // APPEND
	0xFF, // BOOTEND
};

LOCKBITS = {
	0xC5, // LOCKBIT{LB=NOLOCK}
};






#endif /* FUSEBITS_H_ */