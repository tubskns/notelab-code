#include "WifiClient.h"

String ssid = "netw1"; 
String pass = "password1";
WifiClient wifi_client(ssid, pass);

void setup()
{
  Serial.begin(115200); 
  wifi_client.connect();
}

void loop()
{
}
