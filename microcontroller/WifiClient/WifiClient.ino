#include "WifiClient.h"

char *ssid = "netw0"; 
char *pass = "password1";
WifiClient wifi_client(ssid, pass);

void setup()
{
  Serial.begin(9600); // Serial.begin(115200);
  wifi_client.connect();
}

void loop()
{
}
