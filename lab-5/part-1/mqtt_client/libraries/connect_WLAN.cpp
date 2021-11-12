#include "connect_WLAN.h"
#include <ESP8266WiFi.h> // wifi module library

void connect_to_wifi(String ssid, String pass)
{
    Serial.println("Connecting to " + ssid);
    WiFi.begin(ssid, pass); // connect to WiFi
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500); // add delay until network connected
    }
    Serial.print("Connected to WiFi, IP address: ");
    Serial.println(WiFi.localIP());
}
