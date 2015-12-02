//--------------------------------------------------------------
//-- Worm Library. Generation of locomotion gaits in worm modular
//-- robots. A worm is defined as a 1D topology modular robot in
//-- which all the modules are connected in the same orientation,
//-- so that the worm only can move forward or backward
//--
//--  The locomotion is achieved by means os generating "waves".
//-- All the robot's servos perform a sinusoidal oscillation
//-- with the same parameters:
//--  T: Period (in ms)
//--  A: Amplitude (in deg)
//--  O: Offset (in deg)
//--  and a constant phase difference (PD) between two consecutive
//--  modules.
//--------------------------------------------------------------
//-- (c) Juan Gonzalez-Gomez (Obijuan), David Estévez, Dec 2011
//-- GPL license
//--------------------------------------------------------------

#ifndef Worm_h
#define Worm_h

#include <Oscillator.h>

//-- Maximum number of servos allowed
#define MAX_SERVOS 8

//-- Structure for defining a "wave"
struct wave_s {
  unsigned int T;  //-- Period (ms)
  unsigned int A;  //-- Amplitude (deg)
  int O;           //-- Offset (deg)
  int PD;          //-- Phase diff (deg)
  int PHASE0;      //-- Initial phase (deg)
};

typedef struct wave_s Wave;


//-- Class Worm: for implementing the locomotion of
//-- worm modular robots (in 1D)
class Worm 
{
  public:
  
    //-- Constructor
    Worm();
    
    //-- Add a new servo to the worm. It should be done
    //-- during the Setup
    void add_servo(int pin, bool rev=false);
    
    //-- Assign a "wave" to the worm
    void set_wave(Wave w, int servo = -1);
    
    //-- Set the amplitude (deg)
    void SetA(unsigned int A, int servo  = -1);
    
    //-- Set the period (ms)
    void SetT(unsigned int T, int servo  = -1);
    
    //-- Set the offset (deg)
    void SetO(int O, int servo  = -1);
    
    //-- Set the phase difference (deg)
    void SetPd(int Pd, int servo = -1);
    
    //-- Set the Initial phase (deg)
    void SetPh0(int Ph0);
    
    //-- Update the worm state. This method should be
    //-- called periodically from the main loop() function
    void refresh();
    
    
  private:
    //-- Number of servos in the robot
    int _nservos;
    
    //-- Oscilaltors
    Oscillator Osc[MAX_SERVOS];
    
    //-- Current initial phase
    int _phase0;
    
    //-- Current phase difference
    int _pd;
};

#endif


