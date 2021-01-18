void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  float vout = analogRead(A0)/1024.*5;
  float vc = analogRead(A1)/1024.*5; 
  Serial.println("Vout Vc");
  Serial.println(String(vout)+" "+String(vc));
}
