//Raspy commands to Arduino
// turn on and off lamps 
//from terminal, we send (LOOK AT THE COMMA! IS SEPARATOR AND INDICATES NEW DATA
// 0,       turn off both lamps 
// 1,       turn on one lamp
// 2,        turn on lamp2
// 3,         turn off both

int lamp1 = 53;
int lamp2 = 52;
const int MaxChars = 2;     // we send only numbers from 0 to 3 and a comma
char strValue[MaxChars+1];
int index = 0;
int whichLamp = 0;

void setup(){
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(lamp1, OUTPUT);
  pinMode(lamp2, OUTPUT);
}

void loop(){
  //here we do the thing about the motor control
  Serial.print("This is what I receive ");
  Serial.print(whichLamp);
  Serial.println();
  delay(200);
  switch (whichLamp){
    case 0:
      digitalWrite(LED_BUILTIN, LOW);                  
      digitalWrite(lamp1, LOW);    
      digitalWrite(lamp2, LOW);                
      break;
    case 1:
      digitalWrite(LED_BUILTIN, HIGH);    
      digitalWrite(lamp1, HIGH);    
      digitalWrite(lamp2, LOW);    
      break;
    case 2:
      digitalWrite(LED_BUILTIN, LOW);                  
      digitalWrite(lamp1, LOW);    
      digitalWrite(lamp2, HIGH);    
      break;
    case 3:
      digitalWrite(LED_BUILTIN, HIGH);    
      digitalWrite(lamp1, HIGH);    
      digitalWrite(lamp2, HIGH);    
      break;
    }

  
  }


/// when serial event (always listening). Expects strings, reads char by char
void serialEvent(){
   while(Serial.available())   {
      char ch = Serial.read();
      Serial.write(ch);        
      if(isDigit(ch)) {  //this array is needed to store the complete byte and turn from ascii array into integer
            strValue[index++] = ch;
      } else {
            strValue[index] = 0;          //to complete the array, needs a zero at the end
            whichLamp = atoi(strValue);  //from ascii array to integer
//            switch (whichLamp){
//              case 0:
//                digitalWrite(LED_BUILTIN, LOW);                  
//                digitalWrite(lamp1, LOW);    
//                digitalWrite(lamp2, LOW);                
//                break;
//              case 1:
//                digitalWrite(LED_BUILTIN, HIGH);    
//                digitalWrite(lamp1, HIGH);    
//                digitalWrite(lamp2, LOW);    
//                break;
//              case 2:
//                digitalWrite(LED_BUILTIN, LOW);                  
//                digitalWrite(lamp1, LOW);    
//                digitalWrite(lamp2, HIGH);    
//                break;
//              case 3:
//                digitalWrite(LED_BUILTIN, HIGH);    
//                digitalWrite(lamp1, HIGH);    
//                digitalWrite(lamp2, HIGH);    
//                break;
//              }
            index = 0;
      }  
   }
}



