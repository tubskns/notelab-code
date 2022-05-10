#include "WifiClient.h"
#include <ESP8266WiFi.h>

WifiClient::WifiClient(String ssid, String pass)
{
    _ssid = ssid;
    _pass = pass;
}

void WifiClient::connect()
{
    Serial.println("Connecting to " + _ssid);
    WiFi.begin(_ssid, _pass);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    Serial.println(" connected to WiFi: " + WiFi.localIP().toString());
}
