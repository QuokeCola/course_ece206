int total_rotation = 0; //this is a global variable all functions can access
int last_a = 0;

// one time run setup function
void setup() {
  // initialize digital pins 12/13 to be inputs (channels A and B respectively)
  pinMode(12, INPUT);
  pinMode(13, INPUT);
}

// infinite loop for real-time operation
void loop() {
	int a = digitalRead(12);//read pin 12, call it 'a'
	int b = digitalRead(13);//read pin 13, call it 'b'

	if ((last_a == LOW) && (a == HIGH)){
		//if A has gone from low to high 
		//you should do something here depending on B
	}
		if ((last_a == HIGH) && (a == LOW)){
		//if A has gone from high to low 
		//you should do something here depending on B
	}
	
	//display the new value here on the LED
	
	last_a = a; //update last_a
}