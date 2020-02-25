#include <atmel_start.h>
#include <main.h>
#include <atomic.h>
#include <stdint.h>
#include "i2c_register.h"
#include "Encoder.h"
#include <avr/io.h>
#include <avr/fuse.h>


#define f_APPEND  0x00
#define f_BODCFG  0x50 
#define f_BOOTEND  0x00
#define f_OSCCFG  0x02 
//#define f_SYSCFG0  0xF4 //UDPI MODE
#define f_SYSCFG0  0xF0 //GPIO MODE
#define f_SYSCFG1  0x03
#define f_TCD0CFG  0x00
#define f_WDTCFG  0x00




__fuse_t  __fuse __attribute__((section (".fuse"))) =
{
{f_WDTCFG, f_BODCFG, f_OSCCFG, 0,0, f_SYSCFG0, f_SYSCFG1, f_APPEND, f_BOOTEND,0}

};


volatile bool sys_timer;

void SystemTimer(void){
	sys_timer = true;

}


int main(void)
{

	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
    I2C_init_clock_stretch();

	
	/* Replace with your application code */
	while (1) {
		if(sys_timer == true){
			sys_timer = false;
			Encoder_PushButton_FSM();
			}
	}
}




