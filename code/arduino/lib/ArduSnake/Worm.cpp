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
//--  modules
//--------------------------------------------------------------
//-- (c) Juan Gonzalez-Gomez (Obijuan), David Estévez, Dec 2011
//-- GPL license
//--------------------------------------------------------------

#include <Servo.h>
#include <Oscillator.h>
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include <pins_arduino.h>
#endif
#include "Worm.h"

//-- Macro for converting from degrees to radians
#define DEG2RAD(g) ((g)*M_PI)/180

Worm::Worm()
{
  //-- Initially the robot consist of 0 servos
  _nservos=0;
  
  //-- Initial phase
  _phase0=0;
  
  //-- Initial phase difference
  _pd=-120;
}

void Worm::add_servo(int s,bool rev)
{
   Osc[_nservos].attach(s,rev);
   
   //-- Calculate the default phase
   Osc[_nservos].SetPh(DEG2RAD(_phase0 + _nservos*_pd));
   _nservos++;
}

void Worm::refresh()
{
  //-- Refresh the oscillators
  for (int i=0; i<_nservos; i++)
    Osc[i].refresh();
}


void Worm::set_wave(Wave w, int servo )
{
	//-- If a servo index is specified, it only changes that servo
	if (servo >= 0 && servo < _nservos)
	{
   		Osc[servo].SetA(w.A);
    		Osc[servo].SetO(w.O);
		Osc[servo].SetT(w.T);
		Osc[servo].SetPh(DEG2RAD(w.PD));
	}
	else
	{
 		for (int i=0; i<_nservos; i++) 
		{
   			Osc[i].SetA(w.A);
    			Osc[i].SetO(w.O);
			Osc[i].SetT(w.T);
			Osc[i].SetPh(DEG2RAD(w.PHASE0 + i*w.PD));
		}
	}

  _phase0=w.PHASE0;
}

void Worm::SetA(unsigned int A,  int servo)
{
	//-- If a servo index is specified, it only changes that servo
	if (servo >= 0 && servo < _nservos)
		Osc[servo].SetA(A);
	else
  		for (int i=0; i<_nservos; i++)
   			Osc[i].SetA(A);
}

void Worm::SetT(unsigned int T,  int servo)
{
	//-- If a servo index is specified, it only changes that servo
	if (servo >= 0 && servo < _nservos)
		Osc[servo].SetT(T);
	else
  		for (int i=0; i<_nservos; i++)
    			Osc[i].SetT(T);
}

void Worm::SetO(int O,  int servo)
{
	//-- If a servo index is specified, it only changes that servo
	if (servo >= 0 && servo < _nservos)
		Osc[servo].SetO(O);
	else
		for (int i=0; i<_nservos; i++)
		    Osc[i].SetO(O);
}

void Worm::SetPd(int Pd, int servo)
{
	//-- If a servo index is specified, it only changes that servo
	if (servo >= 0 && servo < _nservos)
		Osc[servo].SetPh(DEG2RAD(Pd));
	else
		for (int i=0; i<_nservos; i++)
		Osc[i].SetPh(DEG2RAD(_phase0 + i*Pd));
}

void Worm::SetPh0(int Ph0)
{
  _phase0 = Ph0;
  SetPd(_pd);
}




