/*
 * Opto-Isolator Board Testing Code for Pinball Computers
 * 
 * 
 */

// assign I/O pins
#define opto1 9
#define opto2 10
#define opto3 11
#define opto4 12
#define opto5 A0
#define opto6 A1
#define opto7 A2
#define opto8 A3
#define opto9 2
#define opto10 3
#define opto11 4
#define opto12 5

void setup() {
  Serial.begin(9600);
  
  pinMode(opto1, INPUT_PULLUP);
  pinMode(opto2, INPUT_PULLUP);
  pinMode(opto3, INPUT_PULLUP); 
  pinMode(opto4, INPUT_PULLUP);
  pinMode(opto5, INPUT_PULLUP);
  pinMode(opto6, INPUT_PULLUP);
  pinMode(opto7, INPUT_PULLUP);
  pinMode(opto8, INPUT_PULLUP);
  pinMode(opto9, INPUT_PULLUP);
  pinMode(opto10, INPUT_PULLUP);
  pinMode(opto11, INPUT_PULLUP);
  pinMode(opto12, INPUT_PULLUP);
    
}

void loop() {
  if (digitalRead(opto1) == LOW) Serial.println("1");
  if (digitalRead(opto2) == LOW) Serial.println("2");
  if (digitalRead(opto3) == LOW) Serial.println("3");
  if (digitalRead(opto4) == LOW) Serial.println("4");
  if (digitalRead(opto5) == LOW) Serial.println("5");
  if (digitalRead(opto6) == LOW) Serial.println("6");
  if (digitalRead(opto7) == LOW) Serial.println("7");
  if (digitalRead(opto8) == LOW) Serial.println("8");
  if (digitalRead(opto9) == LOW) Serial.println("9");
  if (digitalRead(opto10) == LOW) Serial.println("10");
  if (digitalRead(opto11) == LOW) Serial.println("11");  
  if (digitalRead(opto12) == LOW) Serial.println("12");  
}
