#include <Adafruit_NeoPixel.h>
#include "functions.h"
#include <dht11.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20,16,2);
dht11 DHT;
#define DHT11_PIN 4;

#define PIN 6
#define BUTTONPIN 9
#define RBUTTONPIN 10
#define LBUTTONPIN 8

//CHANGE THESE
uint16_t numPix = 15;
unsigned long Interval = 200; // HOW FAST THE LIGHTS CHANGE

////////////////////////////////////
//      NEEDED FOR SCANNER        //
////////////////////////////////////
unsigned long lastUpdate;
bool dir;
uint32_t Color1;
uint16_t Index;
////////////////////////////////////
////////////////////////////////////
//        NEEDED FOR GAME         //
////////////////////////////////////
int buttonState = HIGH;
int rButton = HIGH;
int lButton = HIGH;
int gameState = HIGH;
long score = 0;
int numMissed = 0;
uint16_t target;
uint8_t wait = 200;
//////////////////////////////////// 

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numPix, PIN, NEO_RGBW + NEO_KHZ800);

const uint32_t magenta = strip.Color(0, 200, 255);
const uint32_t green = strip.Color(255, 0, 0);
const uint32_t red = strip.Color(0, 255, 0);
const uint32_t blue = strip.Color(0, 0, 255);
const uint32_t white = strip.Color(0, 0, 0, 255);

void setup() {  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Scanner(blue,Interval);

  pinMode(BUTTONPIN, INPUT);
  digitalWrite(BUTTONPIN, HIGH);//Sets unpushed to HIGH to 1
  
  pinMode(RBUTTONPIN, INPUT);
  digitalWrite(RBUTTONPIN, HIGH);
  
  pinMode(LBUTTONPIN, INPUT);
  digitalWrite(LBUTTONPIN, HIGH);

  lcd.begin();
  lcd.backlight();

  printOnLCD("Ready?");
  //waitingToPlay(); NOT READY TO BE USED
}

void loop() {
  if(gameState == HIGH){
    gameState = digitalRead(BUTTONPIN);
    //waitingToPlay(wait); // NOT READY TO BE USED
  }
  if(gameState == LOW){
    delay(500); // to avoid one button press being counted as multiple
    printOnLCD("GO!");
    
    target = random(numPix);
    oneON(target, white);
    buttonState = HIGH;
    
    while(buttonState == HIGH){
      Update();
      buttonState = digitalRead(BUTTONPIN);
    }
    if(Index == target){
       oneON(Index,red);
       score = score + 100;
       printOnLCD("Nice hit!");
       delay(2000);
       oneOFF(Index);
    }
    else{
      numMissed = numMissed + 1;
      printOnLCD("You missed.");
      delay(700);
      if(numMissed == 3){
        gameState = HIGH;
        printOnLCD("You missed 3.");
        delay(1000);

        lcd.clear();
        lcd.print("    GAME OVER   ");
        delay(2000);
        lcd.print("  Score: ");
        lcd.print((String)score);
        delay(3000);
        
        printOnLCD("Again? L=NO R=YES");
        while((rButton == HIGH) && (lButton == HIGH)){
          rButton = digitalRead(RBUTTONPIN);
          lButton = digitalRead(LBUTTONPIN);
        }
        if (rButton == LOW){ printOnLCD("Ready?"); }
        else{ //waitingToPlay() }
        
      }
    }
    delay(1000);
  }
 }
}

//void waitingToPlay(uint8_t wait){
//  printOnLCD("Press to Play.");
//  strip.RainbowCycle();
//  while(gameState == HIGH){
//    for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
//      for(i=0; i< strip.numPixels(); i++) {
//        strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
//      }
//    strip.show();
//    delay(wait);
//  }
//    
//  }
//}

void printOnLCD(String message){
  lcd.clear();
  lcd.print(message);
}
