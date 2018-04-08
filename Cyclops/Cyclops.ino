#include <Adafruit_NeoPixel.h>

#define PIN 6
uint16_t numPix = 30;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numPix, PIN, NEO_RGBW + NEO_KHZ800);
const uint32_t magenta = strip.Color(0, 200, 255);
const uint32_t green = strip.Color(255, 0, 0);
const uint32_t red = strip.Color(0, 255, 0);
const uint32_t blue = strip.Color(0, 0, 255);

////////////////////////////////////////////////////////////////////////////////////
void Update(void);
void Increment();
void Reverse();

void Scanner(uint32_t color1, uint8_t interval);
void ScannerUpdate();

uint32_t DimColor(uint32_t color);
uint8_t Red(uint32_t color);
uint8_t Green(uint32_t color);
uint8_t Blue(uint32_t color);

void oneON(uint16_t pix, uint32_t c);
void oneOFF(uint16_t pix);

unsigned long Interval;
unsigned long lastUpdate;

uint16_t dir;
uint32_t Color1;
uint16_t TotalSteps;
uint16_t Index;
////////////////////////////////////////////////////////////

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  
  Serial.begin(9600);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Scanner(magenta,100);
}

uint16_t pix=0;

void loop() {
  Update();
}

void Update(){
  if((millis() - lastUpdate) > Interval) { // time to update
    lastUpdate = millis();
    ScannerUpdate();
  }
}

// Increment the Index and reset at the end
void Increment(){
  if (dir == 1) {
    Index++;
    if (Index >= numPix){
      Reverse();
    }
  }
  else{ // dir == -1 (REVERSE)
    --Index;
    if (Index <= 0) {
      Reverse();
    }
  }
}

// Reverse pattern strip_direction
void Reverse() {
  if (dir == 1) {
    dir = -1;
    Index = numPix-1;
  }
  else{
    dir = 1;
    Index = 0;
    //delay(3000);
  }
}

// Initialize for a SCANNNER
void Scanner(uint32_t color1, uint8_t interval) {
  Interval = interval;
  TotalSteps = (numPix - 1) * 2; // twice num of pixels - 2
  Color1 = color1;
  Index = 0;
  dir = 1;
}

// Update the Scanner Pattern
void ScannerUpdate(){ 
  for (int i = 0; i < numPix; i++){
    if (i == Index) { // first half of the scan
      oneON(i, Color1);
    }
    else { // fade to black
      strip.setPixelColor(i, DimColor(strip.getPixelColor(i)));
    }
  }
  strip.show();
  Increment();
}

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
  strip.begin();
  strip.setPixelColor(pix,c);
  strip.show();
}

void oneOFF(uint16_t pix){
  strip.setPixelColor(pix, strip.Color(0,0,0));
  strip.show();
}
