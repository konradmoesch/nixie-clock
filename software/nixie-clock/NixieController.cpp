#include "Arduino.h"
#include "NixieController.hpp"
#include <ArduinoLog.h>

// SN74141 : True Table
//D C B A #
//L,L,L,L 0
//L,L,L,H 1
//L,L,H,L 2
//L,L,H,H 3
//L,H,L,L 4
//L,H,L,H 5
//L,H,H,L 6
//L,H,H,H 7
//H,L,L,L 8
//H,L,L,H 9

// SN74141
#define SN74141_A 2
#define SN74141_B 3
#define SN74141_C 4
#define SN74141_D 5
             
// anodes
#define ANODE_1 6
#define ANODE_2 7
#define ANODE_3 8
#define ANODE_4 9
#define ANODE_5 10
#define ANODE_6 11
const int anodes[] = {ANODE_1, ANODE_2, ANODE_3, ANODE_4, ANODE_5, ANODE_6}

void NixieController::initialize(){
  Log.noticeln("Initializing nixies");
  pinMode(SN74141_A, OUTPUT);      
  pinMode(SN74141_B, OUTPUT);      
  pinMode(SN74141_C, OUTPUT);      
  pinMode(SN74141_D, OUTPUT);    
  
  pinMode(ANODE_1, OUTPUT);      
  pinMode(ANODE_2, OUTPUT);      
  pinMode(ANODE_3, OUTPUT); 
  pinMode(ANODE_4, OUTPUT);    
  pinMode(ANODE_5, OUTPUT);      
  pinMode(ANODE_6, OUTPUT);  
}

int[] decimalTo4BitBinary(int decimal_number) {
  if (decimal_number > 15) {
    Log.errorln("error in decimal conversion: number too big");
    return;
  }
   int binaryNumber[4];
   int i = 0;
   while (decimal_number > 0) {
      binaryNumber[i] = decimal_number % 2;
      decimal_number = decimal_number / 2;
      i++;
   }
   return binaryNumber;
}

void displayDigit(int anode = 0, int digit) {
  int anodePin;
  int a,b,c,d;
    
  anodePin = anodes[anode];
  
  switch(digit) {
    case 0: a=0;b=0;c=0;d=0;break;
    case 1: a=1;b=0;c=0;d=0;break;
    case 2: a=0;b=1;c=0;d=0;break;
    case 3: a=1;b=1;c=0;d=0;break;
    case 4: a=0;b=0;c=1;d=0;break;
    case 5: a=1;b=0;c=1;d=0;break;
    case 6: a=0;b=1;c=1;d=0;break;
    case 7: a=1;b=1;c=1;d=0;break;
    case 8: a=0;b=0;c=0;d=1;break;
    case 9: a=1;b=0;c=0;d=1;break;
  }  
  
  digitalWrite(SN74141_D, d);
  digitalWrite(SN74141_C, c);
  digitalWrite(SN74141_B, b);
  digitalWrite(SN74141_A, a);

  digitalWrite(anodePin, HIGH);   
  delay(2);
  digitalWrite(anodePin, LOW);
}
