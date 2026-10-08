#include "funcs.h"

String RetrieveAlertInfo()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Error: WiFi not connected");
        return ""; 
    }

    // Making a request to the air alert server
    WiFiClientSecure client;
    client.setInsecure();
    client.setHandshakeTimeout(15000);

    HTTPClient http;
    http.setTimeout(15000);
    http.begin(client, String(URL_ADDRESS));
    http.addHeader("Authorization", "Bearer " + String(API_TOKEN));
    http.addHeader("User-Agent", "ESP32-AirAlert-Map/1.0");

    // Receiving a string from the server
    int httpResponseCode = http.GET();
    String resultString = "";

    if (httpResponseCode == HTTP_CODE_OK)
    {
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, http.getStream());

        if (!error)
        {
            resultString = doc.as<String>();

            Serial.print("Received alert string: ");
            Serial.println(resultString);
        }
        else
        {
            Serial.print("deserializeJson() failed: ");
            Serial.println(error.c_str());
        }
    }
    else
    {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        String errorPayload = http.getString();
        Serial.println("Server response: " + errorPayload);
    }

    http.end();
    client.stop();
    return resultString;
}

void TurnOnLEDs(const String &alertString, CRGB leds[], int size)
{
    // An empty string indicates an error
    if(alertString.isEmpty())
    {
        // Turn on the pulsing purple light on all LEDs
        uint8_t bright = beatsin8(15, 10, 50); 
        fill_solid(leds, size, CHSV(192, 255, bright));
        FastLED.show();

        return;
    }

    // Turn on the LEDs depending on received information about alerts
    // 'A' - Air raid alert is active throughout the region, turn on the red light
    // 'P' - Partial alert in certain districts or communities, turn on the yellow light
    // 'N' - No information available regarding an air raid alert, turn on the green light

    int limit = min(size, (int)alertString.length());

    for (int i = 0; i < limit; ++i)
    {
        switch (alertString[i])
        {
            case 'A':
                leds[i] = CRGB::Red;
                break;
            case 'P':
                leds[i] = CRGB::Yellow;
                break;
            case 'N':
                leds[i] = CRGB::Green;
                break;
            default:
                leds[i] = CRGB::Black;
                break;
        }
    }

    FastLED.show();
}