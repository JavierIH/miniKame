#include "minikame.h"

int angToUsec(float value){
    return value/180 * (MAX_PULSE_WIDTH-MIN_PULSE_WIDTH) + MIN_PULSE_WIDTH;
}

void MiniKame::init(){
    board_pins[0] = D1;
    board_pins[1] = D4,
    board_pins[2] = D8;
    board_pins[3] = D6;
    board_pins[4] = D7;
    board_pins[5] = D5;
    board_pins[6] = D2;
    board_pins[7] = D3;

    trim[0] = 1;
    trim[1] = -8;
    trim[2] = 6;
    trim[3] = 4;
    trim[4] = 2;
    trim[5] = -5;
    trim[6] = 6;
    trim[7] = 2;

    //for(int i=0; i<8; i++) oscillator[i].setTrim(trim[i]);
    for(int i=0; i<8; i++) servo[i].attach(board_pins[i]);
    home();
}

void MiniKame::turnR(float steps, float T=600){
    int x_amp = 15;
    int z_amp = 15;
    int ap = 15;
    int hi = 23;
    float period[] = {T, T, T, T, T, T, T, T};
    int amplitude[] = {x_amp,x_amp,z_amp,z_amp,x_amp,x_amp,z_amp,z_amp};
    int offset[] = {90+ap,90-ap,90-hi,90+hi,90-ap,90+ap,90+hi,90-hi};
    int phase[] = {0,180,90,90,180,0,90,90};

    execute(steps, period, amplitude, offset, phase);
}

void MiniKame::turnL(float steps, float T=600){
    int x_amp = 15;
    int z_amp = 15;
    int ap = 15;
    int hi = 23;
    float period[] = {T, T, T, T, T, T, T, T};
    int amplitude[] = {x_amp,x_amp,z_amp,z_amp,x_amp,x_amp,z_amp,z_amp};
    int offset[] = {90+ap,90-ap,90-hi,90+hi,90-ap,90+ap,90+hi,90-hi};
    int phase[] = {180,0,90,90,0,180,90,90};

    execute(steps, period, amplitude, offset, phase);
}

void MiniKame::dance(float steps, float T=600){
    int x_amp = 0;
    int z_amp = 40;
    int ap = 30;
    int hi = 20;
    float period[] = {T, T, T, T, T, T, T, T};
    int amplitude[] = {x_amp,x_amp,z_amp,z_amp,x_amp,x_amp,z_amp,z_amp};
    int offset[] = {90+ap,90-ap,90-hi,90+hi,90-ap,90+ap,90+hi,90-hi};
    int phase[] = {0,0,0,270,0,0,90,180};

    execute(steps, period, amplitude, offset, phase);
}

void MiniKame::run(float steps, float T=5000){
    int x_amp = 15;
    int z_amp = 15;
    int ap = 15;
    int hi = 15;
    int front_x = 6;
    float period[] = {T, T, T, T, T, T, T, T};
    int amplitude[] = {x_amp,x_amp,z_amp,z_amp,x_amp,x_amp,z_amp,z_amp};
    int offset[] = {    90+ap-front_x,
                        90-ap+front_x,
                        90-hi,
                        90+hi,
                        90-ap-front_x,
                        90+ap+front_x,
                        90+hi,
                        90-hi
                    };
    int phase[] = {0,0,90,90,180,180,90,90};

    execute(steps, period, amplitude, offset, phase);
}

void MiniKame::moonwalkL(float steps, float T=5000){
    int z_amp = 45;
    float period[] = {T, T, T, T, T, T, T, T};
    int amplitude[] = {0,0,z_amp,z_amp,0,0,z_amp,z_amp};
    int offset[] = {90, 90, 90, 90, 90, 90, 90, 90};
    int phase[] = {0,0,0,120,0,0,180,290};

    execute(steps, period, amplitude, offset, phase);
}

void MiniKame::walk(float steps, float T=5000){
    volatile int x_amp = 15;
    volatile int z_amp = 20;
    volatile int ap = 20;
    volatile int hi = 10;
    volatile int front_x = 12;
    volatile float period[] = {T, T, T/2, T/2, T, T, T/2, T/2};
    volatile int amplitude[] = {x_amp,x_amp,z_amp,z_amp,x_amp,x_amp,z_amp,z_amp};
    volatile int offset[] = {   90+ap-front_x,
                                90-ap+front_x,
                                90-hi,
                                90+hi,
                                90-ap-front_x,
                                90+ap+front_x,
                                90+hi,
                                90-hi
                    };
    volatile int  phase[] = {90, 90, 270, 90, 270, 270, 90, 270};

    for (int i=0; i<8; i++){
        oscillator[i].reset();
        oscillator[i].setPeriod(period[i]);
        oscillator[i].setAmplitude(amplitude[i]);
        oscillator[i].setPhase(phase[i]);
        oscillator[i].setOffset(offset[i]);
    }

    _final_time = millis() + period[0]*steps;
    _init_time = millis();
    bool side;
    while (millis() < _final_time){
        side = (int)((millis()-_init_time) / (period[0]/2)) % 2;
        setServo(0, oscillator[0].refresh());
        setServo(1, oscillator[1].refresh());
        setServo(4, oscillator[4].refresh());
        setServo(5, oscillator[5].refresh());

        if (side == 0){
            setServo(3, oscillator[3].refresh());
            setServo(6, oscillator[6].refresh());
        }
        else{
            setServo(2, oscillator[2].refresh());
            setServo(7, oscillator[7].refresh());
        }
        delay(1);
    }
}

void MiniKame::jump(){
    float sentado[]={90+15,90-15,90-65,90+65,90+20,90-20,90+10,90-10};
    int ap = 20;
    int hi = 35;
    float salto[] = {90+ap,90-ap,90-hi,90+hi,90-ap*3,90+ap*3,90+hi,90-hi};
    moveServos(150, sentado);
    delay(200);
    moveServos(0, salto);
    delay(100);
    home();
}

void MiniKame::home(){
    int ap = 20;
    int hi = 35;
    int position[] = {90+ap,90-ap,90-hi,90+hi,90-ap,90+ap,90+hi,90-hi};
    for (int i=0; i<8; i++) setServo(i, position[i]);
}

void MiniKame::zero(){
    for (int i=0; i<8; i++) setServo(i, 90);
}

void MiniKame::setServo(int id, float target){
    servo[id].writeMicroseconds(angToUsec(target+trim[id]));
    _servo_position[id] = target;
}

float MiniKame::getServo(int id){
    return _servo_position[id];
}


void MiniKame::moveServos(int time, float target[8]) {
    if (time>10){
        for (int i = 0; i < 8; i++)	_increment[i] = (target[i] - _servo_position[i]) / (time / 10.0);
        _final_time =  millis() + time;

        while (millis() < _final_time){
            _partial_time = millis() + 10;
            for (int i = 0; i < 8; i++) setServo(i, _servo_position[i] + _increment[i]);
            while (millis() < _partial_time); //pause
        }
    }
    else{
        for (int i = 0; i < 8; i++) setServo(i, target[i]);
    }
    for (int i = 0; i < 8; i++) _servo_position[i] = target[i];
}

void MiniKame::execute(float steps, float period[8], int amplitude[8], int offset[8], int phase[8]){

    for (int i=0; i<8; i++){
        oscillator[i].setPeriod(period[i]);
        oscillator[i].setAmplitude(amplitude[i]);
        oscillator[i].setPhase(phase[i]);
        oscillator[i].setOffset(offset[i]);
    }

    unsigned long global_time = millis();

    for (int i=0; i<8; i++) oscillator[i].setTime(global_time);

    _final_time = millis() + period[0]*steps;
    while (millis() < _final_time){
        for (int i=0; i<8; i++){
            setServo(i, oscillator[i].refresh());
        }
        yield();
    }
}
