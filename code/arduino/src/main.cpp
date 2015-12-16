#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <Servo.h>
#include "octosnake.h"

const char* ssid = "ssid";
const char* password = "password";
Oscillator oscillator[8];
Servo servo[8];
int board_pins[] = {D1, D4, D8, D6, D7, D5, D2, D3};
int trim[] = {1, -8, 8, 4, 2, -5, 6, 2};

int angToUsec(float value){
    int usecs = value/180 * (MAX_PULSE_WIDTH-MIN_PULSE_WIDTH) + MIN_PULSE_WIDTH;
    return usecs;
}

void execute(float steps, float period[8], int amplitude[8], int offset[8], int phase[8]){
    for (int i=0; i<8; i++){
        oscillator[i].setPeriod(period[i]);
        oscillator[i].setAmplitude(amplitude[i]);
        oscillator[i].setPhase(phase[i]);
        oscillator[i].setOffset(offset[i]);
    }

    unsigned long final = millis() + period[0]*steps;
    while (millis() < final){
        for (int i=0; i<8; i++){
            servo[i].writeMicroseconds(angToUsec(oscillator[i].refresh()));
            Serial.println("");
        }
    }
}

void turnR(float steps, float T=5000){
    int x_amp = 15;//15;
    int z_amp = 15;//15;
    int ap = 15;//15;
    int hi = 15;
    float period[] = {T, T, T, T, T, T, T, T};
    int amplitude[] = {x_amp,x_amp,z_amp,z_amp,x_amp,x_amp,z_amp,z_amp};
    int offset[] = {90+ap,90-ap,90-hi,90+hi,90-ap,90+ap,90+hi,90-hi};
    int phase[] = {0,180,90,90,180,0,90,90};

    execute(steps, period, amplitude, offset, phase);
}

void turnL(float steps, float T=5000){
    int x_amp = 15;//15;
    int z_amp = 15;//15;
    int ap = 15;//15;
    int hi = 15;
    float period[] = {T, T, T, T, T, T, T, T};
    int amplitude[] = {x_amp,x_amp,z_amp,z_amp,x_amp,x_amp,z_amp,z_amp};
    int offset[] = {90+ap,90-ap,90-hi,90+hi,90-ap,90+ap,90+hi,90-hi};
    int phase[] = {180,0,90,90,0,180,90,90};

    execute(steps, period, amplitude, offset, phase);
}

void dance(float steps, float T=5000){
    int x_amp = 0;//15;
    int z_amp = 40;//15;
    int ap = 30;//15;
    int hi = 20;
    float period[] = {T, T, T, T, T, T, T, T};
    int amplitude[] = {x_amp,x_amp,z_amp,z_amp,x_amp,x_amp,z_amp,z_amp};
    int offset[] = {90+ap,90-ap,90-hi,90+hi,90-ap,90+ap,90+hi,90-hi};
    int phase[] = {0,0,0,270,0,0,90,180};

    execute(steps, period, amplitude, offset, phase);
}


void run(float steps, float T=5000){
    int x_amp = 15;//15;
    int z_amp = 15;//15;
    int ap = 15;//15;
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

void walk(float steps, float T=5000){
    int x_amp = 15;
    int z_amp = 15;
    int ap = 20;
    int hi = 15;
    int front_x = 12;
    float period[] = {T, T, T/2, T/2, T, T, T/2, T/2};
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
    int  phase[] = {90, 90, 270, 90, 270, 270, 90, 270};

    for (int i=0; i<8; i++){
        oscillator[i].reset();
        oscillator[i].setPeriod(period[i]);
        oscillator[i].setAmplitude(amplitude[i]);
        oscillator[i].setPhase(phase[i]);
        oscillator[i].setOffset(offset[i]);
    }

    unsigned long final = millis() + period[0]*steps;
    unsigned long init = millis();
    while (millis() < final){
        int side = (int)((millis()-init) / (period[0]/2)) % 2;
        servo[0].writeMicroseconds(angToUsec(oscillator[0].refresh()));
        servo[1].writeMicroseconds(angToUsec(oscillator[1].refresh()));
        servo[4].writeMicroseconds(angToUsec(oscillator[4].refresh()));
        servo[5].writeMicroseconds(angToUsec(oscillator[5].refresh()));
        if (side == 0){
            servo[3].writeMicroseconds(angToUsec(oscillator[3].refresh()));
            servo[6].writeMicroseconds(angToUsec(oscillator[6].refresh()));
        }
        else{
            servo[2].writeMicroseconds(angToUsec(oscillator[2].refresh()));
            servo[7].writeMicroseconds(angToUsec(oscillator[7].refresh()));
        }
    }
}

void home(){
    int ap = 20;
    int hi = 35;
    int position[] = {90+ap,90-ap,90-hi,90+hi,90-ap,90+ap,90+hi,90-hi};
    for (int i=0; i<8; i++) servo[i].writeMicroseconds(angToUsec(position[i])+trim[i]);
}

void zero(){
    for (int i=0; i<8; i++) servo[i].writeMicroseconds(angToUsec(90+trim[i]));
}

void setup(){
    Serial.begin(115200);
    for(int i=0; i<8; i++) servo[i].attach(board_pins[i]);
    for(int i=0; i<8; i++) oscillator[i].setTrim(trim[i]);
}

void loop(){
    zero();
    delay(5000);
    home();
    delay(5000);
    //walk(2, 250);
}
