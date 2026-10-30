#include "funcs.h"

#define PIN 2         
#define NUMPIXELS 26  
#define BRIGHTNESS 15 

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

String currentAlerts = "";
uint32_t lastRequestTime = 0;
const uint32_t REQUEST_INTERVAL = 120000;

void setup()
{
    pixels.begin();
    pixels.setBrightness(BRIGHTNESS);
    pixels.clear();
    pixels.show();

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
    // Send the request to the server
    if (millis() - lastRequestTime >= REQUEST_INTERVAL || lastRequestTime == 0)
    {
        currentAlerts = RetrieveAlertInfo();
        lastRequestTime = millis();
    }

    TurnOnLEDs(currentAlerts, pixels, NUMPIXELS);

    delay(20);

    // // Вмикаємо червоний
    // for (int i = 0; i < NUMPIXELS; i++)
    // {
    //     pixels.setPixelColor(i, pixels.Color(255, 0, 0));
    // }
    // pixels.show();
    // delay(1000);

    // // Вмикаємо зелений
    // for (int i = 0; i < NUMPIXELS; i++)
    // {
    //     pixels.setPixelColor(i, pixels.Color(0, 255, 0));
    // }
    // pixels.show();
    // delay(1000);
}