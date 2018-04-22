/*
    Led Lamps turn on
*/

// pins
int lamp1 = 52;
int lamp2 = 53;


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(lamp1, OUTPUT);
  pinMode(lamp2, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(lamp1, HIGH);    
  digitalWrite(lamp2, HIGH);
  delay(200);

  digitalWrite(LED_BUILTIN, LOW);  
  digitalWrite(lamp1, LOW);
  digitalWrite(lamp2, LOW);
  delay(200);

}

