#include "Octosnake.h"
#include <Servo.h>

Oscillator::Oscillator(){
    _period = 2000;
    _amplitude = 50;
    _phase = 0;
    _offset = 0;
    _stop = true;
    _ref_time = millis();
    _delta_time = 0;
}

float Oscillator::refresh(){
    if (!_stop){
        _delta_time = (millis()-_ref_time) % _period;
        _output =   (float)_amplitude*sin(time_to_radians(_delta_time)
                    + degrees_to_radians(_phase))
                    + _offset;
    }

    return _output;
}

void Oscillator::reset(){
    _ref_time = millis();
}

void Oscillator::start(){
    reset();
    _stop = false;
}

void Oscillator::start(unsigned long ref_time){
    _ref_time = ref_time;
    _stop = false;
}

void Oscillator::stop(){
    _stop = true;
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

void Oscillator::setTime(unsigned long ref){
    _ref_time = ref;
}

float Oscillator::getOutput(){
    return _output;
}

unsigned long Oscillator::getTime(){
    return _ref_time;
}

float Oscillator::getPhaseProgress(){
    return ((float)_delta_time/_period) * 360;
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
