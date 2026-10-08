#pragma once

#include "wifi_api_data.h"
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <FastLED.h>
#include "regions.h"
#include <WiFiClientSecure.h>

String RetrieveAlertInfo();
void TurnOnLEDs(const String &alertString, CRGB leds[], int size);