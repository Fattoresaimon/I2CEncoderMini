/*
* I2C_register.c
*
* Created: 03/05/2019 15:13:33
*  Author: scaron
*/

#include <stdint.h>
#include <stdbool.h>
#include <atmel_start.h>
#include <main.h>
#include <atomic.h>
#include "i2c_register.h"
#include "Configuration.h"


#define I2C_ADDRES_EEPROM 0x00
#define EEPROM_OFFSET_ADD 0x80
#define EEPROM_TOP_BORDER 0x81
#define EEPROM_BOT_BORDER 0xFF
volatile uint8_t register_address=0;
volatile uint8_t data_type;

volatile uint8_t tempAdd[3]={1,2,3}, AddCnt=0;
uint8_t data[] __attribute__((section(".eeprom"))) = {0x20}; //Configure the default address

volatile uint8_t GCONF;
volatile uint8_t INTCONF;
volatile uint8_t ESTATUS;
volatile union Data_v CVAL;
volatile union Data_v CMAX;
volatile union Data_v CMIN;
volatile union Data_v ISTEP;
volatile uint8_t DPPERIOD;
volatile uint8_t I2CADDRESS;

volatile uint16_t DoublePush;

void I2C_address_handler()
{
	data_type=I2C_DATA_REGISTER;
	I2C_send_ack(); // or send_nack() if we don't want to ack the address
}

void I2C_read_handler()
{ // Master read operation
	
	volatile uint8_t data=0;
	switch(register_address){
		
		case REG_GCONF:
		data=GCONF;
		break;
		
		case REG_INTCONF:
		data=INTCONF;
		break;

		case REG_ESTATUS:
		data=ESTATUS;
		Ext_Int_Reset();
		break;
		
		case REG_CVALB4:
		data=CVAL.bval[BYTE4];
		break;
		
		case REG_CVALB3:
		data=CVAL.bval[BYTE3];
		break;
		
		case REG_CVALB2:
		data=CVAL.bval[BYTE2];
		break;
		
		case REG_CVALB1:
		data=CVAL.bval[BYTE1];
		break;
		
		case REG_CMAXB4:
		data=CMAX.bval[BYTE4];
		break;
		
		case REG_CMAXB3:
		data=CMAX.bval[BYTE3];
		break;
		
		case REG_CMAXB2:
		data=CMAX.bval[BYTE2];
		break;
		
		case REG_CMAXB1:
		data=CMAX.bval[BYTE1];
		break;
		
		case REG_CMINB4:
		data=CMIN.bval[BYTE4];
		break;
		
		case REG_CMINB3:
		data=CMIN.bval[BYTE3];
		break;
		
		case REG_CMINB2:
		data=CMIN.bval[BYTE2];
		break;
		
		case REG_CMINB1:
		data=CMIN.bval[BYTE1];
		break;
		
		case REG_ISTEPB4:
		data=ISTEP.bval[BYTE4];
		break;
		
		case REG_ISTEPB3:
		data=ISTEP.bval[BYTE3];
		break;
		
		case REG_ISTEPB2:
		data=ISTEP.bval[BYTE2];
		break;
		
		case REG_ISTEPB1:
		data=ISTEP.bval[BYTE1];
		break;
		
		
		case REG_DPPERIOD:
		data=DPPERIOD;
		
		break;
		
		case REG_IDCODE:
		data=ID_CODE;
		break;
		
		case REG_VERSION:
		data=ID_VERSION;
		break;
		
		case REG_I2CADDRESS:
		data=FLASH_0_read_eeprom_byte((eeprom_adr_t)I2C_ADDRES_EEPROM);
		break;
	}
	
	if((register_address >= EEPROM_TOP_BORDER)&&(register_address <= EEPROM_BOT_BORDER)){
		data=FLASH_0_read_eeprom_byte((eeprom_adr_t)(register_address-EEPROM_OFFSET_ADD));
	}
	
	I2C_write(data);
	I2C_send_ack();
	register_address++;


}

void I2C_write_handler()
{ // Master write handler
	
	if(data_type==I2C_DATA_REGISTER){
		
		register_address = I2C_read();
		data_type=I2C_DATA_DATA;
		I2C_send_ack(); // or send_nack() if we don't want to receive more data
		return;
	}
	
	switch(register_address){
		case REG_GCONF:
		GCONF= I2C_read();
		Gconf_process();
		break;
		
		case REG_INTCONF:
		INTCONF= I2C_read();
		break;
		
		case REG_CVALB4:
		CVAL.bval[BYTE4]= I2C_read();
		break;
		
		case REG_CVALB3:
		CVAL.bval[BYTE3]= I2C_read();
		break;
		
		case REG_CVALB2:
		CVAL.bval[BYTE2]=I2C_read();
		break;
		
		case REG_CVALB1:
		CVAL.bval[BYTE1]=I2C_read();
		break;
		
		case REG_CMAXB4:
		CMAX.bval[BYTE4]=I2C_read();
		break;
		
		case REG_CMAXB3:
		CMAX.bval[BYTE3]=I2C_read();
		break;
		
		case REG_CMAXB2:
		CMAX.bval[BYTE2]=I2C_read();
		break;
		
		case REG_CMAXB1:
		CMAX.bval[BYTE1]=I2C_read();
		break;
		
		case REG_CMINB4:
		CMIN.bval[BYTE4]=I2C_read();
		break;
		
		case REG_CMINB3:
		CMIN.bval[BYTE3]=I2C_read();
		break;
		
		case REG_CMINB2:
		CMIN.bval[BYTE2]=I2C_read();
		break;
		
		case REG_CMINB1:
		CMIN.bval[BYTE1]=I2C_read();
		break;
		
		case REG_ISTEPB4:
		ISTEP.bval[BYTE4]=I2C_read();
		break;
		
		case REG_ISTEPB3:
		ISTEP.bval[BYTE3]=I2C_read();
		break;
		
		case REG_ISTEPB2:
		ISTEP.bval[BYTE2]=I2C_read();
		break;
		
		case REG_ISTEPB1:
		ISTEP.bval[BYTE1]=I2C_read();
		break;
		
		case REG_DPPERIOD:
		DPPERIOD=I2C_read();
		DoublePush = (uint16_t) DPPERIOD * 10;
		break;
		
		case REG_I2CADDRESS:
		I2CADDRESS=I2C_read();
		tempAdd[AddCnt++]=I2CADDRESS;
		
		if(AddCnt>2){
			AddCnt=0;
			if((tempAdd[0] == tempAdd[1]) && (tempAdd[0] == tempAdd[2])){
				FLASH_0_write_eeprom_byte(I2C_ADDRES_EEPROM,I2CADDRESS);
				tempAdd[0]=1;
				tempAdd[1]=2;
				tempAdd[2]=3;
			}
		}
		
		break;
		
	}

	if((register_address >= EEPROM_TOP_BORDER)&&(register_address <= EEPROM_BOT_BORDER)){
		FLASH_0_write_eeprom_byte((eeprom_adr_t)(register_address-EEPROM_OFFSET_ADD), I2C_read());
	}

	I2C_send_ack(); // or send_nack() if we don't want to receive more data
	register_address++;
}

void I2C_stop_handler()
{
	return;
}

void I2C_error_handler()
{
	while (1)
	;
}

/**
* \brief Initialize I2C interface
* If module is configured to disabled state, the clock to the I2C is disabled
* if this is supported by the device's clock system.
*
* \return Nothing
*/
void I2C_init_clock_stretch()
{
	
	GCONF=0;
	INTCONF=0;
	ESTATUS=0;
	CVAL.val=0;
	CMAX.val=0;
	CMIN.val=0;
	ISTEP.val=0;
	DPPERIOD=0;	

	uint8_t add;
	add=FLASH_0_read_eeprom_byte((eeprom_adr_t)(I2C_ADDRES_EEPROM));

	// TWI0.CTRLA = 0 << TWI_FMPEN_bp /* FM Plus Enable: disabled */
	//		 | TWI_SDAHOLD_OFF_gc /* SDA hold time off */
	//		 | TWI_SDASETUP_4CYC_gc; /* SDA setup time is 4 clock cycles */

	// TWI0.DBGCTRL = 0 << TWI_DBGRUN_bp; /* Debug Run: disabled */

	TWI0.SADDR = add << TWI_ADDRMASK_gp /* Slave Address: 0x20 */
	| 0 << TWI_ADDREN_bp;   /* General Call Recognition Enable: disabled */

	// TWI0.SADDRMASK = 0 << TWI_ADDREN_bp /* Address Mask Enable: disabled */
	//		 | 0x0 << TWI_ADDRMASK_gp; /* Address Mask: 0x0 */

	TWI0.SCTRLA = 1 << TWI_APIEN_bp    /* Address/Stop Interrupt Enable: enabled */
	| 1 << TWI_DIEN_bp   /* Data Interrupt Enable: enabled */
	| 1 << TWI_ENABLE_bp /* Enable TWI Slave: enabled */
	| 1 << TWI_PIEN_bp   /* Stop Interrupt Enable: enabled */
	| 0 << TWI_PMEN_bp   /* Promiscuous Mode Enable: disabled */
	| 0 << TWI_SMEN_bp;  /* Smart Mode Enable: enable */

	I2C_set_write_callback(I2C_write_handler);
	I2C_set_read_callback(I2C_read_handler);
	I2C_set_address_callback(I2C_address_handler);
	I2C_set_stop_callback(I2C_stop_handler);
	I2C_set_collision_callback(I2C_error_handler);
	I2C_set_address_callback(I2C_address_handler);
	I2C_open();
	
	Gconf_process();
}

