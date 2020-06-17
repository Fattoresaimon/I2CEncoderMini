# I2C Encoder Mini

## Introduction
The I2C Encoder Mini is a small board where you can use a classical mechanical encoder
It's possible to connect up to 127 boards in cascade and read all of them with the same I2C bus.
The I2C Encoder Mini has a series of 8 bit registers where it is possible to configure  the parameters and four 32 bit of registers. These 32 bit registers store counter value, value of increment steps, maximum and minimum thresholds.
Every time when encoder rotates at least one step, the counter value increases or decreases according to the rotation direction by the value of the increment steps register.
When the counter value is outside of the limit set by the thresholds registers, the counter value can be wrapped or can stuck on the threshold value reached.
I2C Encoder Mini also has an open-drain interrupt pin. It is set to logic low every time an interrupt occurs, the source of interrupt can be customized.

## Where you can get this board?
This project is avaiable on our [Tindie store!]https://www.tindie.com/products/saimon/i2c-encoder-mini/)



## Repository Structure
* [Arduino Library:](https://github.com/Fattoresaimon/ArduinoDuPPaLib) Repository where you can find the Arduino IDE library for the DuPPa boards  (Future)
* [Raspberry Library:](/Python%20Raspberry%20Library) Ready to use library in Python for the Raspberry board with example. (Future)
* [Firmware:](/Firmware) Project folder of Atmel Studio contain the code running inside of the ATtiny 402
* [Hardware:](/Hardware) Folder containing the gerber file, schematic and BOM. 
* [Datasheet EncoderMini:](EncoderMini_v1.1.pdf) Datasheet of the board with the description of the registers and some useful information.



## Licensing

Hardware and firmware are licensed under GPL-3 license.

Documentation is licensed under a Creative Commons BY-SA 4.0 international license.


**If you want to donate for my work, i would really appreciate it. You can donate here with this link. Thank you!**

[![donate](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=5DX7BCX7JD5SL)
