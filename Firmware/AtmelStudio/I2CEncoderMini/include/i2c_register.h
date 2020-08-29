/*
 * i2c_register.h
 *
 * Created: 03/05/2019 15:13:52
 *  Author: scaron
 */ 


#ifndef I2C_REGISTER_H_
#define I2C_REGISTER_H_


#define ID_CODE		0x39
#define ID_VERSION	0x11

typedef enum {
	I2C_DATA_REGISTER,
	I2C_DATA_DATA,
} I2C_DATA_MANAGING;

/** Internal i2C address definition **/
typedef enum {
	REG_GCONF = 0x00,
	REG_INTCONF = 0x01,
	REG_ESTATUS = 0x02,
	REG_CVALB4 = 0x03,
	REG_CVALB3 = 0x04,
	REG_CVALB2 = 0x05,
	REG_CVALB1 = 0x06,
	REG_CMAXB4 = 0x07,
	REG_CMAXB3 = 0x08,
	REG_CMAXB2 = 0x09,
	REG_CMAXB1 = 0x0A,
	REG_CMINB4 = 0x0B,
	REG_CMINB3 = 0x0C,
	REG_CMINB2 = 0x0D,
	REG_CMINB1 = 0x0E,
	REG_ISTEPB4 = 0x0F,
	REG_ISTEPB3 = 0x10,
	REG_ISTEPB2 = 0x11,
	REG_ISTEPB1 = 0x12,
	REG_DPPERIOD = 0x13,
	REG_IDCODE = 0x70,
	REG_VERSION = 0x71,
	REG_I2CADDRESS = 0x72,
	REG_EEPROMS = 0x80,
} I2C1_REGISTER;

union Data_v {
	int32_t val;
	uint8_t bval[4];
};


extern volatile uint8_t GCONF;
extern volatile uint8_t INTCONF;
extern volatile uint8_t ESTATUS;
extern volatile union Data_v CVAL;
extern volatile union Data_v CMAX;
extern volatile union Data_v CMIN;
extern volatile union Data_v ISTEP;
extern volatile uint8_t DPPERIOD;
extern volatile uint8_t I2CADDRESS;


extern volatile uint16_t DoublePush;


/** MSB or LSB order in 16bit variable **/
#define BYTE1 0
#define BYTE2 1
#define BYTE3 2
#define BYTE4 3






void i2c_error_handler();
void i2c_stop_handler();
void i2c_write_handler();
void i2c_read_handler();
void i2c_address_handler();

void I2C_init_clock_stretch();

#endif /* I2C_REGISTER_H_ */