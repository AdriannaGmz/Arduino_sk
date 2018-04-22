/* Simple program to read Maxbotix sonar 
MB7072, 7m max reach, closest readable distance 20cm, 10Hz
Big objects
*/

bool startsonar = false;
bool stayon = false;
const int anPin = 0;
long anVolt, mm,cm;

void setup() {
  Serial.begin(9600);
}

void read_sensor(){
  anVolt = analogRead(anPin);
  mm = anVolt * 5; //with supply of 5v
  cm = anVolt ;//this seems more reliable, lets use this one
}

void print_range(){
  Serial.print("Distance S1 = ");
  Serial.print(mm);
  Serial.println(" mm");
  Serial.print("\t\t AnalogVal = ");
  Serial.print(anVolt);
  Serial.println(" ");
}

void loop() {
  read_sensor();
  print_range();
  delay(500);
}
