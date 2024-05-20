#include "DcrossoverSignal.h"
#include "Arduino.h"


DoubleCrossover::DoubleCrossover(int pin){
  pinMode(pin,OUTPUT);
  digitalWrite(pin,HIGH);
  _pin = pin;
}

void DoubleCrossover::SignalON(){
  digitalWrite(_pin,LOW);
}

void DoubleCrossover::SignalOFF(){
  digitalWrite(_pin,HIGH);
}

  
