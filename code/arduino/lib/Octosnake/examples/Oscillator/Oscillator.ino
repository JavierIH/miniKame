/*
    Oscillator
    by JavierIH https://github.com/JavierIH/
    Octosnake example, it moves a servo
*/

#include <Servo.h>
#include <Octosnake.h>


Servo servo;
Oscillator oscillator;

void setup() {
    servo.attach(9);                // attaches the servo on pin 9 to the servo object
    oscillator.setOffset(90);       // sets an offset value to the output: 90º
    oscillator.setPeriod(1200);     // sets the oscillation period: 1200 ms
    oscillator.setAmplitude(50);    // sets the oscillation amplitude: 40º
    oscillator.setPhase(90);        // sets the oscillation phase: 90º

    oscillator.start();
}

void loop() {
    float output = oscillator.refresh();    // refresh the oscillator and return its value
    servo.write(output);                    // moves the servo to the oscillator output position
}
