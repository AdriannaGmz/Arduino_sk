
//// Serial TX-RX commands for lamps and sonar. MOTORS to be added
//                    ASCII
//lamp1 on             l1n,     
//lamp2 on             l2n,     
//lamp1 off            l1f,     
//lamp2 off            l2f,     
//lamp1 toggle         l1t,
//lamp2 toggle         l2t,
//movements (front, back, left, right, stop):    mf,   mb,  ml,  mr, ms,



//Serial
int   ch;
String inString = "";

//Sonar
const int anPin = 0;
long anVolt, mm,cm;

//Lamps
int lamp1 = 53;
int lamp2 = 52;
int lampNr, lampAct;
boolean lampsJob = false;
boolean lamp1St =false;
boolean lamp2St =false;

//PressureSensor
#include <Wire.h>
#include "MS5837.h"
MS5837 sensor;


//Motors
boolean motorsJob = false;
int      mtrAct;
int      MotorA_orange = 8;         //pwm pins, check if available
int      MotorA_yellow = 9;         //two channels per motor to have front and backmovement on each drive
int      MotorB_orange = 10;
int      MotorB_yellow = 11;
// http://savagemakers.com/differential-drive-tank-drive-in-arduino/
//#define DDRIVE_MIN -100 //The minimum value x or y can be.
//#define DDRIVE_MAX 100  //The maximum value x or y can be.
//#define MOTOR_MIN_PWM -255 //The minimum value the motor output can be. WE USE MAX VELOCITIES
#define MOTOR_MAX_PWM 255 //The maximum value the motor output can be.
#define MOTOR_MED_PWM 127 //The maximum value the motor output can be.
#define MOTOR_MIN_PWM 0
int LeftMotorOutput_o; //will hold the calculated output for the left motor, channel orange
int LeftMotorOutput_y; //left motor, channel yellow
int RightMotorOutput_o; //will hold the calculated output for the right motor, channel orange
int RightMotorOutput_y; //right motor, channel yellow
int pwm_move;
// ----------- Encoders. Get velocity
//#include "Encoder.h"
#define RH_ENCODER_A 2     // pins for the encoder inputs   
#define RH_ENCODER_B 3     //2, 3, 18, 19, 20, 21 interrupt pins for mega
#define LH_ENCODER_A 18
#define LH_ENCODER_B 19
// variables to store the number of encoder pulses for each motor. 
volatile unsigned long leftCount = 0;
volatile unsigned long rightCount = 0;
//velocities
volatile long encoderPos_R=0;
long newposition_R;
long oldposition_R = 0;
unsigned long newtime_R;
unsigned long oldtime_R = 0;
long vel_R;
volatile long encoderPos_L=0;
long newposition_L;
long oldposition_L = 0;
unsigned long newtime_L;
unsigned long oldtime_L = 0;
long vel_L;



void setup(){
  pinMode(LED_BUILTIN, OUTPUT); //state as Lamp1
  pinMode(lamp1, OUTPUT);
  pinMode(lamp2, OUTPUT);
  
  
  // -------- pressureSensor
  Wire.begin();
  while (!sensor.init()) {
    Serial.println("Init failed!");
    Serial.println("Are SDA/SCL connected correctly?");
    Serial.println("Blue Robotics Bar30: White=SDA, Green=SCL");
    Serial.println("\n\n\n");
    delay(5000);
  }  
  sensor.setModel(MS5837::MS5837_30BA);
  sensor.setFluidDensity(997); // kg/m^3 (freshwater, 1029 for seawater)    
  // -------- 
   
   
   // -------- Motors,PWM
  pinMode(MotorA_orange, OUTPUT);
  pinMode(MotorA_yellow, OUTPUT);
  pinMode(MotorB_orange, OUTPUT);
  pinMode(MotorB_yellow, OUTPUT);
// -------- Encoders 
//  pinMode(LH_ENCODER_A, INPUT);     //tested.. now moving to other cfg
//  pinMode(LH_ENCODER_B, INPUT);
//  pinMode(RH_ENCODER_A, INPUT);
//  pinMode(RH_ENCODER_B, INPUT);
//  attachInterrupt(0, leftEncoderEvent, CHANGE);
//  attachInterrupt(1, rightEncoderEvent, CHANGE);
//According to https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
  pinMode(LH_ENCODER_A, INPUT_PULLUP);
  pinMode(LH_ENCODER_B, INPUT_PULLUP);
  pinMode(RH_ENCODER_A, INPUT_PULLUP);
  pinMode(RH_ENCODER_B, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(LH_ENCODER_A), leftEncoderEvent, CHANGE);
  attachInterrupt(digitalPinToInterrupt(RH_ENCODER_A), rightEncoderEvent, CHANGE);
  // -------- Motors,ENcoders - end



  Serial.begin(115200);   
}


void read_fromPC(){                     //   CONTROL. Here we just read and decypher commands
  while ( Serial.available() ){         //just when it receives data
    inString = Serial.readString();
    Serial.println(inString);
    
    if (inString[0]=='l'){              //Lamps 
      Serial.println("Lamps Cmd");
      lampsJob = true;
      lampNr =   inString[1]-'0';
      lampAct =  inString[2];        
      } 
      
      
    else if(inString[0]=='m'){          //Motor       
      Serial.println("Motors Cmd");
      motorsJob = true;      
      mtrAct =   inString[1];
      }       
      
    inString = "";    // clear the string for new input/command
    Serial.flush();
    }
}



void read_char(){
 while (Serial.available()==0); //wait to receive data
  int var = Serial.read()-'0';  //0AsCII is 48decimal, 1ASCII is 49decimal, etc
  Serial.println(var);
  if(var==0){
    Serial.println("I received command 0");    
  } else if (var==0){
    Serial.println("I received command 1");    
  } else{
    Serial.print("This is what arduino received: ");
    Serial.println(var);
  }  
  Serial.flush();  //after the first read character, throws away the rest
}


void read_sonar(){
  anVolt = analogRead(anPin);
  cm = anVolt;
  print_sonar();
}

void print_sonar(){
  Serial.println(" \n     ---- SONAR SENSOR");
  Serial.print("Big object detected at ");
  Serial.print(anVolt);
  Serial.println(" cm ");
}


void read_pressure(){
  sensor.read();
  print_pressure();
}



void print_pressure(){
  Serial.println(" \n     ---- PRESSURE SENSOR");
  Serial.println("Pressure [mbar], Temperature [°C], Depth [m], Altitude [m] above mean sea level "); 
  Serial.print(sensor.pressure()); 
  Serial.print("            ");
  Serial.print(sensor.temperature()); 
  Serial.print("            ");
  Serial.print(sensor.depth()); 
  Serial.print("            ");
  Serial.println(sensor.altitude()); 
}



void lamps_job(){
  Serial.print("Lampnr = ");
  Serial.print(lampNr);
  Serial.print("\t action = ");
  Serial.println(lampAct);
  
  if (lampNr == 1){
    if (lampAct == 'n') { digitalWrite(lamp1, HIGH); digitalWrite(LED_BUILTIN, HIGH); lamp1St = true;} 
    else if (lampAct == 'f') { digitalWrite(lamp1, LOW); digitalWrite(LED_BUILTIN, LOW);lamp1St = false;} 
    else if (lampAct == 't') { 
      if(lamp1St == false){ digitalWrite(lamp1, HIGH); digitalWrite(LED_BUILTIN, HIGH); lamp1St = true;} 
      else if(lamp1St == true){ digitalWrite(lamp1, LOW); digitalWrite(LED_BUILTIN, LOW); lamp1St = false;} 
    }

  }else if (lampNr == 2){
    if (lampAct == 'n') { digitalWrite(lamp2, HIGH); lamp2St = true;} 
    else if (lampAct == 'f') { digitalWrite(lamp2, LOW); lamp2St = false;} 
    else if (lampAct == 't') { 
      if(lamp2St == false){ digitalWrite(lamp2, HIGH); lamp2St = true;} 
      else if(lamp2St == true){ digitalWrite(lamp2, LOW); lamp2St = false;} 
    }    
  }
  lampsJob = false;
}



void motors_job(){  //differential drive pwm for movements: front, back, right, left, stop
  Serial.print("MtrCommand = ");
  Serial.println(mtrAct);
  pwm_move = MOTOR_MED_PWM;  //or MOTOR_MAX_PWM;
  switch (mtrAct) {
    case 'f':           //front
      LeftMotorOutput_o = pwm_move;
      LeftMotorOutput_y = MOTOR_MIN_PWM;
      RightMotorOutput_o= pwm_move;
      RightMotorOutput_y= MOTOR_MIN_PWM;
      break;
    case 'b':          //back
      LeftMotorOutput_o = MOTOR_MIN_PWM;
      LeftMotorOutput_y = pwm_move;
      RightMotorOutput_o= MOTOR_MIN_PWM;
      RightMotorOutput_y= pwm_move;
      break;
    case 'l':           //left
      LeftMotorOutput_o = MOTOR_MIN_PWM;
      LeftMotorOutput_y = pwm_move;
      RightMotorOutput_o= pwm_move;
      RightMotorOutput_y= MOTOR_MIN_PWM;
      break;
    case 'r':        //right
      LeftMotorOutput_o = pwm_move;
      LeftMotorOutput_y = MOTOR_MIN_PWM;
      RightMotorOutput_o= MOTOR_MIN_PWM;
      RightMotorOutput_y= pwm_move;
      break;
    case 's':        //stop
      LeftMotorOutput_o = MOTOR_MIN_PWM;
      LeftMotorOutput_y = MOTOR_MIN_PWM;
      RightMotorOutput_o= MOTOR_MIN_PWM;
      RightMotorOutput_y= MOTOR_MIN_PWM;
      break;
    default:
      LeftMotorOutput_o = MOTOR_MIN_PWM;
      LeftMotorOutput_y = MOTOR_MIN_PWM;
      RightMotorOutput_o= MOTOR_MIN_PWM;
      RightMotorOutput_y= MOTOR_MIN_PWM;
      break;
    analogWrite(MotorA_orange, LeftMotorOutput_o);
    analogWrite(MotorA_yellow, LeftMotorOutput_y);
    analogWrite(MotorB_orange, RightMotorOutput_o);
    analogWrite(MotorB_yellow, LeftMotorOutput_y);
  }
  

  
  motorsJob = false;
}

void encoderVelocities(){
    //reading velocities... to test!   https://forum.arduino.cc/index.php?topic=158385.0
  newposition_R = rightCount;
  newposition_L = leftCount;
  newtime_L = millis(); //but should be the same than R... todo: merge in one newtime
    newtime_R = millis();
  vel_R = (newposition_R-oldposition_R) * 1000 /(newtime_R-oldtime_R);
  vel_L = (newposition_L-oldposition_L) * 1000 /(newtime_L-oldtime_L);
  Serial.print ("speed_R = ");
  Serial.println (vel_R);
  Serial.print ("speed_L = ");
  Serial.println (vel_L);
  oldposition_R = newposition_R;
    oldposition_L = newposition_L;
  oldtime_R = newtime_R;
    oldtime_L = newtime_L;
//  delay(250);
  }



// encoder event for the interrupt calls. Counts
void leftEncoderEvent() {
  if (digitalRead(LH_ENCODER_A) == HIGH) {
    if (digitalRead(LH_ENCODER_B) == LOW) {
      leftCount++;
    } else {
      leftCount--;
    }
  } else {
    if (digitalRead(LH_ENCODER_B) == LOW) {
      leftCount--;
    } else {
      leftCount++;
    }
  }
}

void rightEncoderEvent() {
  if (digitalRead(RH_ENCODER_A) == HIGH) {
    if (digitalRead(RH_ENCODER_B) == LOW) {
      rightCount++;
    } else {
      rightCount--;
    }
  } else {
    if (digitalRead(RH_ENCODER_B) == LOW) {
      rightCount--;
    } else {
      rightCount++;
    }
  }
}






void loop() {
  // Sending data
  read_fromPC();
  read_sonar();
  read_pressure();
///  read_char();   //only for testing
  
  // Reading data, i.e. control from outside
  if(lampsJob==true){lamps_job();}
  if(motorsJob==true){motors_job();encoderVelocities();}  

  Serial.println("This is getting better.. ");
  delay(500);
}
