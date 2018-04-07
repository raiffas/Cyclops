#include <Adafruit_NeoPixel.h>
//#include <NeoPattern.h>

#define PIN 6
const int numPix = 30;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numPix, PIN, NEO_RGBW + NEO_KHZ800);
//NeoPatterns stick(numPix, PIN, nEO_RGBW + NEO_KHZ800);

const uint32_t magenta = strip.Color(0, 200, 255);
const uint32_t green = strip.Color(255, 0, 0);
const uint32_t red = strip.Color(0, 255, 0);
const uint32_t blue = strip.Color(0, 0, 255);

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  
  strip.begin();
  
  Serial.begin(9600);
  strip.setBrightness(15);
  Serial.println(strip.getBrightness());

//  Stick.Scanner(magenta),500);
  strip.show(); // Initialize all pixels to 'off'
}
uint16_t pix = 0;
void loop() {
  pix = pix+1;
  if(pix>=numPix){
    pix = 0;
  }
  Serial.println("on");
  oneON(pix, magenta);
  delay(200);
  Serial.println("off");
  oneOFF(pix);
  delay(200);

//  strip.Scanner(blue,500);
}

void oneON(uint16_t pix, uint32_t c) {
   strip.setPixelColor(pix,c);
   strip.show();
}

void oneOFF(uint16_t pix){
  strip.setPixelColor(pix, strip.Color(0,0,0));
  strip.show();
}
