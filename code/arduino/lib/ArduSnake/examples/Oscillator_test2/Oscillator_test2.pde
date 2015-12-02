//--------------------------------------------------------------
//-- ArduSnake library: Locomotion of modular snake robots
//-----------------------------------------------------------
//-- Layer: Oscillator
//------------------------------------------------------------
//-- Example of use of the Oscillator layer
//--
//-- Example 2: Setting the oscillator parameters
//-- One servo is being oscillated using the parameters set by the user
//--------------------------------------------------------------
//-- (c) Juan Gonzalez-Gomez (Obijuan), Feb-2012
//-- GPL license
//--------------------------------------------------------------
#include <Servo.h>
#include <Oscillator.h>
#include "skymega.h"

//-- Declare an oscillator
Oscillator osc;

void setup()
{
  //-- Attach the oscillator to the servo
  //-- For arduino, you can use the pin number instead of SERVO2 (for example 8)
  osc.attach(SERVO2);
  
  //-------- Set the oscillator parameters
  //-- Set the offset. The servo will oscillate around this point
  //-- Units: Degrees. Default value: 0
  osc.SetO(40);
  
  //-- Set the Amplitude. How far the servo moves from the position
  //-- given by the offset. Units: degrees. Default value: 45
  osc.SetA(40);

  //-- Set the oscillation period. After one period the servo will be
  //-- in the same state. Units: ms. Default value: 2000
  osc.SetT(1000);

  //-- Set the Initial phase. It determines in which part of the cycle
  //-- the servo starts. So, this parameter determines the staring point
  osc.SetPh(DEG2RAD(-90));
}

void loop()
{
  //-- Refresh the oscillator
  osc.refresh();
}


