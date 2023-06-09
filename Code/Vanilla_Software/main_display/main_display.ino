/*
 * Code for Pinball Display Arduino
 * Mike Hilton, Eckerd College
 * 
 * This program implements the score display, NeoPixel effects,
 * and sound output for the NA125 STEM course pinball machine.
 */

// If DEBUG is defined, debug messages will be printed to the serial monitor.  
#undef DEBUG

#include "PixelStrand.h"

// I2C communication info
#include <Wire.h>
#define I2C_MY_ADDRESS 9

// NeoPixel Strand
// One extra pixel is allocated to simplify the pixel rotation effect
#define UseNeoPixels              // undef this if no NeoPixels are used
#ifdef UseNeoPixels
#define numNeoPixels 16            // number of pixels in strand, plus 1
#define pinNeoPixels 7            // I/O pin used to control NeoPixel strand
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
////// MP3 Player for Sound Effects
#include <SoftwareSerial.h>
// The serial connections on the inexpensive Catalex MP3 board we are using has
// reversed RX and TX lines
#define pinMP3_RX 5  //should connect to TX of the Serial MP3 Player module
#define pinMP3_TX 6  //connect to RX of the module
SoftwareSerial mp3(pinMP3_RX, pinMP3_TX);
#endif 

////// Global variables associated with display functions
long int score = 0;     // current score
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
#endif

#ifdef UseSound
  // Initialize the MP3 player by sending Select Device command (0x09) with TF option (0x02)
  sendMp3Command(0x09, 0x02);
#endif
  
  // configure the I2C communications channel
  Wire.begin(I2C_MY_ADDRESS); 
  Wire.onReceive(I2C_ReceiveEvent);
  
#ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Initialized");
#endif
}

void loop() {
  DisplayScore(score);

#ifdef UseSound
  if (soundID) {
    // play the sound
    sendMp3Command(0x0D, soundID);
    soundID = 0;
  }
#endif

#ifdef DEBUG
  Serial.print("Score = ");
  Serial.print(score);
  Serial.print("   sound ID = ");
  Serial.print(soundID);
  Serial.print("   lighting ID = ");
  Serial.println(lightingID);
#endif  
}


void DisplayScore(long int score) {
  // Shows the score on the 7-segment LED displays.
  
  // extract the digits from score
  for (int i=0; i < scoreDigitsToDisplay; i++) {
    int digit = score % 10;
    score = score / 10;
    scoreDisplay.setDigit(0, i, digit, false);
  }
}


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


#ifdef UseSound
void sendMp3Command(int8_t command, int16_t dat)
{
  // Send a command to the MP3 player.

  static int8_t Send_buf[8] = {0}; // Buffer for Send commands

  // create the command packet
  Send_buf[0] = 0x7e;   //
  Send_buf[1] = 0xff;   //
  Send_buf[2] = 0x06;   // Len
  Send_buf[3] = command;//
  Send_buf[4] = 0x00;   // 0x00 No feedback, 0x01 feedback
  Send_buf[5] = (int8_t)(dat >> 8);  //data high byte
  Send_buf[6] = (int8_t)(dat);       //data low byte
  Send_buf[7] = 0xef;   //

  // write the command to the player
  for (uint8_t i = 0; i < 8; i++) {
    mp3.write(Send_buf[i]) ;
  }
}
#endif
