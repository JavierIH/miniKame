#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <Servo.h>
#include "octosnake.h"
#include "minikame.h"

const char* ssid = "ssid";
const char* password = "password";

MiniKame robot;
WiFiServer server(80);

void setup(){
    Serial.begin(115200);
    Serial.println("Setting WiFi connection...");
    WiFi.mode(WIFI_AP_STA);
    WiFi.disconnect();

    WiFi.begin(ssid, password);
    while (!MDNS.begin("minikame")){
        Serial.println("Setting MDNS...");
        delay(100);
    }

    server.begin();
    MDNS.addService("http", "tcp", 80);
    Serial.println(WiFi.localIP());

    delay(100);
    robot.init();
    Serial.println("Robot en marcha");
}

char command;

void loop(){
    //robot.home();
    WiFiClient client = server.available();
    while (client.connected()){
        command = client.read();
        Serial.println(command);
        switch (command){
            case 'W':
                robot.walk(2,400);
                break;
            case 'A':
                robot.turnL(2,400);
                break;
            case 'D':
                robot.turnR(2,400);
                break;
            case 'J':
                robot.jump();
                break;
            default:
                robot.home();
                break;
        }
    }
}
