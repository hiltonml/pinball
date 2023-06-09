#include "PixelStrand.h"

PixelStrand::PixelStrand(int pixelCount, int pinControl){
  // set instance attributes
  numPixels = pixelCount;
  pixelColors = new uint8_t[numPixels * 3];  
  pin = pinControl;
  
  // initialize the NeoPixel object
  strand = Adafruit_NeoPixel(numPixels, pin, NEO_GRB + NEO_KHZ800);
  strand.begin();
}

void PixelStrand::alternate(uint8_t redA, uint8_t greenA, uint8_t blueA, uint8_t redB, uint8_t greenB, uint8_t blueB) {
  // Alternate the colors of the pixels spatially between two colors.
  // INPUTS:
  //  redA, greenA, blueA    color values of even pixels, 0 to 255
  //  redB, greenB, blueB    color values of odd pixels, 0 to 255  

  for(int p=0; p < numPixels; p++) { 
    if (p % 2 == 0) setColor(p, redA, greenA, blueA); 
    else setColor(p, redB, greenB, blueB);                    
  }
  show();    
}

void PixelStrand::colorWipe(uint8_t red, uint8_t green, uint8_t blue, int wait) {
  // Fill strip pixels one after another with a color. Strip is NOT cleared
  // first; anything there will be covered pixel by pixel. 
  // INPUTS:
  //  red, green, blue    color values, 0 to 255
  //  wait                delay (in milliseconds) between each pixel color change

  for(int p=0; p < numPixels; p++) { 
    setColor(p, red, green, blue);
    show();                          
    delay(wait); 
  }
}


uint8_t PixelStrand::getColor(int pixel, int channel) {
  // Return the color of pixel
  int i = pixel * 3 + channel;
  return pixelColors[i];
}


void PixelStrand::rainbow(uint16_t first_hue, int8_t reps) {
  // Fill the strand with one or more cycles of hues.
  // INPUTS:
  //  first_hue   Hue of first pixel, 0-65535. The hue of each subsequent pixel 
  //              in the strand will be offset so as to complete REPS cycles over the
  //              length of the strand.
  //  reps        Number of cycles of the color wheel over the length of the strand. 
  //              Default is 1. Negative values can be used to reverse the hue order.
  
  for (int i=0; i < numPixels; i++) {
    uint16_t hue = first_hue + (i * reps * 65536) / numPixels;
    uint32_t color = strand.gamma32(strand.ColorHSV(hue, 255, 255));
    setColor(i, color);
  }
  show();
}


void PixelStrand::rotate(int positions) {
  // Rotates the pixel colors around the strand the specified number of positions.

  uint8_t temp_r, temp_g, temp_b;
  int i;
  int im1;  // i minus 1 pixel
  
  for (int p=0; p < positions; p++) {
    // rotate by one position
    i = (numPixels-1)*3;
    temp_r = pixelColors[i++];
    temp_g = pixelColors[i++];
    temp_b = pixelColors[i];
    
    for (int j=numPixels-1; j > 0; j--) {
      i = j * 3;
      im1= (j-1) * 3;
      pixelColors[i++] = pixelColors[im1++];
      pixelColors[i++] = pixelColors[im1++];
      pixelColors[i] = pixelColors[im1];            
    }
    
    pixelColors[0] = temp_r;
    pixelColors[1] = temp_g;
    pixelColors[2] = temp_b;
  }

  show();
}


void PixelStrand::setBrightness(uint8_t  value) {
  // Sets the brightness of the strand.
  // Input:
  //  value       1-255; 1 is dark, 255 is maximum brightness
  
  strand.setBrightness(value);
}

void PixelStrand::setColor(int index, uint8_t red, uint8_t green, uint8_t blue) {
  // Set the color of the specified pixel.
  // INPUTS:
  //  index               index of pixel in strand
  //  red, green, blue    color values, 0 to 255

  int i = index * 3;
  pixelColors[i++] = red;
  pixelColors[i++] = green;  
  pixelColors[i++] = blue;
}


void PixelStrand::setColor(int index, uint32_t color) {
  // Set the color of the specified pixel.
  // INPUTS:
  //  index     index of pixel in strand
  //  color     packed color values
  
  uint8_t r = (uint8_t)(color >> 16), g = (uint8_t)(color >> 8), b = (uint8_t)color;
  setColor(index, r, g, b);
}


void PixelStrand::show() {
  // Update the pixel colors and send them to the hardware.
  
  int i = 0;
  for (uint16_t p=0; p < numPixels; p++) {
    uint8_t r = pixelColors[i++];
    uint8_t g = pixelColors[i++];
    uint8_t b = pixelColors[i++];
    strand.setPixelColor(p, r, g, b);
  }
  strand.show();
}
