/*
 * Configuration.h
 *
 * Created: 22/06/2019 15:18:43
 *  Author: Saimon
 */ 


#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_



#define WRAPE 0x01
#define DIRE 0x02
#define IPULL 0x04
#define RMOD 0x18
#define RESET_BOARD 0x80

 #define S_PUSHR 0x01
 #define S_PUSHP  0x02
 #define S_PUSHD  0x04
 #define S_PUSHL  0x08
 #define S_RINC  0x10
 #define S_RDEC  0x20
 #define S_RMAX  0x40
 #define S_RMIN  0x80
 

extern volatile uint8_t X1_p;
extern volatile uint8_t X1_n;
extern volatile uint8_t X2_p;
extern volatile uint8_t X2_n;
extern volatile uint8_t X4_p;
extern volatile uint8_t X4_pp;
extern volatile uint8_t X4_n;
extern volatile uint8_t X4_nn;

extern volatile uint8_t wrap;


void Gconf_process(void);
void Encoder_Config(void);
void Int_set(uint8_t stat);
void Ext_Int_Set(void);
void Ext_Int_Reset(void);

#endif /* CONFIGURATION_H_ */