#include <Servo.h>
#include <Oscillator.h>

Oscillator osc;

void setup()
{
    osc.attach(9);
}

void loop()
{
    delay(100);
}
