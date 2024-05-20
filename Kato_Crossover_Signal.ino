#include "DCrossoverSignal.h"
#include "Arduino.h"



int switch1pin1=2;//set up digital pin 2 for controlling switch 1
int switch1pin2=3;//set up digital pin 3 for controlling switch 1
int button=A0;//set up analog pin A0 for reading button 1
int button2=A1;
DoubleCrossover R1(4);
DoubleCrossover Y1(5);
DoubleCrossover G1(6);
DoubleCrossover R2(7);
DoubleCrossover Y2(8);
DoubleCrossover G2(9);
DoubleCrossover R3(10);
DoubleCrossover Y3(11);
DoubleCrossover G3(12);
DoubleCrossover R4(13);
DoubleCrossover Y4(14);
DoubleCrossover G4(15);
DoubleCrossover R5(16);
DoubleCrossover Y5(17);
DoubleCrossover G5(18);
DoubleCrossover R6(19);
DoubleCrossover Y6(20);
DoubleCrossover G6(21);
DoubleCrossover R7(22);
DoubleCrossover Y7(23);
DoubleCrossover G7(24);
DoubleCrossover R8(25);
DoubleCrossover Y8(26);
DoubleCrossover G8(27);
int State1=0;//Sets our value for the state of switch 1
int State2=0;

void setup() {
  Serial.begin(9600);//sets up our readings in the serial monitor and the baud rate of 9600
  pinMode(switch1pin1,OUTPUT);
  pinMode(switch1pin2,OUTPUT);
  
  pinMode(button,INPUT);
  pinMode(button2,INPUT);
}
enum SWITCHSTATES
{
  ST_OFF,
  ST_STRAIGHT,
  ST_TURN,
  ST_RESET,
  ST_CHANGE1,
  ST_CHANGE2,
};//Sets up states that arduino can hop between

SWITCHSTATES switchState=ST_OFF;

void loop(){
  //Serial.println("State 1");
  //Serial.println(State1);//display in serial monitor what the State of State 1 is with the text "State 1" in front.
  

int ButtonRead=analogRead(button);//Stores value for button1
int Button2Read=analogRead(button2);
  Serial.println("Button");
  Serial.println(ButtonRead);//display in serial monitor what the State of Button 1 is with the text "Button 1" in front.
  Serial.println(Button2Read);
  Serial.println(State1);
  Serial.println(State2);
  delay(200);// 0.2 second pause between readings
  switch(switchState)
  {
    case ST_OFF:
    switchoff(ButtonRead, Button2Read, State1, State2);
    break;
    case ST_STRAIGHT:
    switchstraight(ButtonRead);
    break;
    case ST_TURN:
    switchturn(ButtonRead);
    break;
    case ST_RESET:
    switchreset(ButtonRead);
    break;
    case ST_CHANGE1:
    switchchange1();
    break;
    case ST_CHANGE2:
    switchchange2();
    break;
    
  }
}

void switchoff(int ButtonRead, int Button2Read, int State1, int State2){
  digitalWrite(switch1pin1,LOW);
  digitalWrite(switch1pin2,LOW);
if ((ButtonRead<500) && (Button2Read<500) && (State1==0) && (State2==0)){
  G1.SignalON();
  R2.SignalON();
  G3.SignalON();
  R4.SignalON();
  R5.SignalON();
  R6.SignalON();
  R7.SignalON();
  R8.SignalON();
}
if ((ButtonRead<500) && (Button2Read<500) &&  ((State1==1) && (State2 ==1))||(State1==0) && (State2 ==2)){
  R1.SignalON();
  R2.SignalON();
  R3.SignalON();
  R4.SignalON();
  R5.SignalON();
  R6.SignalON();
  R7.SignalON();
  R8.SignalON();
}
if ((ButtonRead<500) && (Button2Read<500) && (State1==0) && (State2 ==1)){
  R1.SignalON();
  R2.SignalON();
  R3.SignalON();
  R4.SignalON();
  G5.SignalON();
  R6.SignalON();
  G7.SignalON();
  R8.SignalON();
}
if ((ButtonRead<500) && (Button2Read<500) && (State1==1) && (State2 ==0)){
  R1.SignalON();
  R2.SignalON();
  R3.SignalON();
  R4.SignalON();
  R5.SignalON();
  R6.SignalON();
  R7.SignalON();
  R8.SignalON();
}
if ((ButtonRead<500) && (Button2Read<500) && (State1==1) && (State2 ==1)){
  R1.SignalON();
  R2.SignalOFF();
  G2.SignalON();
  R3.SignalON();
  R4.SignalON();
  R5.SignalON();
  R6.SignalON();
  R7.SignalON();
  R8.SignalON();
}
if ((ButtonRead<500) && (Button2Read<500) && (State1==1) && (State2 ==2)){
  R1.SignalON();
  R2.SignalON();
  R3.SignalON();
  G4.SignalON();
  R5.SignalON();
  R6.SignalON();
  R7.SignalON();
  R8.SignalON();
}
if ((ButtonRead<500) && (Button2Read<500) && (State1==1) && (State2 ==3)){
  R1.SignalON();
  R2.SignalON();
  R3.SignalON();
  R4.SignalON();
  R5.SignalON();
  G6.SignalON();
  R7.SignalON();
  R8.SignalON();
}
if ((ButtonRead<500) && (Button2Read<500) && (State1==1) && (State2 ==4)){
  R1.SignalON();
  R2.SignalON();
  R3.SignalON();
  R4.SignalON();
  R5.SignalON();
  R6.SignalON();
  R7.SignalON();
  G8.SignalON();
}
   if ((Button2Read>500) && (State2<=3)){
     switchState=ST_CHANGE1;
 }
    if ((Button2Read>500) && (State1==0) && (State2==2)){
     switchState=ST_CHANGE2;
 }   
    if ((Button2Read>500) && (State2>3)){
     switchState=ST_CHANGE2;    
 }
  if ((ButtonRead>500) && (State1==1)){
    switchState=ST_STRAIGHT;//sends to straight 1 with button press
  }
  if ((ButtonRead>500) && (State1==0)){
    switchState=ST_TURN;//sends to turn 1 with button press
  }

}

void switchstraight(int ButtonRead){
  digitalWrite(switch1pin1,HIGH);//powers on turnout
  digitalWrite(switch1pin2,LOW);
  delay(500);//keep power to the turnout for 0.5 seconds
  State1=0;//sets value to 0
  switchState=ST_RESET;
}

void switchturn(int ButtonRead){
  digitalWrite(switch1pin1,LOW);
  digitalWrite(switch1pin2,HIGH);//powers on turnout
  delay(500);//keep power to the turnout for 0.5 seconds
State1=1;//sets value to 1
State2=0;
  switchState=ST_RESET;
}

void switchchange1(){;
State2=(State2+1);
delay(500);
switchState=ST_RESET;
}

void switchchange2(){;
State2=0;
delay(500);
switchState=ST_RESET;
}

void switchreset(int ButtonRead){
  R1.SignalOFF();
  Y1.SignalOFF();
  G1.SignalOFF();
  R2.SignalOFF();
  Y2.SignalOFF();
  G2.SignalOFF();
  R3.SignalOFF();
  Y3.SignalOFF();
  G3.SignalOFF();
  R4.SignalOFF();
  Y4.SignalOFF();
  G4.SignalOFF();
  R5.SignalOFF();
  Y5.SignalOFF();
  G5.SignalOFF();
  R6.SignalOFF();
  Y6.SignalOFF();
  G6.SignalOFF();
  R7.SignalOFF();
  Y7.SignalOFF();
  G7.SignalOFF();
  R8.SignalOFF();
  Y8.SignalOFF();
  G8.SignalOFF();
  delay(10);
  switchState=ST_OFF;
    
    
}
