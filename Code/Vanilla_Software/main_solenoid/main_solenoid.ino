/* 
 *  Pinball Solenoid-Side Main Code for Arduino Nano
 *  Mike Hilton, Eckerd College
 *  
 *  This program implements the solenoid side of the pinball machine,
 *  which is controlled by an Arduino Nano. There are eight possible  
 *  solenoid actuators, each with an associated switch.  When a switch
 *  is closed, the associated solenoid fires.

 *  
 *  This Arduino is configured as an I2C slave and the Scoring Arduino
 *  is the I2C master.  This Arduino sends the switch state information
 *  to the master.
 */

// If DEBUG is defined, debug messages will be printed to the serial monitor.  
#define DEBUG

#include "main_solenoid.h"

// Debounced switch class
#include "Debounce.h"

 // I2C communication info
#include <Wire.h>
#define I2C_MY_ADDRESS 8

#ifdef Solenoid1
#define SolenoidMask1 B00000100    // I/O pin D2,   Port D, pin 5 on Nano 
#define SwitchMask1   B00000010    // I/O pin D9,  Port B, pin 12 on Nano
Debounce *switch1;                 // debounced switch; state() = 1 if pressed, 0 if not pressed
int IsFiring1;                     // 1 if solenoid is firing, 0 if not
unsigned long ExpirationTime1;     // time when firing should stop
// debounce delay for switch (milliseconds)
#ifndef Delay1
#define Delay1 4                         
#endif
// duration of solenoid firing, in milliseconds
#ifndef FiringDuration1
#define FiringDuration1 ((unsigned long) 40) 
#endif
// state change ignore window for switch (milliseconds)
#ifndef IgnoreWindow1
#define IgnoreWindow1 40                
#endif
#endif // Solenoid1

#ifdef Solenoid2
#define SolenoidMask2 B00001000    // I/O pin D3,   Port D, pin 6 on Nano 
#define SwitchMask2   B00000100    // I/O pin D10,  Port B, pin 13 on Nano
Debounce *switch2;                 // debounced switch; state() = 1 if pressed, 0 if not pressed
int IsFiring2;                     // 1 if solenoid is firing, 0 if not
unsigned long ExpirationTime2;     // time when firing should stop
// debounce delay for switch (milliseconds)
#ifndef Delay2
#define Delay2 4                         
#endif
// duration of solenoid firing, in milliseconds
#ifndef FiringDuration2
#define FiringDuration2 ((unsigned long) 40) 
#endif
// state change ignore window for switch (milliseconds)
#ifndef IgnoreWindow2
#define IgnoreWindow2 40                
#endif
#endif // Solenoid2

#ifdef Solenoid3
#define SolenoidMask3 B00010000    // I/O pin D4,   Port D, pin 7 on Nano 
#define SwitchMask3   B00001000    // I/O pin D11,  Port B, pin 14 on Nano
Debounce *switch3;                 // debounced switch; state() = 1 if pressed, 0 if not pressed
int IsFiring3;                     // 1 if solenoid is firing, 0 if not
unsigned long ExpirationTime3;     // time when firing should stop
// debounce delay for switch (milliseconds)
#ifndef Delay3
#define Delay3 4                         
#endif
// duration of solenoid firing, in milliseconds
#ifndef FiringDuration3
#define FiringDuration3 ((unsigned long) 40) 
#endif
// state change ignore window for switch (milliseconds)
#ifndef IgnoreWindow3
#define IgnoreWindow3 40                
#endif
#endif // Solenoid3

#ifdef Solenoid4
#define SolenoidMask4 B00100000    // I/O pin D5,   Port D, pin 8 on Nano 
#define SwitchMask4   B00010000    // I/O pin D12,  Port B, pin 15 on Nano
Debounce *switch4;                 // debounced switch; state() = 1 if pressed, 0 if not pressed
int IsFiring4;                     // 1 if solenoid is firing, 0 if not
unsigned long ExpirationTime4;     // time when firing should stop
// debounce delay for switch (milliseconds)
#ifndef Delay4
#define Delay4 4                         
#endif
// duration of solenoid firing, in milliseconds
#ifndef FiringDuration4
#define FiringDuration4 ((unsigned long) 40) 
#endif
// state change ignore window for switch (milliseconds)
#ifndef IgnoreWindow4
#define IgnoreWindow4 40                
#endif
#endif // Solenoid4

#ifdef Solenoid5
#define SolenoidMask5 B01000000    // I/O pin D6,   Port D, pin 9 on Nano 
#define SwitchMask5   B00000001    // I/O pin A0,   Port C, pin 19 on Nano
Debounce *switch5;                 // debounced switch; state() = 1 if pressed, 0 if not pressed
int IsFiring5;                     // 1 if solenoid is firing, 0 if not
unsigned long ExpirationTime5;     // time when firing should stop
// debounce delay for switch (milliseconds)
#ifndef Delay5
#define Delay5 4                         
#endif
// duration of solenoid firing, in milliseconds
#ifndef FiringDuration5
#define FiringDuration5 ((unsigned long) 40) 
#endif
// state change ignore window for switch (milliseconds)
#ifndef IgnoreWindow5
#define IgnoreWindow5 40                
#endif
#endif // Solenoid5

#ifdef Solenoid6
#define SolenoidMask6 B10000000    // I/O pin D7,   Port D, pin 10 on Nano 
#define SwitchMask6   B00000010    // I/O pin A1,   Port C, pin 20 on Nano
Debounce *switch6;                 // debounced switch; state() = 1 if pressed, 0 if not pressed
int IsFiring6;                     // 1 if solenoid is firing, 0 if not
unsigned long ExpirationTime6;     // time when firing should stop
// debounce delay for switch (milliseconds)
#ifndef Delay6
#define Delay6 4                         
#endif
// duration of solenoid firing, in milliseconds
#ifndef FiringDuration6
#define FiringDuration6 ((unsigned long) 40) 
#endif
// state change ignore window for switch (milliseconds)
#ifndef IgnoreWindow6
#define IgnoreWindow6 40                
#endif
#endif // Solenoid6

#ifdef Solenoid7
#define SolenoidMask7 B00000001    // I/O pin D8,   Port B, pin 11 on Nano 
#define SwitchMask7   B00000100    // I/O pin A2,   Port C, pin 21 on Nano
Debounce *switch7;                 // debounced switch; state() = 1 if pressed, 0 if not pressed
int IsFiring7;                     // 1 if solenoid is firing, 0 if not
unsigned long ExpirationTime7;     // time when firing should stop
// debounce delay for switch (milliseconds)
#ifndef Delay7
#define Delay7 4                         
#endif
// duration of solenoid firing, in milliseconds
#ifndef FiringDuration7
#define FiringDuration7 ((unsigned long) 40) 
#endif
// state change ignore window for switch (milliseconds)
#ifndef IgnoreWindow7
#define IgnoreWindow7 40                
#endif
#endif // Solenoid7

#ifdef Solenoid8
#define SolenoidMask8 B00100000    // I/O pin D13,  Port B, pin 16 on Nano 
#define SwitchMask8   B00001000    // I/O pin A3,   Port C, pin 22 on Nano
Debounce *switch8;                 // debounced switch; state() = 1 if pressed, 0 if not pressed
int IsFiring8;                     // 1 if solenoid is firing, 0 if not
unsigned long ExpirationTime8;     // time when firing should stop
// debounce delay for switch (milliseconds)
#ifndef Delay8
#define Delay8 4                         
#endif
// duration of solenoid firing, in milliseconds
#ifndef FiringDuration8
#define FiringDuration8 ((unsigned long) 40) 
#endif
// state change ignore window for switch (milliseconds)
#ifndef IgnoreWindow8
#define IgnoreWindow8 40                
#endif
#endif // Solenoid8


void setup() {
#ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Starting...");
#endif  
  
#ifdef Solenoid1
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);   
  pinMode(9, INPUT_PULLUP); 
  switch1 = new Debounce(Delay1, IgnoreWindow1);
#endif

#ifdef Solenoid2
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);   
  pinMode(10, INPUT_PULLUP); 
  switch2 = new Debounce(Delay2, IgnoreWindow2);
#endif

#ifdef Solenoid3
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);   
  pinMode(11, INPUT_PULLUP); 
  switch3 = new Debounce(Delay3, IgnoreWindow3);
#endif

#ifdef Solenoid4
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);   
  pinMode(12, INPUT_PULLUP); 
  switch4 = new Debounce(Delay4, IgnoreWindow4);
#endif

#ifdef Solenoid5
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);   
  pinMode(A0, INPUT_PULLUP); 
  switch5 = new Debounce(Delay5, IgnoreWindow5);
#endif

#ifdef Solenoid6
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);   
  pinMode(A1, INPUT_PULLUP); 
  switch6 = new Debounce(Delay6, IgnoreWindow6);
#endif

#ifdef Solenoid7
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);   
  pinMode(A2, INPUT_PULLUP); 
  switch7 = new Debounce(Delay7, IgnoreWindow7);
#endif

#ifdef Solenoid8
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);   
  pinMode(A3, INPUT_PULLUP); 
  switch8 = new Debounce(Delay8, IgnoreWindow8);
#endif

  // configure the I2C communications channel
  Wire.begin(I2C_MY_ADDRESS); 
  Wire.onRequest(I2C_RequestEvent);

#ifdef DEBUG
  Serial.println("Initialized");
#endif  
}


void readSwitches() {
#ifdef Solenoid1  
  switch1->update((PINB & SwitchMask1) == 0, millis()); 
#endif
#ifdef Solenoid2  
  switch2->update((PINB & SwitchMask2) == 0, millis());   
#endif
#ifdef Solenoid3
  switch3->update((PINB & SwitchMask3) == 0, millis()); 
#endif
#ifdef Solenoid4
  switch4->update((PINB & SwitchMask4) == 0, millis()); 
#endif
#ifdef Solenoid5
  switch5->update((PINC & SwitchMask5) == 0, millis()); 
#endif
#ifdef Solenoid6
  switch6->update((PINC & SwitchMask6) == 0, millis()); 
#endif
#ifdef Solenoid7
  switch7->update((PINC & SwitchMask7) == 0, millis()); 
#endif
#ifdef Solenoid8
  switch8->update((PINC & SwitchMask8) == 0, millis()); 
#endif
}

void loop() {
  unsigned long _millis;

  readSwitches();

#ifdef Solenoid1
  _millis = millis();  
  // Solenoids are fired for a specific duration when a switch is first activated.
  if (IsFiring1) {
    if (ExpirationTime1 < _millis) {
      // turn off the solenoid
      PORTD &= ~SolenoidMask1;
      // prevent the solenoid from firing again until the switch is released
      if (switch1->state() == 0) IsFiring1 = 0;
#ifdef DEBUG
      Serial.print(_millis); 
      Serial.print(" Solenoid 1 off: "); 
      Serial.println(Solenoid1);   
#endif       
    }
  } else if (switch1->state() == 1 && !switch1->isIgnoring(_millis)) {
    // turn on the solenoid
    PORTD |= SolenoidMask1;
    ExpirationTime1 = _millis + FiringDuration1;
    IsFiring1 = 1;
#ifdef DEBUG
    Serial.print(_millis); 
    Serial.print(" Solenoid 1 firing: ");  
    Serial.println(Solenoid1); 
#endif     
  }
#endif // Solenoid1

#ifdef Solenoid2
  _millis = millis();
  // Solenoids are fired for a specific duration when a switch is first activated.
  if (IsFiring2) {
    if (ExpirationTime2 < _millis) {
      // turn off the solenoid
      PORTD &= ~SolenoidMask2;
      // prevent the solenoid from firing again until the switch is released
      if (switch2->state() == 0) IsFiring2 = 0;
#ifdef DEBUG
      Serial.print(_millis); 
      Serial.print(" Solenoid 2 off: ");   
      Serial.println(Solenoid2); 
#endif       
    }
  } else if (switch2->state() == 1 && !switch2->isIgnoring(_millis)) {
    // turn on the solenoid
    PORTD |= SolenoidMask2;
    ExpirationTime2 = _millis + FiringDuration2;
    IsFiring2 = 1;
#ifdef DEBUG
    Serial.print(_millis); 
    Serial.print(" Solenoid 2 firing: ");  
    Serial.println(Solenoid2); 
#endif     
  }
#endif // Solenoid2

#ifdef Solenoid3
  _millis = millis();
  // Solenoids are fired for a specific duration when a switch is first activated.
  if (IsFiring3) {
    if (ExpirationTime3 < _millis) {
      // turn off the solenoid
      PORTD &= ~SolenoidMask3;
      // prevent the solenoid from firing again until the switch is released
      if (switch3->state() == 0) IsFiring3 = 0;
#ifdef DEBUG
      Serial.print(_millis); 
      Serial.print(" Solenoid 3 off: ");   
      Serial.println(Solenoid3);  
#endif       
    }
  } else if (switch3->state() == 1 && !switch3->isIgnoring(_millis)) {
    // turn on the solenoid
    PORTD |= SolenoidMask3;
    ExpirationTime3 = _millis + FiringDuration3;
    IsFiring3 = 1;
#ifdef DEBUG
    Serial.print(_millis); 
    Serial.print(" Solenoid 3 firing: "); 
    Serial.println(Solenoid3);  
#endif     
  }
#endif // Solenoid3

#ifdef Solenoid4
  _millis = millis();
  // Solenoids are fired for a specific duration when a switch is first activated.
  if (IsFiring4) {
    if (ExpirationTime4 < _millis) {
      // turn off the solenoid
      PORTD &= ~SolenoidMask4;
      // prevent the solenoid from firing again until the switch is released
      if (switch4->state() == 0) IsFiring4 = 0;
#ifdef DEBUG
      Serial.print(_millis); 
      Serial.print(" Solenoid 4 off: ");   
      Serial.println(Solenoid4);
#endif          
    }
  } else if (switch4->state() == 1 && !switch4->isIgnoring(_millis)) {
    // turn on the solenoid
    PORTD |= SolenoidMask4;
    ExpirationTime4 = _millis + FiringDuration4;
    IsFiring4 = 1;
#ifdef DEBUG
    Serial.print(_millis); 
    Serial.print(" Solenoid 4 firing: ");    
    Serial.println(Solenoid4);    
#endif     
  }
#endif // Solenoid4       

#ifdef Solenoid5
  _millis = millis();
  // Solenoids are fired for a specific duration when a switch is first activated.
  if (IsFiring5) {
    if (ExpirationTime5 < _millis) {
      // turn off the solenoid
      PORTD &= ~SolenoidMask5;
      // prevent the solenoid from firing again until the switch is released
      if (switch5->state() == 0) IsFiring5 = 0;
#ifdef DEBUG
      Serial.print(_millis); 
      Serial.print(" Solenoid 5 off: ");    
      Serial.println(Solenoid5);      
#endif          
    }
  } else if (switch5->state() == 1 && !switch5->isIgnoring(_millis)) {
    // turn on the solenoid
    PORTD |= SolenoidMask5;
    ExpirationTime5 = _millis + FiringDuration5;
    IsFiring5 = 1;
#ifdef DEBUG
    Serial.print(_millis); 
    Serial.print(" Solenoid 5 firing: "); 
    Serial.println(Solenoid5); 
#endif     
  }
#endif // Solenoid5    

#ifdef Solenoid6
  _millis = millis();
  // Solenoids are fired for a specific duration when a switch is first activated.
  if (IsFiring6) {
    if (ExpirationTime6 < _millis) {
      // turn off the solenoid
      PORTD &= ~SolenoidMask6;
      // prevent the solenoid from firing again until the switch is released
      if (switch6->state() == 0) IsFiring6 = 0;
#ifdef DEBUG
      Serial.print(_millis); 
      Serial.print(" Solenoid 6 off: ");  
      Serial.println(Solenoid6);   
#endif          
    }
  } else if (switch6->state() == 1 && !switch6->isIgnoring(_millis)) {
    // turn on the solenoid
    PORTD |= SolenoidMask6;
    ExpirationTime6 = _millis + FiringDuration6;
    IsFiring6 = 1;
#ifdef DEBUG
    Serial.print(_millis); 
    Serial.print(" Solenoid 6 firing: "); 
    Serial.println(Solenoid6);    
#endif     
  }
#endif // Solenoid6 

#ifdef Solenoid7
  _millis = millis();
  // Solenoids are fired for a specific duration when a switch is first activated.
  if (IsFiring7) {
    if (ExpirationTime7 < _millis) {
      // turn off the solenoid
      PORTB &= ~SolenoidMask7;
      // prevent the solenoid from firing again until the switch is released
      if (switch7->state() == 0) IsFiring7 = 0;
#ifdef DEBUG
      Serial.print(_millis); 
      Serial.print(" Solenoid 7 off: ");   
      Serial.println(Solenoid7); 
#endif          
    }
  } else if (switch7->state() == 1 && !switch7->isIgnoring(_millis)) {
    // turn on the solenoid
    PORTB |= SolenoidMask7;
    ExpirationTime7 = _millis + FiringDuration7;
    IsFiring7 = 1;
#ifdef DEBUG
    Serial.print(_millis); 
    Serial.print(" Solenoid 7 firing: ");   
    Serial.println(Solenoid7); 
#endif     
  }
#endif // Solenoid7

#ifdef Solenoid8
  _millis = millis();
  // Solenoids are fired for a specific duration when a switch is first activated.
  if (IsFiring8) {
    if (ExpirationTime8 < _millis) {
      // turn off the solenoid
      PORTB &= ~SolenoidMask8;
      // prevent the solenoid from firing again until the switch is released
      if (switch8->state() == 0) IsFiring8 = 0;
#ifdef DEBUG
      Serial.print(_millis); 
      Serial.print(" Solenoid 8 off: ");   
      Serial.println(Solenoid8); 
#endif          
    }
  } else if (switch8->state() == 1 && !switch8->isIgnoring(_millis)) {
    // turn on the solenoid
    PORTB |= SolenoidMask8;
    ExpirationTime8 = _millis + FiringDuration8;
    IsFiring8 = 1;
#ifdef DEBUG
    Serial.print(_millis); 
    Serial.print(" Solenoid 8 firing: ");  
    Serial.println(Solenoid8); 
#endif     
  }
#endif // Solenoid8

#ifdef DEBUG
  writeSwitchesToSerial(); 
#endif
}



void I2C_RequestEvent(){
  // The I2C master (the scoring computer) sent a request for the
  // current switch settings.  Pack the switch settings into one
  // byte of data and write it onto the I2C wire.

  byte data = 0;
  
  // bitwise OR together the switch values that have not previously been
  // sent to the scoring computer
#ifdef Solenoid1  
  if (switch1->state() && !switch1->serviced) {
    data |= 1;
    switch1->serviced = true;
  }
#endif
#ifdef Solenoid2  
  if (switch2->state() && !switch2->serviced) {
    data |= 2;
    switch2->serviced = true;
  }
#endif  
#ifdef Solenoid3  
  if (switch3->state() && !switch3->serviced) {
    data |= 4;
    switch3->serviced = true;
  }
#endif
#ifdef Solenoid4  
  if (switch4->state() && !switch4->serviced) {
    data |= 8;
    switch4->serviced = true;
  }
#endif
#ifdef Solenoid5  
  if (switch5->state() && !switch5->serviced) {
    data |= 16;
    switch5->serviced = true;
  }
#endif
#ifdef Solenoid6  
  if (switch6->state() && !switch6->serviced) {
    data |= 32;
    switch6->serviced = true;
  }
#endif
#ifdef Solenoid7  
  if (switch7->state() && !switch7->serviced) {
    data |= 64;
    switch7->serviced = true;
  }
#endif
#ifdef Solenoid8  
  if (switch8->state() && !switch8->serviced) {
    data |= 128;
    switch8->serviced = true;
  }
#endif

  // send the data to the scoring computer
  Wire.write(&data, 1);
}




void writeSwitchesToSerial() {
  static String previous = "";
  String s = "";

#ifdef Solenoid1    
  if (switch1->state()) s = s + " " + Solenoid1;  
#endif
#ifdef Solenoid2    
  if (switch2->state()) s = s + " " + Solenoid2;  
#endif  
#ifdef Solenoid3    
  if (switch3->state()) s = s + " " + Solenoid3;  
#endif
#ifdef Solenoid4    
  if (switch4->state()) s = s + " " + Solenoid4;  
#endif
#ifdef Solenoid5  
  if (switch5->state()) s = s + " " + Solenoid5;  
#endif
#ifdef Solenoid6    
  if (switch6->state()) s = s + " " + Solenoid6;  
#endif
#ifdef Solenoid7    
  if (switch7->state()) s = s + " " + Solenoid7;  
#endif
#ifdef Solenoid8    
  if (switch8->state()) s = s + " " + Solenoid8;  
#endif

  if (previous != s) {
#ifdef DEBUG    
    Serial.println(s);
#endif    
  }
  previous = s;
}
