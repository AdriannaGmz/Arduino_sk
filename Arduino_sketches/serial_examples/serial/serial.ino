// Simple Serial TX-RX communication, sends and prints digits

void setup(){
  Serial.begin(9600);
}


void loop(){
  while (Serial.available()==0); //wait to receive data
//  int valor = Serial.read();  // Reads Ascii values, for example, if I send 0, it reads 48
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


//  Serial.print("Rojo ");   //ard tarnsmits
//  Serial.print(15);
//  Serial.println(15);
//  delay(500);

}

