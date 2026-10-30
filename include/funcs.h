#pragma once

#include "wifi_api_data.h"
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "regions.h"
#include <WiFiClientSecure.h>
#include <Adafruit_NeoPixel.h>

String RetrieveAlertInfo();
void TurnOnLEDs(const String &alertString, Adafruit_NeoPixel &pixels, int size);