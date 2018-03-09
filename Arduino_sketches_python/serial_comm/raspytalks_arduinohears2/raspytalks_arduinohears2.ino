//Communicating with raspby through serial communication
//http://www.meccanismocomplesso.org/en/arduino-tutorial-serial-data-actuator//

#include Servo 

Servo myservo;
int angle = 0;
int newAngle = 0;
const int MaxChars = 4;
char strValue[MaxChars+1];
int index = 0;

void setup(){
  Serial.begin(9600);
  myservo.attach(10);
  angle = 90;
}

void loop()
{}

// Finally, define a new function called serialEvent(). 
//This feature, although it is not included within the loop(), 
///is always listening, and when a serial event is captured by 
//the Arduino board, as in our case, the sending from the PC 
//to a numeric value, the serialEvent function is activated, 
//and the code inside is executed.

void serialEvent()
{
   while(Serial.available())
   {
      char ch = Serial.read();
      Serial.write(ch);
      if(index < MaxChars && isDigit(ch)) {
            strValue[index++] = ch;
      } else {
            strValue[index] = 0;
            newAngle = atoi(strValue);
            if(newAngle > 0 && newAngle < 180){
                   if(newAngle < angle)
                       for(; angle > newAngle; angle -= 1) {
                             myservo.write(angle);
                       }  
                    else
                       for(; angle < newAngle; angle += 1){
                          myservo.write(angle);
                    }
            }
            index = 0;
            angle = newAngle;
      }  
   }
}



