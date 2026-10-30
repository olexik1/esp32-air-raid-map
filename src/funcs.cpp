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

void TurnOnLEDs(const String &alertString, Adafruit_NeoPixel &pixels, int size)
{
    pixels.clear();

    // An empty string indicates an error
    // Turn on the pulsing purple light on all LEDs
    if (alertString.isEmpty())
    {
        for (int i = 0; i < size; i++)
        {
            pixels.setPixelColor(i, pixels.Color(128, 0, 128));
        }
        pixels.show();
        return;
    }

    int limit = min((int)size + 1, (int)alertString.length());

    // Turn on the LEDs depending on received information about alerts
    // 'A' - Air raid alert is active throughout the region, turn on the red light
    // 'P' - Partial alert in certain districts or communities, turn on the yellow light
    // 'N' - No information available regarding an air raid alert, turn on the green light
    for (int i = 0; i < limit; ++i)
    {
        int ledIndex = apiToLedMap[i]; 

        switch (alertString[i])
        {
            case 'A':
                pixels.setPixelColor(ledIndex, pixels.Color(255, 0, 0));
                break;
            case 'P':
                pixels.setPixelColor(ledIndex, pixels.Color(255, 255, 0));
                break;
            case 'N':
                pixels.setPixelColor(ledIndex, pixels.Color(0, 255, 0)); 
                break;
            default:
                pixels.setPixelColor(ledIndex, pixels.Color(0, 0, 0)); 
                break;
        }
    }
    pixels.show();
}