//Communicating with raspby through serial communication
//raspy talks, arduino acts accordingly

// ready to receive commands from serial line. 
//The commands will be numbers between 0 and 9,
// which correspond to the frequency with which the LED 13 
// (the one built into the Arduino board) will blink.


const int ledPin = 13
int n;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  n=7;
}

void loop() {
  if(Serial.available()){
    n=Serial.read()-'0';
    }
  digitalWrite(ledPin,HIGH);
  delay(n*100);
  digitalWrite(ledPin,LOW);
  delay(n*100);
}
