#include "funcs.h"

#define NUM_LEDS 26        
#define DATA_PIN 2       
#define BRIGHTNESS 50     

CRGB leds[NUM_LEDS];
uint8_t startIndex = 0;

String currentAlerts = "";
uint32_t lastRequestTime = 0;
const uint32_t REQUEST_INTERVAL = 30000;

void setup() 
{
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

    // Prevent LED current from exceeding 1A
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);

    FastLED.setBrightness(BRIGHTNESS);

    // Connecting to WI-FI
    Serial.begin(115200);

    delay(2000);

    // Wait for opening Serial Monitor
    uint32_t startTime = millis();
    while (!Serial && (millis() - startTime < 3000))
    {
        delay(10);
    }

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.println("Connecting");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
}

void loop() 
{
    // // Send the request to the server once a 30 seconds
    // if (millis() - lastRequestTime >= REQUEST_INTERVAL || lastRequestTime == 0)
    // {
    //     currentAlerts = RetrieveAlertInfo(); 
    //     lastRequestTime = millis();
    // }

    // TurnOnLEDs(currentAlerts, leds, NUM_LEDS);

    // delay(20);

    fill_solid(leds, NUM_LEDS, CRGB::Red);
    FastLED.show();
    delay(1000);

    fill_solid(leds, NUM_LEDS, CRGB::Green);
    FastLED.show();
    delay(1000);
}