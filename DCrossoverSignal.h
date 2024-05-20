#ifndef DCrossoverSignal_h
#define DCrossoverSignal_h

#include "Arduino.h"

class DoubleCrossover {
  public:
  DoubleCrossover(int pin);
  void SignalON();
  void SignalOFF();

  private:
  int _pin;
  
 };

#endif
