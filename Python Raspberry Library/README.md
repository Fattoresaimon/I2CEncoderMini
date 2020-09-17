# I2C Encoder Mini Python library 
--------------------------------------------------------------------------------

## Introduction

Here you can find the library and some examples for Raspberry Pi.
For more details of the functionality of the board please read the [Datasheet](../I2CEncoderMini_v1.2.pdf) 

## Installation

The installation is very simple:

* Download the file [**i2cEncoderMiniLib.py** ](Source/i2cEncoderMiniLib.py) 
* Put the file in the folder where you have the source files.
* Import the library in your source files
``` python
import i2cEncoderMiniLib
```


## Initialization

The library makes available the class **i2cEncoderMiniLib**
For initialize the library you have to declare an instance of the class **i2cEncoderMiniLib** for each encoders.
In the instance you have to declare the I2C address of the board
For example:

``` python
import smbus2
import i2cEncoderMiniLib

bus = smbus2.SMBus(1)
encoder = i2cEncoderMiniLib.i2cEncoderMiniLib(bus, 0x20)
```
In this example the I2C address is the default address 0x20

## Callback Configuration

This library support the callback functionality.
There is the possibility to link a function to a specific interrupt of the I2C Encoder Mini, in this way the function is automatically called when the I2C Encoder Mini generates an interrupts.

A callback function must be declared as the following:

```python
def NAME_OF_THE_FUNCTION():
```
There are 16 possible events:

| Event   | Description   |
|:-----------:|:----------------------------------|
| onButtonRelease | Encoder push button is released |
| onButtonPush | Encoder push button is pushed |
| onButtonDoublePush | Encoder push button is double pushed |
| onButtonLongPush | Encoder push button is long pressed |
| onIncrement | The counter value is incremented |
| onDecrement | The counter value is decremented |
| onChange | The counter value is incremented or decremented |
| onMax | The counter value reach the maximum threshold |
| onMin | The counter value reach the minimum threshold |
| onMinMax | The counter value reach the maximum or minimum threshold |

#### Examples:

```python
encoder = i2cEncoderMiniLib.i2cEncoderMiniLib(bus, 0x20)

...

 # Simple callback that ist's called when the encoder is rotated and blink the green led #
def EncoderChange():
    print ('Changed: %d' % (encoder.readCounter32()))
...

encoder.onChange = EncoderChange # Attach the event to the callback function#

}

```

If you need to remove the link with a callback, you just need to define:
```python
encoder.onChange = None
```

## Methods

### Initialization
#### begin(conf)
This is used for initialize the encoder by writing the configuration register.
The parameters can be concatenate in OR mode.
Possible parameters are the following:

| Parameter | Description |
| ---------- | ------------------------------------------------------ |
| WRAP_ENABLE | Wrap enable. When the counter value reaches the CMAX+1, restart to the CMIN and vice versa |
| WRAP_DISABLE | Wrap disable. When the counter value reaches the CMAX or CMIN, the counter stops to increasing or decreasing |
| | |
| DIRE_LEFT | Rotate left side to increase the value counter |
| DIRE_RIGHT | Rotate right side to increase the value counter |
| | |
| IPUP_DISABLE | Disable the internal pull-up on the INT pin |
| IPUP_ENABLE | Enable the internal pull-up on the INT pin |
| | |
| RMOD_X1 | Encoder in X1 mode |
| RMOD_X2 | Encoder in X2 mode |
| RMOD_X4 | Encoder in X4 mode |
| | |
| RESET | Reset the board |
| | |

###### Examples:

```python
encoder.begin(i2cEncoderMiniLib.WRAP_ENABLE | i2cEncoderMiniLib.DIRE_RIGHT | i2cEncoderMiniLib.IPUP_ENABLE | i2cEncoderMiniLib.RMOD_X1 )
```

###  reset()
Reset of the board. 
In this command there is 8ms delay in order to make the board correctly restart.


### Configuration

##### writeInterruptConfig(interrupt)

This method is used for enable or disable the interrupt source selectively. When an interrupt event occurs, the INT pin goes low and the event is stored in the status register.

| Parameter   | Description   |
|:-----------:|:-------------:|
| PUSHR | Push button of the encoder is released |
| PUSHP | Push button of the encoder is pressed |
| PUSHL | Push button of the encoder is long pressed |
| PUSHD | Push button of the encoder is doule pushed  |
| RINC  | Encoder is rotated in the increment direction  |
| RDEC  | Encoder is rotated in the decrement direction  |
| RMAX  | Maximum threshold is reached  |
| RMIN  | Minimum threshold is reached  |


###  void autoconfigInterrupt(void)

This method auto configures the **INTCONF** register according to the attached callback.
**For the proper use, must be called after the definition of the last event property.**

```python
encoder.onChange = EncoderChange
encoder.onButtonPush = EncoderPush
encoder.onButtonDoublePush = EncoderDoublePush
encoder.onMax = EncoderMax
encoder.onMin = EncoderMin
  # Enable the I2C Encoder V2 interrupts according to the previous attached callback #
encoder.autoconfigInterrupt()

```

##### writeDoublePushPeriod(dperiod)

This method is used for setting the window period  **DPPERIOD** of the double push of the rotary encoder switch. It the value is 0 the double push option is disabled.
The I2C encoder V2 will multiply this value x10.
###### Examples:

```python
encoder.writeDoublePushPeriod(50)  # Set a period for the double push of 500ms #
```
### Status

##### updateStatus()
Read from the encoder status register (reg:0x05) and save the value internally.
Return value is **true** in case of some event, otherwise is **false**

###### Examples:

```python
  if Encoder.updateStatus() == True :
  # Something happens
  
```



##### readStatus(status)

Must be called after **updateStatus()**, this method is used for check if some event occurred one the **ESTATUS** register.
Return value is **true** in case of the event occurred, otherwise is **false**
Possible parameter are:

| Parameter   | Description   |
|:-----------:|:-------------:|
| PUSHR | Push button of the encoder is released |
| PUSHP | Push button of the encoder is pressed |
| PUSHL | Push button of the encoder is long pushed  |
| PUSHD | Push button of the encoder is double pushed  |
| RINC  | Encoder is rotated in the increment direction  |
| RDEC  | Encoder is rotated in the decrement direction  |
| RMAX  | Maximum threshold is reached  |
| RMIN  | Minimum threshold is reached  |

###### Example:
```python
 if  encoder.updateStatus() == True :
      if  encoder.readStatus(RINC) == True :
      	print ('Increment: %d' % (encoder.readCounter32())) 
      
      if  encoder.readStatus(RDEC) == True :
      	print ('Decrement: %d' % (encoder.readCounter32())) 

      if  encoder.readStatus(RMAX) == True :
      	print ('Max!') 

      if  encoder.readStatus(RMIN) == True :
      	print ('Min!')  

      if  encoder.readStatus(PUSHP) == True :
      	print ('Encoder pushed!')  
        
	  if  encoder.readStatus(PUSHR) == True :
      	print ('Encoder released!')   

      if  encoder.readStatus(PUSHD) == True :
      	print ('Encoder double pushed!')
```


##### readStatus()

Return the status of the register **ESTATUS**


### Reading methods
In this section are listed all the reading method available


##### readCounter32()
Return the counter value in the format **32bit int**, by reading all the 4 bytes of the counter value registers.



##### readCounter16()
Return the counter value in the format **16bit int**, by reading the 2 LSB  of the counter value registers.
Useful when the counter register is between the values -32768 to 32767.



##### readCounter8()
Return the counter value in the format **8bit int**, by reading the LSB byte of the counter value register.
Useful when the counter register is between the values -128 to 127



##### readMax()
Return the maximum threshold in format **32bit int**, bye reading all the 4 bytes of the counter Max.




##### readMin()
Return the minimum threshold in format **32bit int**, by reading all the 4 byte of the counter Min.



##### readStep()
Return the minimum threshold in format **32bit int**, by reading all the 4 bytes of the ISTEP registers.




##### readDoublePushPeriod()
Return the value of the DPPERIOD register. 



##### readIDCode()
Return the ID code of the I2C Encoder Mini, that is 0x39



##### readVersion()
Return the version of the board. 



##### readEEPROM(add)
Return the value of the EEPROM register. 
This function automatically manage the setting of the first and second memory bank.



### Writing methods
#####  writeCounter(value)
Write the counter value register with a  **32bit int** number. All of the 4 bytes are wrote.



#####  writeMax(max)
Write the Max register with a  **32bit int** number. All of the 4 bytes are wrote.



#####  writeMax(max)
Write the Max register with a  **float** number. All of the 4 bytes are wrote.



#####  writeMin(min)
Write the Min register with a **32bit int** number. All of the 4 bytes are wrote.



#####  writeStep(step)
Write the increment step  with a  **32bit int** number. All of the 4 bytes are wrote.



##### writeDoublePushPeriod(dperiod)
Write the DPPERIOD register.




##### writeEEPROM(add, data)
Write the EEPROM memory.
The input parameter *add* is the address. This method automatically change the first or the second bank.
The input parameter *data* is the data that will be written.

