/*
    Led Lamps turn on according to the sonar sound after the push button is pressed
    Requires amplification from logic level to 12v
*/

// pins
int interruptPin = 2;
int led1 = 48;
int led2 = 50;
int lamp1 = 22;
int lamp2 = 24;

bool startsonar = false;
bool stayon = false;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(lamp1, OUTPUT);
  pinMode(lamp2, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), activate_interr, RISING);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  if (startsonar == true) {
//    delay(1044);
    for (int i = 0; i<5; i++){    
      digitalWrite(lamp1, HIGH);    
      digitalWrite(lamp2, HIGH);
      digitalWrite(led1, HIGH);    
      digitalWrite(led2, HIGH);
      delay(1500);
      
      digitalWrite(lamp1, LOW);
      digitalWrite(lamp2, LOW);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      delay(2500);
    }
    startsonar=false;
    stayon= true;
  }  
  if (stayon== true){
    digitalWrite(lamp1, HIGH);    
    digitalWrite(lamp2, HIGH);
    digitalWrite(led1, HIGH);    
    digitalWrite(led2, HIGH);
  }
}

void activate_interr() {
  if ((startsonar ==false)&(stayon==false)){  startsonar = true;}
  if (stayon ==true){  stayon= false;}
}

