//Serial communication. between raspy and arduino.
//     according to nr received in arduino, turns on/off lamps/outputs
//     from terminal, we send (LOOK AT THE COMMA! IS SEPARATOR AND INDICATES NEW DATA
// 0,       turn off both lamps 
// 1,       turn on one lamp
// 2,       turn on lamp2
// 3,       turn off both

//DC Motor control with PWM and H-Bridgge
#define in2 49   //brown, 
#define in1 47   //red
#define enA 45   //green, PWM

// Serial
int lamp1 = 53;
int lamp2 = 52;
const int MaxChars = 2;     // we send only numbers from 0 to 3 and a comma
char strValue[MaxChars+1];
int index = 0;

String inString = "";    // string to hold input

int whichLamp = 0;

//Motors
const int MaxCharsM = 3;     // we send numbers v0... v9.   with vC = changes rotation  and a comma
char strValueM[MaxCharsM+1];
int indexM = 0;
int changeRotDirection = false;
int velMotor = 0;          // numbers v0... v9.   with vC = changes rotation
bool st_in1 = true;
bool st_in2 = false;

void setup(){
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(lamp1, OUTPUT);
  pinMode(lamp2, OUTPUT);
  
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  digitalWrite(in1, HIGH);  //bool st_in1 = true;    // initial rotation direction
  digitalWrite(in2, LOW);   //bool st_in2 = false;
}

void loop(){
  //here we do the thing about the motor control
  Serial.print("    This is whichLamp ");
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
    default:
      digitalWrite(LED_BUILTIN, LOW);                  
      digitalWrite(lamp1, LOW);    
      digitalWrite(lamp2, LOW);                
      break; 
    }
    
//    Serial.print("    This is velMotor ");
//    Serial.print(velMotor);
//    Serial.println();    
    int pwmOutput = map(velMotor, 0, 9, 0 , 255); // Map the serial vel value to 0:255
    Serial.print("    This is pwmOut ");
    Serial.print(pwmOutput);
    Serial.println();    

    analogWrite(enA, pwmOutput); // Send PWM signal to Enable pin 
    if (st_in1 == true){
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);  
    }
    if (st_in2 == true){
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);  
    }  
    if (changeRotDirection == true) {
      st_in1 = !st_in1;
      st_in2 = !st_in2;
      changeRotDirection = false;
    }
    
    
}

/// when serial event (always listening). Expects strings, reads char by char
void serialEvent(){
   while(Serial.available())   {
      int ch = Serial.read();
      Serial.print("This is ch ");
      Serial.write(ch);        //we write what we got  
      Serial.println();
        
      if(ch!=44) {        //this array is needed to store the complete byte and turn from ascii array into integer
            inString += (char)ch;
            //strValue[index++] = ch;
      } 
      if(ch==44){
//        Serial.print("          I have a comma ");
//        Serial.print("Value:");
//        Serial.println(inString.toInt());
//        Serial.print("String: ");
//        Serial.println(inString);
      
//        Serial.print("          my first is  ");            
//        Serial.print(inString[0]);  

        if (inString[0]!='v'){  
          whichLamp = inString.toInt();
        } else if(inString[0]=='v'){  
          if(inString[1]=='C'){velMotor = 0; changeRotDirection = true;}
          else{ velMotor = inString[1]-48; }   //ASCII numbers begin in 48 (zero). Just gets the first digit
        }

      // clear the string for new input:
      inString = "";
      }
   } 
}



