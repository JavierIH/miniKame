#ifndef minikame_h
#define minikame_h

#include <Servo.h>
#include "octosnake.h"

class MiniKame{

    public:
        MiniKame();
        void run(float steps, float period);
        void walk(float steps, float period);
        //void backward(float steps, float period);
        void turnL(float steps, float period);
        void turnR(float steps, float period);
        void dance(float steps, float period);
        //void jump();
        void home();
        void zero();

    private:
        Oscillator oscillator[8];
        Servo servo[8];
        int board_pins[8];
        int trim[8];

        int angToUsec(float value);
        void execute(float steps, float period[8], int amplitude[8], int offset[8], int phase[8]);
};

#endif
