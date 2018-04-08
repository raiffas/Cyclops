#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

extern Adafruit_NeoPixel strip;
extern uint16_t numPix;
extern unsigned long lastUpdate;
extern unsigned long Interval;
extern bool dir;
extern uint16_t Index;
extern uint32_t Color1;
extern uint16_t target;

void Update();
void Increment();
void Reverse();

void Scanner(uint32_t color1, uint8_t interval);
void ScannerUpdate();

void RainbowCycle();
void RainbowCycleUpdate();

uint32_t DimColor(uint32_t color);
uint8_t Red(uint32_t color);
uint8_t Green(uint32_t color);
uint8_t Blue(uint32_t color);

void oneON(uint16_t pix, uint32_t c);
void oneOFF(uint16_t pix);

#endif