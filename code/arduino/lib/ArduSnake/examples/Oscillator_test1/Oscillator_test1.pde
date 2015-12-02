//--------------------------------------------------------------
//-- ArduSnake library: Locomotion of modular snake robots
//-----------------------------------------------------------
//-- Layer: Oscillator
//------------------------------------------------------------
//-- Example of use of the Oscillator layer
//-- HELLO WORLD EXAMPLE!
//-- A Servo is oscillated using the default parameters
//------------------------------------------------------------
//-- This example works on the following boards:
//--   -skymega
//--   -Arduino
//-----------------------------------------------------------
//-- If using the skymega, connect the servo to SERVO #2 header
//-- If using Arduino, connect the servo to pin 8
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
}

//-- The servo will oscillate with the
//-- default parameters
void loop()
{
  //-- Refresh the oscillator
  osc.refresh();
}


