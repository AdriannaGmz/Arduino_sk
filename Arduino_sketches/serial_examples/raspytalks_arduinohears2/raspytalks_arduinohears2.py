# http://www.meccanismocomplesso.org/en/arduino-tutorial-serial-data-actuator/

import serial
arduinoSerialData = serial.Serial('/dev/ttyACM0',9600)
arduinoSerialData.write('5')

arduinoSerialData.write('3')