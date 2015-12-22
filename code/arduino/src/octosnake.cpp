#include "octosnake.h"
#include <Servo.h>

Oscillator::Oscillator(){
    _period = 2000;
    _amplitude = 50;
    _phase = 0;
    _offset = 0;
    _stop = false;
    _ref_time = millis();
    _delta_time = 0;
    _trim = 0;
}

float Oscillator::refresh(){
    _delta_time = (millis()-_ref_time) % _period;
    return      (float)_amplitude*sin(time_to_radians(_delta_time)
                + degrees_to_radians(_phase))
                + _offset
                + _trim;
}

void Oscillator::reset(){
    _ref_time = millis();
}

void Oscillator::setPeriod(int period){
    _period = period;
}

void Oscillator::setAmplitude(int amplitude){
    _amplitude = amplitude;
}

void Oscillator::setPhase(int phase){
    _phase = phase;
}

void Oscillator::setOffset(int offset){
    _offset = offset;
}

void Oscillator::setTrim(int trim){
    _trim = trim;
}

void Oscillator::setTime(unsigned long ref){
    _ref_time = ref;
}

unsigned long Oscillator::getTime(){
    return _ref_time;
}

float Oscillator::time_to_radians(double time){
    return time*2*PI/_period;
}

float Oscillator::degrees_to_radians(float degrees){
    return degrees*2*PI/360;
}

float Oscillator::degrees_to_time(float degrees){
    return degrees*_period/360;
}
