import smbus2
import RPi.GPIO as GPIO
from time import sleep
import i2cEncoderMiniLib


def EncoderChange():
    print ('Changed: %d' % (encoder.readCounter32()))

def EncoderPush():
    print ('Encoder Pushed!')
	
def EncoderRelease():
    print ('Encoder Released!')

def EncoderDoublePush():
    print ('Encoder Double Push!')

def EncoderLongPush():
    print ('Encoder Long Push!')

def EncoderMax():
    print ('Encoder max!')


def EncoderMin():
    print ('Encoder min!')


def Encoder_INT(self):
    encoder.updateStatus()


GPIO.setmode(GPIO.BCM)
bus = smbus2.SMBus(1)
INT_pin = 4
GPIO.setup(INT_pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)

encoder = i2cEncoderMiniLib.i2cEncoderMiniLib(bus, 0x20)

encconfig = ( i2cEncoderMiniLib.WRAP_ENABLE | i2cEncoderMiniLib.DIRE_RIGHT | i2cEncoderMiniLib.IPUP_ENABLE | i2cEncoderMiniLib.RMOD_X1)
encoder.begin(encconfig)

encoder.writeCounter(0)
encoder.writeMax(35)
encoder.writeMin(-20)
encoder.writeStep(1)
encoder.writeDoublePushPeriod(50)

encoder.onChange = EncoderChange
encoder.onButtonPush = EncoderPush
encoder.onButtonRelease = EncoderRelease
encoder.onButtonDoublePush = EncoderDoublePush
encoder.onButtonLongPush = EncoderLongPush
encoder.onMax = EncoderMax
encoder.onMin = EncoderMin

encoder.autoconfigInterrupt()
print ('Board ID code: 0x%X' % (encoder.readIDCode()))
print ('Board Version: 0x%X' % (encoder.readVersion()))


GPIO.add_event_detect(INT_pin, GPIO.FALLING, callback=Encoder_INT, bouncetime=10)

while True:
  #  if GPIO.input(INT_pin) == False: #
   #     Encoder_INT() #
    pass
