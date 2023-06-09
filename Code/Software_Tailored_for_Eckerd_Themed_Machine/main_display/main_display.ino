/*
 * Code for Pinball Display Arduino
 * 
 * Modified for Lexi's machine
 * 
 * Mike Hilton, Eckerd College
 * 
 * This program implements the score display, NeoPixel effects,
 * and sound output for the NA125 STEM course pinball machine.
 */

// If DEBUG is defined, debug messages will be printed to the serial monitor.  
#define DEBUG

#include "PixelStrand.h"

// I2C communication info
#include <Wire.h>
#define I2C_MY_ADDRESS 9

// NeoPixel Strand
// One extra pixel is allocated to simplify the pixel rotation effect
#define UseNeoPixels              // undef this if no NeoPixels are used
#ifdef UseNeoPixels
#define numNeoPixels 8            // number of pixels in strand, plus 1
#define pinNeoPixels A0            // I/O pin used to control NeoPixel strand
PixelStrand *neopixels;
#endif

///// MAX7219 8-Digital 7-Segment Display Module
#include "LedControl.h"
// The score display is built of daisy-chained 4-digit 7-segment display units
#define scoreQuadDisplays 2    // the number of displays units
#define scoreDigitsToDisplay (scoreQuadDisplays * 4)  // the number of score digits that can be displayed
#define pinScoreLoad 10    // CS pin of display
#define pinScoreClock 11   // CLK pin of display
#define pinScoreData 12    // DIN pin of display
LedControl scoreDisplay = LedControl(pinScoreData,pinScoreClock,pinScoreLoad,1);

#define UseSound
#ifdef UseSound
////// DF Mini MP3 Player for Sounds
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#define pinMP3_RX 3  
#define pinMP3_TX 2  
SoftwareSerial mp3Serial(pinMP3_TX, pinMP3_RX);
DFRobotDFPlayerMini myDFPlayer;
#endif 
// sound volume should be between 0 and 30
int soundVolume = 30;

////// Global variables associated with display functions
long int score = 0;     // current score
long int lastScore = 0; // previous value of score
unsigned long lastScoreTime = 0;     // time of most recent score change

int soundID = 0;        // ID of sound to play
int lightingID = 0;     // ID of lighting routine to perform

  
void setup() {
  // The MAX72XX is in power-saving mode on startup, we have to do a wakeup call
  scoreDisplay.shutdown(0,false);
  // Set the brightness to a medium values
  scoreDisplay.setIntensity(0,8);
  // clear the display
  scoreDisplay.clearDisplay(0);  

#ifdef UseNeoPixels
  // set up the NeoPixel strip
  pinMode(pinNeoPixels, OUTPUT);
  neopixels = new PixelStrand(numNeoPixels, pinNeoPixels);
  // initialize the strand to rainbow
  neopixels->rainbow(0, 1);  
#endif
  
  // configure the I2C communications channel
  Wire.begin(I2C_MY_ADDRESS); 
  Wire.onReceive(I2C_ReceiveEvent);
  
#ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Initialized");
#endif

#ifdef UseSound
  // Initialize the MP3 player
  mp3Serial.begin(9600);
  if (!myDFPlayer.begin(mp3Serial)) {  // Use mp3Serial to communicate with DF Mini Player
    Serial.println("Unable to begin:");
    Serial.println("1. Please recheck the connection!");
    Serial.println("2. Please insert the SD card!");
    Serial.println("3. Reboot");    
  } else {
    myDFPlayer.volume(soundVolume); 
  }
  myDFPlayer.play(3);  //Play the startup song
#endif
}

void loop() {
  
#ifdef DEBUG
 if (score != lastScore) {
    Serial.print("Score = ");
    Serial.print(score);
    Serial.print(" lastScore = ");
    Serial.println(lastScore);
  }
#endif 
  
  DisplayScore(score);

#ifdef UseNeoPixels
  handleLighting();
#else
  lastScore = score;
#endif  

#ifdef UseSound
  if (soundID) {
#ifdef DEBUG
    Serial.print("Sound ID = ");
    Serial.println(soundID);
#endif    
    // play the sound
    myDFPlayer.play(soundID);
    delay(100);  
    soundID = 0;
  }
#endif



}


void DisplayScore(long int score) {
  // Shows the score on the 7-segment LED displays.
  scoreDisplay.shutdown(0,false);
  
  // extract the digits from score
  for (int i=0; i < scoreDigitsToDisplay; i++) {
    int digit = score % 10;
    score = score / 10;
    scoreDisplay.setDigit(0, i, digit, false);
  }
}


#ifdef UseNeoPixels
void handleLighting() {
  // Finite State Machine for managing NeoPixel strand.
  // Lighting modes:
  //    0   Idle state, entered when score has not changed in the last 60 seconds
  //    1   Play state
  //    2   Target state

  // static variables hold the state of the lighting Finite State Machine
  static unsigned long lastAction = 0;        // time of most recent lighting action
  static int mode = 0;                        // identifies lighting display mode

//#ifdef DEBUG
//  Serial.print("Lighting ID =");
//  Serial.print(lightingID);
//  Serial.print(" mode =");
//  Serial.println(mode);
//#endif

  unsigned long _millis = millis();

  // lighting commands received from the scoring computer have priority over modes
  if (lightingID != 0) {
    if (lightingID == 1) {
      // enter target mode, display solid orange
      mode = 2;
      lastAction = _millis;
      lastScoreTime = _millis;
      neopixels->colorWipe(255, 128, 0, 0);
      
    } else if (lightingID == 2) {
      // enter target mode, alternate strand bewteen green and white
      mode = 2;
      lastAction = _millis;
      lastScoreTime = _millis;      
      neopixels->alternate(0, 255, 0, 255, 255, 255);    
        
    } else if (lightingID == 3) {
      // transition to play mode
      mode = 1;
      lastAction = _millis;     
    }
    
  } else {
    // no lighting command was received
    
    if ((mode == 0) && (score != lastScore)) {
      // transition from idle mode to play mode, set color to white
      lastScore = score;
      lastScoreTime = _millis;
      mode = 1;
      neopixels->colorWipe(255, 255, 255, 0);
#ifdef DEBUG
      Serial.println("mode = 1; idle to play");
#endif      
    } else if ((mode != 0) && (_millis - lastScoreTime > 20e3)) {
      // no score in previous 20 seconds, so enter idle mode
      mode = 0;
      neopixels->rainbow(0, 1);
#ifdef DEBUG      
      Serial.println("mode = 0; enter idle");
#endif           
    } else if ((mode == 0) && (_millis - lastAction > 1000)) {
      // idle mode, rotate colors
      neopixels->rotate(1);
      lastAction = _millis;
#ifdef DEBUG      
      Serial.println("mode = 0; rotate");
#endif      
    } else if ((mode == 1) && (score != lastScore)) {
      // remain in play mode; update lastScore variables
      lastScore = score;
      lastScoreTime = _millis;
      
    } else if ((mode == 2) && (_millis - lastAction > 10e3)) {
      // transition from target mode to play mode
      mode = 1;
      neopixels->colorWipe(255, 255, 255, 0); 
      lastAction = _millis;
#ifdef DEBUG      
      Serial.println("mode = 1; target to play");
#endif      
    }
  }
  
}
#endif


void I2C_ReceiveEvent(int numBytes) {
  // The I2C master (the scoring computer) sends messages that contain:
  //    the current score     (3 bytes, least significant byte first)
  //    sound file ID         (1 byte)
  //    lighting routine ID   (1 byte)
  unsigned char bytes[5];

  // read the data into the bytes array
  int i = 0;
  while(Wire.available() && i < 5) {
    bytes[i++] = Wire.read();
  }

  // convert the first three bytes into the new score
  long int newScore = (long int)bytes[0];
  newScore |= ((long int)bytes[1]) << 8;
  newScore |= ((long int)bytes[2]) << 16;
  score = newScore;

  soundID = bytes[3];
  lightingID = bytes[4];
}


void printPixels() {
  // Print the color values of the neopixels object.

#ifdef UseNeoPixels
    Serial.println();
    for (int i=0; i < numNeoPixels; i++) {
      Serial.print(i);
      Serial.print(": ");
      Serial.print(neopixels->getColor(i, 0));
      Serial.print(", ");
      Serial.print(neopixels->getColor(i, 1));
      Serial.print(", "); 
      Serial.println(neopixels->getColor(i, 2));                 
    }
    Serial.println();
#endif
}
