//--------------------------------------------------------------
//-- ArduSnake library: Locomotion of modular snake robots
//-----------------------------------------------------------
//-- Layer: Oscillator
//------------------------------------------------------------
//-- OSCILLATOR SERVER V2.
//-- This firmware is for contrilling the oscillators from the PC
//-- It offers some services to the PC by a serial channel.
//-- Example of use of the Oscillator layer
//-- Controlling the oscillations from the PC.
//--------------------------------------------------------------
//-- (c) Juan Gonzalez-Gomez (Obijuan), Feb-2015
//-- GPL license
//--------------------------------------------------------------
//-- Serial commands for accesing the servos
//--
//-- The sintax is <servo_id><cmd_id>[<value>]<CMD_END>
//-- were:
//--
//--    <servo_id>: servo identificacion:  ASCII characters: a, b, c, d ....
//--    <cmd_id>: Type of frame (stop, play, SetA, SetO...)
//--    <angle>: Angle in degrees (in ASCII). The range is [-90, 90]. In some commands
//--             this field is not used
//--    <CMD_END>: End of Frame  (ASCII character CR)
//--
//--  Examples:
//--
//--      aP\r  -->  Play the oscillator on sevo a
//--      bS\r --> Stop the oscillator on servo b
//--      aA40\r --> Set the amplitude of Oscillator of servo a to 40 degrees

#include <Servo.h>
#include <Oscillator.h>

//-- CONSTANTS
const int led = 13;         //-- Led: for debugging
const int NSERVOS = 4;      //-- Number of servos controlled by the server


//-- Constant for the frames
const char CMD_END = '\r';  //-- Character end of frame
                            //-- CR is chosen for working with gtkterm correctly in Linux
                            //-- If the arduino terminal is used, Select the option "carriage return"

//-- Command id's                            
const unsigned char CMD_STOP = 'S';   //-- Stop the oscillaltor
const unsigned char CMD_PLAY = 'P';   //-- Play the oscillator
const unsigned char CMD_SET_A = 'A';  //-- Set Amplitude
const unsigned char CMD_SET_O = 'O';  //-- Set Offset
const unsigned char CMD_SET_P = 'H';  //-- Set phase
const unsigned char CMD_SET_T = 'T';  //-- Set Period
const unsigned char CMD_NONE = 0;
                            

//-- Array of oscillators
Oscillator osc[NSERVOS];


void setup()
{
  
  //-- Configure the led 
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  //-- Attach the oscillators to the servos
  osc[0].attach(9);
  osc[1].attach(8);
  osc[2].attach(7);
  osc[3].attach(6);

  //-- Initially the oscillators are stopped
  for (int i=0; i<NSERVOS; i++) {
    osc[i].Stop();
    //osc[i].SetA(10); //-- debugging!
  }  
    
  //Setup usb serial connection to computer
  Serial.begin(19200);
  delay(500);
  
  //-- Debug
  Serial.println("Server ready");

}

void loop()
{
  //-- Get and execute the commands
  getCommands();
}

//-- Command receiver state

const int WAITING_SERVO_ID = 1;
const int WAITING_CMD_ID = 2;
const int WAITING_VALUE = 3;
const int WAITING_END = 4;
int state = WAITING_SERVO_ID;  //-- Initial state

String inputString = "";        // a string to hold incoming data

int si;               //-- Servo index
int cmd = CMD_NONE;   //-- Command type
int value;            //-- Value
bool cmd_ok = false;


void getCommands()
{
  //-- Read the incoming commands
  while (Serial.available()) {
      
    //-- Read the received char
    char inChar = (char)Serial.read();
      
    //-- Depending on the state
    switch(state) {
        
      //-- Read the servo ID
      case WAITING_SERVO_ID:
        
        inputString = "";
        
        //-- Calculate the index
        si = inChar - 'a';
          
        //-- Only if the servo index is ok, the command is accepted
        if (si >= 0 && si < NSERVOS) {
          state = WAITING_CMD_ID;
        }
        //-- otherwise it is ignored. The state is not changed
        else {
          state = WAITING_SERVO_ID;
          Serial.println("Wrong Servo id");
        }
        break;
          
      //-- Read the cmd ID
      case WAITING_CMD_ID:
         cmd = inChar;
           
         //-- The next state depends on the command id
         switch(cmd) {
             
           case CMD_STOP:
           case CMD_PLAY:
             state = WAITING_END;
             break;
               
           case CMD_SET_O:
           case CMD_SET_A:
           case CMD_SET_P:
           case CMD_SET_T:
             state = WAITING_VALUE;
             break;
               
           //-- if the command is unknow, move to the initial state  
           default:
             state = WAITING_SERVO_ID;
             Serial.println("Wrong command");
         }
         break;  
         
       //-- Read the value field
       case WAITING_VALUE:
           
         //-- Check if inChar is a valid digit
         if (isdigit(inChar) || inChar=='-' || inChar == CMD_END) {
             
           //-- Add the char to the String for latter processing
           inputString += inChar;
             
           //-- when end of frame reached...
           if (inChar == CMD_END) {
             value = inputString.toInt();
             state = WAITING_SERVO_ID;
             cmd_ok = true;
             runCommand();
             //Serial.print(inputString);  //-- For debugging
           }
             
         }
         //-- Invalid digit
         else {
           //-- Move to the initial state. Invalid command
           state = WAITING_SERVO_ID;
           cmd_ok = false;
           Serial.println("Wrong value");
         }
         break;
         
       //-- Read the end of the frame
       case WAITING_END:
         
         //-- The next state is the initial, in any case
         state = WAITING_SERVO_ID;
         
         //-- End of frame received correctly
         if (inChar == CMD_END) {
           cmd_ok = true;             //-- The command is ok!
           runCommand();
         }  
         else {
           cmd_ok = false;   //-- Invalid frame. It will be ignored
         }
         break;
          
    } //-- End switch
      
  } //-- End While
  
   // Refresh the oscillators!
  for (int i = 0; i < NSERVOS; i++)
  {
    osc[i].refresh();
  }
}

void runCommand(){ 
  
  //-- If the frame received is ok... process!
  if (cmd_ok) {
    Serial.println("OK");
    
    switch(cmd) {
      
      //-- Command play
      case CMD_PLAY:
        osc[si].Play();
        break;
        
      //-- Command stop
      case CMD_STOP:
        osc[si].Stop();
        break;
      
      //-- Set the amplitude
      case CMD_SET_A:
        osc[si].SetA(abs(value));
        break;
        
      //-- Set the offset
      case CMD_SET_O:
        osc[si].SetO(value);
        break;
        
      //-- Set the phase
      case CMD_SET_P:
        osc[si].SetPh(DEG2RAD(value));
        break;
        
      //-- Set the period
      case CMD_SET_T:
        osc[si].SetT(abs(value));
        break;
    }
    
    cmd_ok = false;
  }
}


