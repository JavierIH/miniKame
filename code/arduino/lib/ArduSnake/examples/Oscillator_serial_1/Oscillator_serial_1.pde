//--------------------------------------------------------------
//-- ArduSnake library: Locomotion of modular snake robots
//-----------------------------------------------------------
//-- Layer: Oscillator
//------------------------------------------------------------
//-- Example of use of the Oscillator layer
//-- Controlling the oscillations from the PC.
//--
//-- One servo is attached to an oscillator. Initially it is stoped
//-- From the PC it is possible to change the state (stop/play) by 
//-- sending the commands Stop and Play (characteres S and P)
//--------------------------------------------------------------
//-- (c) Juan Gonzalez-Gomez (Obijuan), Feb-2012
//-- GPL license
//--------------------------------------------------------------
#include <Servo.h>
#include <Oscillator.h>
#include "skymega.h"

//-- Serial commands
const unsigned char CMD_STOP = 'S';  //-- Stop the oscilaltor
const unsigned char CMD_PLAY = 'P';  //-- Play the oscillator

//-- Declare two oscillators
Oscillator osc;

void setup()
{
  //-- Configure the serial comunication with PC
  Serial.begin(9600);

  //-- Attach the oscillator to servo
  osc.attach(SERVO2);

  //-- Initially the oscillator is stoped
  osc.Stop();

  //-- The oscillator is configured with the default parameters
}

//-- Incoming byte from the PC
unsigned char inbyte;

void loop()
{
  //-- refresh the oscillator
  osc.refresh();

  //-- When a byte is received from the PC
  if (Serial.available()) {

    //-- Read the byte and modify the oscillator state
    //-- acording to the command received
    inbyte = Serial.read();
    switch(inbyte){
      case CMD_STOP:     //-- Stop command
        osc.Stop();
        break;
      case CMD_PLAY:     //-- Play command
        osc.Play();
        break;
    }
  }
}


