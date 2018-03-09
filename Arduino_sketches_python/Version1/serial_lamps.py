#Hears the serial port

import serial
from time import sleep

ser = serial.Serial('/dev/ttyACM0',9600)

for item in range (0,3):
  ser.write('0,')
  sleep(1)
  ser.write('1,')
  sleep(1)
  ser.write('2,')
  sleep(1)
  ser.write('3,')
  sleep(1)

while 1:
	print(ser.read())