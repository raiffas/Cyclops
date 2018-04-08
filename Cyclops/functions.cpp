#include "functions.h"

void Update(){
  if((millis() - lastUpdate) > Interval) { // time to update
    lastUpdate = millis();
    ScannerUpdate();
  }
}

// Increment the Index and reset at the end
void Increment(){
  if (dir) {
    Index++;
    if (Index >= numPix){ Reverse(); }
  }
  else{ // dir = (REVERSE)
    --Index;
    if (Index <= 0) { Reverse(); }
  }
}

// Reverse pattern strip_direction
void Reverse() {
  if (dir) { 
    dir = false;
    Index = numPix-1; }
  else{ 
    dir = true;
    Index = 0; }
}

// Initialize for a SCANNNER
void Scanner(uint32_t color1, uint8_t interval) {
  Interval = interval;
  Color1 = color1;
  Index = 0;
  dir = true;
}

// Update the Scanner Pattern
void ScannerUpdate(){ 
  for (int i = 0; i < numPix; i++){
    if (i == Index) { // first half of the scan
      oneON(i, Color1);
    }
    else { // fade to black
      strip.setPixelColor(i, DimColor(strip.getPixelColor(i)));
      oneON(target,strip.Color(0, 0, 0, 255));
    }
  }
  strip.show();
  Increment();
}

// Initialize for a RainbowCycle
void RainbowCycle();

// Update the RainbowCycle Pattern
void RainbowCycleUpdate();


// Return color, dimmed by 75% (used by scanner)
uint32_t DimColor(uint32_t color) {
  uint32_t dimColor = strip.Color(Red(color) >> 1, Green(color) >> 1, Blue(color) >> 1);
  return dimColor;
}
// Returns the Red component of a 32-bit color
  uint8_t Red(uint32_t color) { return (color >> 16) & 0xFF; }
// Returns the Green component of a 32-bit color
  uint8_t Green(uint32_t color) { return (color >> 8) & 0xFF; }
// Returns the Blue component of a 32-bit color
  uint8_t Blue(uint32_t color) { return color & 0xFF; }

void oneON(uint16_t pix, uint32_t c) {
  strip.setPixelColor(pix,c);
  strip.show();
}

void oneOFF(uint16_t pix){
  strip.setPixelColor(pix, strip.Color(0,0,0));
  strip.show();
}