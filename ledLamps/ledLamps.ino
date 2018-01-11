/* 
 *  Digital output for Led Lamp. Requires amplification from logic level to 12v
*/

// number of pins
int lamp1 = 40;
int lamp2 = 50;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(lamp1, OUTPUT);
  pinMode(lamp2, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(lamp1, HIGH);   
  digitalWrite(lamp2, LOW);   
  delay(1000);                    
  digitalWrite(LED_BUILTIN, LOW);   
  digitalWrite(lamp1, LOW);    
  digitalWrite(lamp2, HIGH);    
  delay(1000);                       
}


