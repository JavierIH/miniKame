//--------------------------------------------------------------
//-- ArduSnake library: Locomotion of modular snake robots
//-----------------------------------------------------------
//-- Layer: Oscillator
//------------------------------------------------------------
//-- OSCILLATOR SERVER.
//-- This firmware is for contrilling the oscillators from the PC
//-- It offers some services to the PC by a serial channel.
//-- Example of use of the Oscillator layer
//-- Controlling the oscillations from the PC.
//--------------------------------------------------------------
//-- (c) Juan Gonzalez-Gomez (Obijuan), Feb-2012
//-- GPL license
//--------------------------------------------------------------
#include <Servo.h>
#include <Oscillator.h>
#include "skymega.h"
#include "freeleds.h"

//-- Serial commands
const unsigned char CMD_STOP = 'S';  //-- Stop the oscillaltor
const unsigned char CMD_PLAY = 'P';  //-- Play the oscillator
const unsigned char CMD_SET_A= 'A';  //-- Set Amplitude

//-- Declare the oscillators
Oscillator osc[8];

void setup()
{
  freeleds_setup();
  
  //-- Configure the serial comunication with PC
  Serial.begin(9600);

  //-- Attach the oscillators to the servos
  osc[1].attach(SERVO2);
  osc[3].attach(SERVO4);
  osc[5].attach(SERVO6);
  osc[7].attach(SERVO8);

  //-- Initially the oscillators are stopped
  for (int i=0; i<8; i++)
    osc[i].Stop();

  //-- The oscillator is configured with the default parameters
  freeleds_display(0xAA);
}

//-- Incoming byte from the PC
unsigned char inbyte;
char nosc;  //-- Oscillator number
char cmd;   //-- Command
char A;     //-- Amplitude
void loop()
{
  //-- refresh the oscillators
  for (int i=0; i<8; i++) 
    osc[i].refresh();

  //-- When a byte is received from the PC
  if (Serial.available()) {

    //-- Process the frame
    //-- The first byte is the oscillator number (in ASCII), characters '0'-'7'
    
    //-- Read the oscillator number
    nosc = Serial.read() - '1';
    freeleds_display(nosc);
    
    //-- Read the command
    while(!Serial.available());
    cmd = Serial.read();
    freeleds_display(cmd);
    
    //-- Depending on the command... execute the action!
    switch(cmd){
      case CMD_STOP:     //-- Stop command
        osc[nosc].Stop();
        Serial.println("Stop");
        break;

      case CMD_PLAY:     //-- Play command
        osc[nosc].Play();
        Serial.println("Play");
        break;

      case CMD_SET_A:
        Serial.println("SetA");
        //-- Read the amplitude
        while(!Serial.available());
        A = Serial.read();
	osc[nosc].SetA(A);
    }
    
    
  }
}


