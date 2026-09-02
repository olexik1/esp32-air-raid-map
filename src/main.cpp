#include <Arduino.h>
#include <FastLED.h>
#include "regions.h"

#define NUM_LEDS 26        
#define DATA_PIN 2       
#define BRIGHTNESS 50     

CRGB leds[NUM_LEDS];
uint8_t startIndex = 0;

void setup() 
{
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

    // Prevent LED current from exceeding 1A
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);

    FastLED.setBrightness(BRIGHTNESS);
}

void loop() 
{
    startIndex = startIndex + 1; 
    fill_rainbow(leds, NUM_LEDS, startIndex, 255/NUM_LEDS); 
    FastLED.show();
    delay(30); 
}