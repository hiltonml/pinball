#include "PixelStrand.h"

PixelStrand::PixelStrand(int pixelCount, int pinControl){
  numPixels = pixelCount;
  pin = pinControl;
  strand = Adafruit_NeoPixel(numPixels, pin, NEO_GRB + NEO_KHZ800);
  strand.begin();
  
  // initialize the strand to white
  pixelColors = new uint8_t[numPixels * 3];
  setBrightness(225);
  colorWipe(255, 255, 255, 0);

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
