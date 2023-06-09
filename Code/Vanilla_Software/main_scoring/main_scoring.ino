/*
 * Code for Pinball Scoring Arduino
 * Mike Hilton, Eckerd College
 * 
 * This program implements the scoring functions
 * for the NA125 STEM course pinball machine.
 */

// If DEBUG is defined, debug messages will be printed to the serial monitor.  
#define DEBUG

#include "main_scoring.h"

#include "Debounce.h"

#include <Wire.h>
#define I2C_SOLENOID_ADDRESS 8    // solenoid nano
#define I2C_DISPLAY_ADDRESS 9     // display nano

// default values are used if no values are defined in main_scoring.h
#define DefaultScore 5            // number of points scored per switch activation
#define DefaultDelay 4            // debounce delay for switches (milliseconds)  
#define DefaultIgnoreWindow 40    // state change ignore window for switches (milliseconds)


/* 
 *  Defines for the 12 Opto-Isolated Switches
 */

#ifdef Switch1
#define Mask1   B00000010            // I/O pin D9,  Port B, pin 12 on Nano
Debounce *switch1;                   // debounced switch; state() = 1 if pressed, 0 if not pressed
// debounce delay for switch (milliseconds)
#ifndef Delay1
#define Delay1 DefaultDelay                        
#endif
// state change ignore window for switch (milliseconds)
#ifndef IgnoreWindow1
#define IgnoreWindow1 DefaultIgnoreWindow                
#endif
// score for this switch
#ifndef Score1
#define Score1 DefaultScore
#endif
#endif // Switch1

#ifdef Switch2
#define Mask2   B00000100          // I/O pin D10,  Port B, pin 13 on Nano
Debounce *switch2;                 // debounced switch; state() = 1 if pressed, 0 if not pressed
// debounce delay for switch (milliseconds)
#ifndef Delay2
#define Delay2 DefaultDelay                         
#endif
// state change ignore window for switch (milliseconds)
#ifndef IgnoreWindow2
#define IgnoreWindow2 DefaultIgnoreWindow                
#endif
// score for this switch
#ifndef Score2
#define Score2 DefaultScore
#endif
#endif // Switch2

#ifdef Switch3
#define Mask3   B00001000          // I/O pin D11,  Port B, pin 14 on Nano
Debounce *switch3;                 // debounced switch; state() = 1 if pressed, 0 if not pressed
// debounce delay for switch (milliseconds)
#ifndef Delay3
#define Delay3 DefaultDelay                         
#endif
// state change ignore window for switch (milliseconds)
#ifndef IgnoreWindow3
#define IgnoreWindow3 DefaultIgnoreWindow                
#endif
// score for this switch
#ifndef Score3
#define Score3 DefaultScore
#endif
#endif // Switch3

#ifdef Switch4
#define Mask4   B00010000          // I/O pin D12,  Port B, pin 15 on Nano
Debounce *switch4;                 // debounced switch; state() = 1 if pressed, 0 if not pressed
// debounce delay for switch (milliseconds)
#ifndef Delay4
#define Delay4 DefaultDelay                         
#endif
// state change ignore window for switch (milliseconds)
#ifndef IgnoreWindow4
#define IgnoreWindow4 DefaultIgnoreWindow                
#endif
// score for this switch
#ifndef Score4
#define Score4 DefaultScore
#endif
#endif // Switch4

#ifdef Switch5
#define Mask5   B00000001          // I/O pin A0,   Port C, pin 19 on Nano
Debounce *switch5;                 // debounced switch; state() = 1 if pressed, 0 if not pressed
// debounce delay for switch (milliseconds)
#ifndef Delay5
#define Delay5 DefaultDelay                         
#endif
// state change ignore window for switch (milliseconds)
#ifndef IgnoreWindow5
#define IgnoreWindow5 DefaultIgnoreWindow                
#endif
// score for this switch
#ifndef Score5
#define Score5 DefaultScore
#endif
#endif // Switch5

#ifdef Switch6
#define Mask6   B00000010          // I/O pin A1,   Port C, pin 20 on Nano
Debounce *switch6;                 // debounced switch; state() = 1 if pressed, 0 if not pressed
// debounce delay for switch (milliseconds)
#ifndef Delay6
#define Delay6 DefaultDelay                         
#endif
// state change ignore window for switch (milliseconds)
#ifndef IgnoreWindow6
#define IgnoreWindow6 DefaultIgnoreWindow                
#endif
// score for this switch
#ifndef Score6
#define Score6 DefaultScore
#endif
#endif // Switch6

#ifdef Switch7
#define Mask7   B00000100          // I/O pin A2,   Port C, pin 21 on Nano
Debounce *switch7;                 // debounced switch; state() = 1 if pressed, 0 if not pressed
// debounce delay for switch (milliseconds)
#ifndef Delay7
#define Delay7 DefaultDelay                         
#endif
// state change ignore window for switch (milliseconds)
#ifndef IgnoreWindow7
#define IgnoreWindow7 DefaultIgnoreWindow                
#endif
// score for this switch
#ifndef Score7
#define Score7 DefaultScore
#endif
#endif // Switch7

#ifdef Switch8
#define Mask8   B00001000          // I/O pin A3,   Port C, pin 22 on Nano
Debounce *switch8;                 // debounced switch; state() = 1 if pressed, 0 if not pressed
// debounce delay for switch (milliseconds)
#ifndef Delay8
#define Delay8 DefaultDelay                         
#endif
// state change ignore window for switch (milliseconds)
#ifndef IgnoreWindow8
#define IgnoreWindow8 DefaultIgnoreWindow                
#endif
// score for this switch
#ifndef Score8
#define Score8 DefaultScore
#endif
#endif // Switch8

#ifdef Switch9
#define Mask9 B00000100            // I/O pin D2,   Port D, pin 5 on Nano 
Debounce *switch9;                 // debounced switch; state() = 1 if pressed, 0 if not pressed
// debounce delay for switch (milliseconds)
#ifndef Delay9
#define Delay9 DefaultDelay                         
#endif
// state change ignore window for switch (milliseconds)
#ifndef IgnoreWindow9
#define IgnoreWindow9 DefaultIgnoreWindow                
#endif
// score for this switch
#ifndef Score9
#define Score9 DefaultScore
#endif
#endif // Switch9

#ifdef Switch10
#define Mask10 B00001000           // I/O pin D3,   Port D, pin 6 on Nano 
Debounce *switch10;                // debounced switch; state() = 1 if pressed, 0 if not pressed
// debounce delay for switch (milliseconds)
#ifndef Delay10
#define Delay10 DefaultDelay                         
#endif
// state change ignore window for switch (milliseconds)
#ifndef IgnoreWindow10
#define IgnoreWindow10 DefaultIgnoreWindow                
#endif
// score for this switch
#ifndef Score10
#define Score10 DefaultScore
#endif
#endif // Switch10

#ifdef Switch11
#define Mask11 B00010000           // I/O pin D4,   Port D, pin 7 on Nano 
Debounce *switch11;                // debounced switch; state() = 1 if pressed, 0 if not pressed
// debounce delay for switch (milliseconds)
#ifndef Delay11
#define Delay11 DefaultDelay                         
#endif
// state change ignore window for switch (milliseconds)
#ifndef IgnoreWindow11
#define IgnoreWindow11 DefaultIgnoreWindow                
#endif
// score for this switch
#ifndef Score11
#define Score11 DefaultScore
#endif
#endif // Switch11

#ifdef Switch12
#define Mask12 B00100000           // I/O pin D5,   Port D, pin 8 on Nano 
Debounce *switch12;                // debounced switch; state() = 1 if pressed, 0 if not pressed
// debounce delay for switch (milliseconds)
#ifndef Delay12
#define Delay12 DefaultDelay                         
#endif
// state change ignore window for switch (milliseconds)
#ifndef IgnoreWindow12
#define IgnoreWindow12 DefaultIgnoreWindow                
#endif
// score for this switch
#ifndef Score12
#define Score12 DefaultScore
#endif
#endif // Switch12


/*
 * Defines for the switches on the solenoid computer.  Information
 * about active switches is sent to this computer over the network.
 */
 
#ifdef Solenoid1
#ifndef SolenoidScore1
#define SolenoidScore1 DefaultScore
#endif
#endif // Solenoid 1

#ifdef Solenoid2
#ifndef SolenoidScore2
#define SolenoidScore2 DefaultScore
#endif
#endif // Solenoid 2

#ifdef Solenoid3
#ifndef SolenoidScore3
#define SolenoidScore3 DefaultScore
#endif
#endif // Solenoid 3

#ifdef Solenoid4
#ifndef SolenoidScore4
#define SolenoidScore4 DefaultScore
#endif
#endif // Solenoid 4

#ifdef Solenoid5
#ifndef SolenoidScore5
#define SolenoidScore5 DefaultScore
#endif
#endif // Solenoid 5

#ifdef Solenoid6
#ifndef SolenoidScore6
#define SolenoidScore6 DefaultScore
#endif
#endif // Solenoid 6

#ifdef Solenoid7
#ifndef SolenoidScore7
#define SolenoidScore7 DefaultScore
#endif
#endif // Solenoid 7

#ifdef Solenoid8
#ifndef SolenoidScore8
#define SolenoidScore8 DefaultScore
#endif
#endif // Solenoid 8

////// Global variables holding switch states from Solenoid computer
// 1 if pressed, 0 if not
int solenoid1, solenoid2, solenoid3, solenoid4;
int solenoid5, solenoid6, solenoid7, solenoid8;


////// Global variables associated with scoring
long int score = 0;       // current score
long int lastScore = 0;   // last score sent to display nano

void setup() {
  setupSwitches();

  // initialize I2C communications
  Wire.begin();
  
#ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Initialized");
#endif  
}


void loop() {
  readSwitches();
  readSolenoidData();

#ifdef DEBUG
  writeSwitchesToSerial(); 
#endif

  handleSwitches(); 
  handleSolenoidSwitches();

  if (lastScore != score) sendDisplayPacket();
}



void handleSolenoidSwitches() {
#ifdef Solenoid1
  if (solenoid1) {
    score += SolenoidScore1;
  }
#endif
#ifdef Solenoid2
  if (solenoid2) {
    score += SolenoidScore2;
  }
#endif
#ifdef Solenoid3
  if (solenoid3) {
    score += SolenoidScore3;
  }
#endif
#ifdef Solenoid4
  if (solenoid4) {
    score += SolenoidScore4;
  }
#endif
#ifdef Solenoid5
  if (solenoid5) {
    score += SolenoidScore5;
  }
#endif
#ifdef Solenoid6
  if (solenoid6) {
    score += SolenoidScore6;
  }
#endif
#ifdef Solenoid7
  if (solenoid7) {
    score += SolenoidScore7;
  }
#endif
#ifdef Solenoid8
  if (solenoid8) {
    score += SolenoidScore8;
  }
#endif
}


void handleSwitches() {
#ifdef Switch1  
  if (switch1->state() && !switch1->serviced) {
    score += Score1;
    switch1->serviced = true;
  }
#endif
#ifdef Switch2  
  if (switch2->state() && !switch2->serviced) {
    score += Score2;
    switch2->serviced = true;
  }
#endif
#ifdef Switch3  
  if (switch3->state() && !switch3->serviced) {
    score += Score3;
    switch3->serviced = true;
  }
#endif
#ifdef Switch4  
  if (switch4->state() && !switch4->serviced) {
    score += Score4;
    switch4->serviced = true;
  }
#endif
#ifdef Switch5  
  if (switch5->state() && !switch5->serviced) {
    score += Score5;
    switch5->serviced = true;
  }
#endif
#ifdef Switch6  
  if (switch6->state() && !switch6->serviced) {
    score += Score6;
    switch6->serviced = true;
  }
#endif
#ifdef Switch7  
  if (switch7->state() && !switch7->serviced) {
    score += Score7;
    switch7->serviced = true;
  }
#endif
#ifdef Switch8  
  if (switch8->state() && !switch8->serviced) {
    score += Score8;
    switch8->serviced = true;
  }
#endif
#ifdef Switch9  
  if (switch9->state() && !switch9->serviced) {
    score += Score9;
    switch9->serviced = true;
  }
#endif
#ifdef Switch10  
  if (switch10->state() && !switch10->serviced) {
    score += Score10;
    switch10->serviced = true;
  }
#endif
#ifdef Switch11  
  if (switch11->state() && !switch11->serviced) {
    score += Score11;
    switch11->serviced = true;
  }
#endif
#ifdef Switch12  
  if (switch12->state() && !switch12->serviced) {
    score += Score12;
    switch12->serviced = true;
  }
#endif
}


void readSolenoidData() {
  // Requests the switch data from the Solenoid computer, using I2C.
  // The data is unpacked into global switch variables
  
  int data1;
  Wire.requestFrom(I2C_SOLENOID_ADDRESS, 1);
  if(Wire.available()) {   
    // read the data
    data1 = (int)Wire.read();
   
    // tease out the switch information  
    solenoid1 = (data1 & 1) != 0;
    solenoid2 = (data1 & 2) != 0;
    solenoid3 = (data1 & 4) != 0;
    solenoid4 = (data1 & 8) != 0;
    solenoid5 = (data1 & 16) != 0;    
    solenoid6 = (data1 & 32) != 0;
    solenoid7 = (data1 & 64) != 0;  
    solenoid8 = (data1 & 128) != 0;
    
  } else {
#ifdef DEBUG    
    //Serial.println("No I2C");
#endif    
  }
}


void readSwitches() {  
  // Read the switch values from the opto-isolator board  
#ifdef Switch1  
  switch1->update((PINB & Mask1) == 0, millis()); 
#endif
#ifdef Switch2  
  switch2->update((PINB & Mask2) == 0, millis());   
#endif
#ifdef Switch3
  switch3->update((PINB & Mask3) == 0, millis()); 
#endif
#ifdef Switch4
  switch4->update((PINB & Mask4) == 0, millis()); 
#endif
#ifdef Switch5
  switch5->update((PINC & Mask5) == 0, millis()); 
#endif
#ifdef Switch6
  switch6->update((PINC & Mask6) == 0, millis()); 
#endif
#ifdef Switch7
  switch7->update((PINC & Mask7) == 0, millis()); 
#endif
#ifdef Switch8
  switch8->update((PINC & Mask8) == 0, millis()); 
#endif
#ifdef Switch9
  switch9->update((PIND & Mask9) == 0, millis()); 
#endif
#ifdef Switch10
  switch10->update((PIND & Mask10) == 0, millis()); 
#endif
#ifdef Switch11
  switch11->update((PIND & Mask11) == 0, millis()); 
#endif
#ifdef Switch12
  switch12->update((PIND & Mask12) == 0, millis()); 
#endif
}


void sendDisplayPacket() {
  // Send a packet of data across I2C to the display nano.

#ifdef DEBUG
 // Serial.println("Sending Display Packet");
#endif

  // prepare the packet
  byte bytes[5];
  bytes[0] = (byte)(score & 0xFF);
  bytes[1] = (byte)((score >> 8) & 0xFF);
  bytes[2] = (byte)((score >> 16) & 0xFF);
  bytes[3] = (byte) 0;  // TODO Sound ID, indicating what sound to play
  bytes[4] = (byte) 0;  // TODO NeoPixel routine ID

  // send the packet
  Wire.beginTransmission(I2C_DISPLAY_ADDRESS);
  Wire.write(bytes, 5);
  Wire.endTransmission();    
}


void setupSwitches() {   
#ifdef Switch1
  pinMode(9, INPUT_PULLUP);
  switch1 = new Debounce(Delay1, IgnoreWindow1);
#endif
#ifdef Switch2
  pinMode(10, INPUT_PULLUP);
  switch2 = new Debounce(Delay2, IgnoreWindow2);
#endif 
#ifdef Switch3
  pinMode(11, INPUT_PULLUP);
  switch3 = new Debounce(Delay3, IgnoreWindow3);
#endif
#ifdef Switch4
  pinMode(12, INPUT_PULLUP);
  switch4 = new Debounce(Delay4, IgnoreWindow4);
#endif
#ifdef Switch5
  pinMode(A0, INPUT_PULLUP);
  switch5 = new Debounce(Delay5, IgnoreWindow5);
#endif
#ifdef Switch6
  pinMode(A1, INPUT_PULLUP);
  switch6 = new Debounce(Delay6, IgnoreWindow6);
#endif
#ifdef Switch7
  pinMode(A2, INPUT_PULLUP);
  switch7 = new Debounce(Delay7, IgnoreWindow7);
#endif
#ifdef Switch8
  pinMode(A3, INPUT_PULLUP);
  switch8 = new Debounce(Delay8, IgnoreWindow8);
#endif
#ifdef Switch9
  pinMode(2, INPUT_PULLUP);
  switch9 = new Debounce(Delay9, IgnoreWindow9);
#endif
#ifdef Switch10
  pinMode(3, INPUT_PULLUP);
  switch10 = new Debounce(Delay10, IgnoreWindow10);
#endif
#ifdef Switch11
  pinMode(4, INPUT_PULLUP);
  switch11 = new Debounce(Delay11, IgnoreWindow11);
#endif
#ifdef Switch12
  pinMode(5, INPUT_PULLUP);
  switch12 = new Debounce(Delay12, IgnoreWindow12);
#endif
}




void writeSwitchesToSerial() {
  static String previous = "";
  String s = "";

  s = "SCORE = " + String(score) + " ";

#ifdef Switch1
  if (switch1->state()) s = s + " " + Switch1;
#endif
#ifdef Switch2
  if (switch2->state()) s = s + " " + Switch2;
#endif
#ifdef Switch3
  if (switch3->state()) s = s + " " + Switch3;
#endif
#ifdef Switch4
  if (switch4->state()) s = s + " " + Switch4;
#endif 
#ifdef Switch5
  if (switch5->state()) s = s + " " + Switch5;
#endif
#ifdef Switch6
  if (switch6->state()) s = s + " " + Switch6;
#endif
#ifdef Switch7
  if (switch7->state()) s = s + " " + Switch7;
#endif
#ifdef Switch8
  if (switch8->state()) s = s + " " + Switch8;
#endif
#ifdef Switch9
  if (switch9->state()) s = s + " " + Switch9;
#endif
#ifdef Switch10
  if (switch10->state()) s = s + " " + Switch10;
#endif
#ifdef Switch11
  if (switch11->state()) s = s + " " + Switch11;
#endif
#ifdef Switch12
  if (switch12->state()) s = s + " " + Switch12;
#endif

#ifdef Solenoid1
  if (solenoid1) s = s + " " + Solenoid1;
#endif
#ifdef Solenoid2
  if (solenoid2) s = s + " " + Solenoid2;
#endif
#ifdef Solenoid3
  if (solenoid3) s = s + " " + Solenoid3;
#endif
#ifdef Solenoid4
  if (solenoid4) s = s + " " + Solenoid4;
#endif
#ifdef Solenoid5
  if (solenoid5) s = s + " " + Solenoid5;
#endif
#ifdef Solenoid6
  if (solenoid6) s = s + " " + Solenoid6;
#endif
#ifdef Solenoid7
  if (solenoid7) s = s + " " + Solenoid7;
#endif
#ifdef Solenoid8
  if (solenoid8) s = s + " " + Solenoid8;
#endif


  if (previous != s) {
#ifdef DEBUG    
    Serial.println(s);
#endif    
  }
  previous = s;
}
