/* 
 *  Digital output for Led Lamp. Requires amplification from logic level to 12v
*/

// number of pins
lamp1 = 40
lamp2 = 50

void setup() {
  pinMode(lamp1, OUTPUT);
  pinMode(lamp2, OUTPUT);
}

void loop() {
  digitalWrite(lamp1, HIGH);   
  digitalWrite(lamp2, LOW);   
  delay(1000);                       
  digitalWrite(lamp1, LOW);    
  digitalWrite(lamp2, HIGH);    
  delay(1000);                       
}


