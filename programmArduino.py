from nanpy import (ArduinoApi, SerialManager)
from time import sleep

#number of pins
ledPin = 7
buttonPin = 8
ledState = False
buttonState = 0

try:
	myConnection = SerialManager()   #automatically finds whatever Arduino is connected to this raspberry 
	# instance of the arduinoAPI option is as follows
	a = ArduinoApi(connection = myConnection)
except:   #this happens if fails
	print("Failed to connect to Arduino")

#then eerything is almost the same as in ArduinoIDE
#Setup the pinmodes as if we were in the Arduino IDE
a.pinMode(ledPin, a.OUTPUT)
a.pinMode(buttonPin, a.INPUT)

try: 
	while True:
		buttonState = a.digitalRead(buttonPin)
		print("Our button state is {}".format(buttonState))
		if buttonState:
			if ledState:
				a.digitalWrite(ledPin, a.LOW)
				ledState = False
				print("LED OFF")
				sleep(1)
			else:
				a.digitalWrite(ledPin, a.HIGH)
				ledState = True
				print("LED ON")
				sleep(1)
except:
	a.digitalWrite(ledPin, a.LOW)

