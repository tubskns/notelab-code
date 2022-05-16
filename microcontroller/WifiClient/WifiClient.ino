#include "WifiClient.h"

ssid[] ssid = "netw1"; 
ssid[] pass = "password1";
WifiClient wifi_client(ssid, pass);

void setup()
{
  Serial.begin(115200); 
  wifi_client.connect();
}

void loop()
{
}
