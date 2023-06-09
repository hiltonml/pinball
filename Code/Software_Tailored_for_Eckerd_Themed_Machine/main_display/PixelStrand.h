#ifndef INCLUDE_PIXELSTRAND
#define INCLUDE_PIXELSTRAND

/*
 * PixelStrand Class
 * Mike Hilton, Eckerd College
 * 
 * Wrapper class for a strand of NeoPixels.
 */

#include <Adafruit_NeoPixel.h> 

class PixelStrand {
  private:
    int numPixels;            // number of NeoPixels in the strand
    int pin;                  // Arduino pin used to control NeoPixels (must be a PWM pin)    
    uint8_t *pixelColors;     // array of color values for each pixel
    Adafruit_NeoPixel strand; // NeoPixel object

  public:
    PixelStrand(int pixelCount, int pinControl);

    void alternate(uint8_t redA, uint8_t greenA, uint8_t blueA, uint8_t redB, uint8_t greenB, uint8_t blueB);
    void colorWipe(uint8_t red, uint8_t green, uint8_t blue, int wait); // fill strand with specified color
    uint8_t getColor(int pixel, int channel);       // gets color channel of specified pixel
    void rainbow(uint16_t first_hue=0, int8_t reps=1);  // rainbow cycle the strand
    void rotate(int positions);                     // rotate the colors by specified number of positions
    void setBrightness(uint8_t  value);             // set brightness of strand 
    void setColor(int index, uint8_t red, uint8_t green, uint8_t blue); // set the color of specified pixel
    void setColor(int index, uint32_t color);       // set the color of specified pixel
    void show();                                    // display the pixels
 };

#endif
