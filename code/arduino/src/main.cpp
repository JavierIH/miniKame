#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Servo.h>
//#include <ctosnake.h>
#include "minikame.h"

const char* ssid = "kame";
const char* password = "asdf";

MiniKame robot;
WiFiServer server(80);
bool running=0;

void setup() {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);
    server.begin();
    Serial.begin(115200);

    delay(1000);
    robot.init();
}

void parseData(String data){

    //switch (data.substring(0,plusIndex).toInt()){
    switch (data.toInt()){

        case 1:
            robot.walk(1,550);
            running = 1;
            break;

        case 2:

            break;

        case 3:
            robot.turnL(1,550);
            running = 1;
            break;

        case 4:
            robot.turnR(1,550);
            running = 1;
            break;

        case 5:
            //STOP
            running = 0;
            break;

        case 6: //heart
            robot.pushUp(2,5000);
            break;

        case 7: //fire
            robot.upDown(4,250);
            break;

        case 8: //skull
            robot.jump();
            break;

        case 9: //cross
            robot.hello();
            break;

        case 10: //punch
        //robot.moonwalkL(4,2000);
        robot.frontBack(4,200);
            break;

        case 11: //mask
            robot.dance(2,1000);
            break;

        default:
            robot.home();
            break;
    }
}

String input;

void loop() {
    WiFiClient client = server.available();
    if (!client) {
        IPAddress myIP = WiFi.softAPIP();
        Serial.print("AP IP address: ");
        Serial.println(myIP);
        delay(1000);
    }
    while (client.connected()) {
        if (running){
            Serial.println("running");
            if (client.available()) {
                while(client.available()) input = client.readStringUntil('+');
                parseData(input);
            }
            else {
                Serial.println("Keep Moving");
                parseData(input);
            }
        }
        else{
            Serial.println("Normal mode");
            if (client.available()) {
                while(client.available()) input = client.readStringUntil('+');
                parseData(input);
            }
            else robot.home();
        }
    }
}
