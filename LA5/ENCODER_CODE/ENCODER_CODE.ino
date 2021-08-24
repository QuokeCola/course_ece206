/*ECE 206 Lab 5*/
#include "arduino.h"

int encoderPIN = 3;
int pastStep = 0;

long int lastLoopTime;
int loopTime = 100;

float currentRPM = 0.0f;

void setup() {
    Serial.begin(500000);
    attachInterrupt(digitalPinToInterrupt(encoderPIN), motorDetect, RISING);
}

void loop() {
    long int currTime = millis();
    if(currTime - lastLoopTime > loopTime) {
        currentRPM = float(pastStep)/144.0/float(loopTime)*1000.0f*60.0f;
        pastStep = 0;
        lastLoopTime = currTime;
    }
}

void motorDetect() {
    pastStep++;
}
