# signal sent from the Arduino will be received by Raspberry through the serial port (USB) ttyACM0
# Arduino talks, raspy hears
import serial 
arduinoSerialData = serial.Serial('/dev/ttyACM0',9600)
while 1:
   if(arduinoSerialData.inWaiting()>0):
      myData = arduinoSerialData.readline()
      print myData
