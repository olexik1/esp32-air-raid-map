#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 1        
#define DATA_PIN 2       
#define BRIGHTNESS 50     

CRGB leds[NUM_LEDS];

void setup() 
{
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

  // Prevent LED current from exceeding 1A
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);

  FastLED.setBrightness(BRIGHTNESS);
}

void loop() 
{
  leds[0] = CRGB::Red;
  FastLED.show(); 
  delay(1000);
}