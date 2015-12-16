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

void setup(){
    robot.home();
    Serial.begin(115200);
}

void loop(){
    //robot.home();
    //delay(5000);
    robot.walk(2, 250);
}
