/*ECE 206 Lab 5*/
#include "arduino.h"

const int pwmPin = 6;

const int PIN_A = 8;
const int PIN_B = 9;

const int ulfilteredPIN = A0;
const int filteredPIN = A1;

bool A[2];
bool B[2];

int miniStep;
int tickCount = 0;

int PWM = 0;


long int lastLoopTime;
int loopTime = 100;

void setup() {
    pinMode(pwmPin, OUTPUT);
    Serial.begin(500000);
    pinMode(PIN_A, INPUT);
    pinMode(PIN_B, INPUT);
    pinMode(3,INPUT);

    pinMode(ulfilteredPIN,INPUT);
    pinMode(filteredPIN,  INPUT);
    A[0] = digitalRead(PIN_A);
    B[0] = digitalRead(PIN_B);
    A[1] = digitalRead(PIN_A);
    B[1] = digitalRead(PIN_B);
    miniStep = 0;
}

void loop() {
    detectEncoder();
    long int currTime = millis();
    if(currTime - lastLoopTime > loopTime) {
        char input = Serial.read();
        analogWrite(pwmPin, tickCount);
    }
    
    Serial.println("ulfiltered filtered MotorEncoder");
    Serial.println(String((analogRead(ulfilteredPIN)>500?5:0))+" "+ String(analogRead(filteredPIN)/1024.0*5.0)+" "+String(digitalRead(3)));
}

void detectEncoder() {
      /*** Rotation Detection ***/
    A[0] = A[1];
    B[0] = B[1];
    A[1] = digitalRead(PIN_A);
    B[1] = digitalRead(PIN_B);
    if((!A[0]&&!A[1]&&!B[0]&& B[1])||
       (!A[0]&& A[1]&& B[0]&& B[1])||
       ( A[0]&& A[1]&& B[0]&&!B[1])||
         A[0]&&!A[1]&&!B[0]&&!B[1]) { // Turn CW
        miniStep+=1;
        if(miniStep>=4) {
            miniStep = 0;
            tickCount-=1;
            if(tickCount<100) {
                tickCount = 254;
            }
        }
    } else if (!(A[0]==A[1]&&B[0]==B[1])) { // Turn CCW (Except same position, 
                                            // the rest condition was turning CCW)
        miniStep-=1;
        if(miniStep <= -4) {
            miniStep = 0;
            tickCount+=1;
            if(tickCount>=255) {
                tickCount = 100;
            }
        }
    }
    
}
