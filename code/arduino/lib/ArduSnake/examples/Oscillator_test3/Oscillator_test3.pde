//--------------------------------------------------------------
//-- ArduSnake library: Locomotion of modular snake robots
//-----------------------------------------------------------
//-- Layer: Oscillator
//------------------------------------------------------------
//-- Example of use of the Oscillator layer
//--
//-- Example 3: Two servos oscillating independenly, with different
//--  parameters
//--------------------------------------------------------------
//-- (c) Juan Gonzalez-Gomez (Obijuan), Feb-2012
//-- GPL license
//--------------------------------------------------------------
#include <Servo.h>
#include <Oscillator.h>
#include "skymega.h"

//-- Declare two oscillators
Oscillator osc[2];

void setup()
{
  //-- Attach the oscillators to the two servos
  //-- SERVO 2 and SERVO 4 for the skymega
  //-- If using arduino, you can use the pin numbers (8 and 9 for example)
  osc[0].attach(SERVO2);
  osc[1].attach(SERVO4);

  //-- Configure the oscillators
  //-- Oscillator 0
  osc[0].SetPh(DEG2RAD(0));
  osc[0].SetO(0);
  osc[0].SetA(45);
  osc[0].SetT(2000);
  
  //-- Oscillator 1
  osc[1].SetPh(DEG2RAD(-90));
  osc[1].SetO(40);
  osc[1].SetA(40);
  osc[1].SetT(4000);

}

void loop()
{
  //-- Refresh the oscillators
  for (int i=0; i<2; i++)
    osc[i].refresh(); 
}


