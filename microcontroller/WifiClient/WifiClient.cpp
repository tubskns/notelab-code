#include <WiFiNINA.h>
#include "WifiClient.h"

WifiClient::WifiClient(char *ssid, char *pass)
{
  _ssid = ssid;
  _pass = pass;
}

void WifiClient::connect()
{
  WiFiClient wifiClient;
  Serial.print("Connecting to WPA SSID [" + String(_ssid) + "]...");
  while (WiFi.begin(_ssid, _pass) != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  IPAddress ip = WiFi.localIP();
  Serial.print(" done, IP: ");
  Serial.println(ip);
}
