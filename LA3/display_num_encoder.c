int total_rotation = 0;
int last_a = 0;

void setup() {
 DDRD = B11011110;
 DDRB = B000111; 
}

void loop() {
  int a = digitalRead(12);
  int b = digitalRead(13);

  if((last_a==LOW)&&(a==HIGH)&&(b==LOW)){
    total_rotation++;
  }
  if((last_a==HIGH)&&(a==LOW)&&(b==LOW)){
    total_rotation--;
  }
  total_rotation = constrain(total_rotation, 0, 99);

 int left_digit = total_rotation / 10;
 int right_digit = total_rotation % 10;

 display_num(left_digit, 1);
 display_num(right_digit, 0);

 last_a = a;
}

void display_num(int i, int left){
 if (i==0){
  PORTD = B01110001;
  PORTB = B111010;
 }
 if (i==1){
  PORTD = B11110111;
  PORTB = B111110;
 }
 if (i==2){
  PORTD = B01101001;
  PORTB = B111110;
 }
 if (i==3){
  PORTD = B01100011;
  PORTB = B111110;
 }
 if (i==4){
  PORTD = B11100111;
  PORTB = B111010;
 }
 if (i==5){
  PORTD = B01100011;
  PORTB = B111011;
 }
 if (i==6){
  PORTD = B01100001;
  PORTB = B111011;
 }
 if (i==7){
  PORTD = B01110111;
  PORTB = B111110;
 }
 if (i==8){
  PORTD = B01100001;
  PORTB = B111010;
 }
 if (i==9){
  PORTD = B01100011;
  PORTB = B111010;
 }
 if (left==0){
  PORTD = PORTD | B01000000;
  PORTB = PORTB & B111101;
 }
 if (left == 1){
  PORTD = PORTD & B10111111;
  PORTB = PORTB | B000010;
 }
 delay(1);
}
