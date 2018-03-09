#include "Time.h"
//Communicating with raspby through serial communication
// Arduino sends a signal every 5 seconds 
// on the serial port, simulating the continuous detection by a sensor.
//Arduino talks, raspy hears

void setup() {
  Serial.begin(9600);
  setTime(12,0,0,1,1,11);
}

void loop() {
  Serial.print("I'm sending a message at ");
  Serial.print(hour());
  printDigits(minute());
  printDigits(seconds());
  Serial.println();
  delay(5000);
}

void printDigits(int digits()){
  Serial.print(":";
  if (digits < 10)
    Serial.print("0");
  Serial.print(digits);
  }
