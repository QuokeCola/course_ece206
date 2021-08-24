#include <Arduino.h>

bool A[2];
bool B[2];
int miniStep;
int tickCount;
long int lastTime = millis();
bool digit=false;

#define PIN_A 11
#define PIN_B 12

void setup() {
    // Initialize LED
    for (int i = 1; i<=10; i++){
        pinMode(i, OUTPUT);
    }
    digitalWrite(5, HIGH); // Disable dot

    // Initialize Encoder
    pinMode(PIN_A, INPUT);
    pinMode(PIN_B, INPUT);
    A[0] = digitalRead(PIN_A);
    B[0] = digitalRead(PIN_B);
    A[1] = digitalRead(PIN_A);
    B[1] = digitalRead(PIN_B);
    miniStep = 0;
    Serial.begin(115200);
}

// infinite loop for real-time operation
void loop() {
    long int Time = millis();
    /*** Rotation Detection ***/
    A[0] = A[1];
    B[0] = B[1];
    A[1] = digitalRead(PIN_A);
    B[1] = digitalRead(PIN_B);
    Serial.println("A B");
    Serial.println(String(A[1])+ " " +String(B[1]));
    if((!A[0]&&!A[1]&&!B[0]&& B[1])||
       (!A[0]&& A[1]&& B[0]&& B[1])||
       ( A[0]&& A[1]&& B[0]&&!B[1])||
         A[0]&&!A[1]&&!B[0]&&!B[1]) { // Turn CW
        miniStep+=1;
        if(miniStep>=4) {
            miniStep = 0;
            tickCount-=1;
            if(tickCount<0) {
                tickCount = 99;
            }
        }
    } else if (!(A[0]==A[1]&&B[0]==B[1])) { // Turn CCW (Except same position, 
                                            // the rest condition was turning CCW)
        miniStep-=1;
        if(miniStep <= -4) {
            miniStep = 0;
            tickCount+=1;
            if(tickCount>=100) {
                tickCount = 0;
            }
        }
    }
    /*** Update Screen ***/
    if (Time - lastTime > 1) {  // Refresh latency [ms]
        if (tickCount < 10) {  // If it's a 1 digit number
            snumber(tickCount, 1);
        } else {                // If it's a 2 digit number
            if(digit == false) {// Showing first digit
                snumber(tickCount%10, 1);
            } else {            // Showing second digit
                snumber(int((tickCount-tickCount%10)/10),2);
            }
            digit = !digit;     // Switch the digit to shown
        }
        lastTime = Time;
    }
}

// function for showing a single number
void snumber(int i, int digit) {
    // Profiles for each number
    //                  0               1               2               3               4           5               6               7           8                   9
    int sete[10][10] = {{1,2,3,7,8,10}, {3,8},          {1,2,4,7,8},    {2,3,4,7,8},    {3,4,8,10}, {7,10,4,2,3},   {7,10,4,3,1,2}, {3,7,8},    {1,2,3,4,7,8,10},   {2,3,7,8,4,10}};
    int setd[10][10] = {{4},            {1,2,4,7,10},   {3,10},         {1,10},         {1,2,7},    {1,8},          {8},            {1,2,4,10}, {0},                {1}};
    // Digit
    if (digit == 1) {
        digitalWrite(9, LOW);
        digitalWrite(6, HIGH);
    } else {
        digitalWrite(6, LOW);
        digitalWrite(9, HIGH);
    }
    // Write HIGH digit
    for (int j = 0; j< 10; j++) {
        if(setd[i][j]!=0) {
            digitalWrite(setd[i][j],HIGH);
        }
    }
    // Write LOW digit
    for (int j = 0; j< 10; j++) {
        if(sete[i][j]!=0) {
            digitalWrite(sete[i][j],LOW);
        }
    }
}
