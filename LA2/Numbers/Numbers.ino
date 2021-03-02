int i = 0;
void setup() {
  // initialize digital pin 13 to drive LED
  for (int i = 0; i<=10; i++){
      pinMode(i, OUTPUT);
  }   // LED should go on
  for (int i = 11; i<=12; i++) {
    pinMode(i, INPUT);
  }
  digitalWrite(5, HIGH);
}

void snumber(int i, int digit){
  int sete[10][10] = {{1,2,3,7,8,10},{3,8},{1,2,4,7,8},{2,3,4,7,8},{3,4,8,10},{7,10,4,2,3},{7,10,4,3,1,2},{3,7,8},{1,2,3,4,7,8,10},{2,3,7,8,4,10}};
  int setd[10][10] = {{4},{1,2,4,7,10},{3,10},{1,10},{1,2,7},{1,8},{8},{1,2,4,10},{0},{1}};
  if (digit == 1) {
    digitalWrite(9, LOW);
    digitalWrite(6, HIGH);
  } else {
    digitalWrite(6, LOW);
    digitalWrite(9, HIGH);
  }
  for (int j = 0; j< 11; j++) {
    if(j!=6 && j!=9) {
        digitalWrite(j,HIGH);
    }
  }
  for (int j = 0; j< 10; j++) {
      if(sete[i][j]!=0) {
        digitalWrite(sete[i][j],LOW);
      }
  }
}

void number(int i, int delayTime) {
  unsigned long startTime = millis();
  if (i < 10) {
    snumber(i, 1);
    delay(delayTime);
  } else {
    while (millis()<startTime+delayTime) {
      snumber(i%10, 1);
      delay(10);
      snumber(int((i-i%10)/10),2);
      delay(10);
    }
  }
}

// infinite loop for real-time operation
void loop() {
  if(i<99) {
    i++;
    number(i,300);
  } else {
    i = 0;
    number(i,300);
  }
}
