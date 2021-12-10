#include "wifi_connection.h"

String ssid = "netw1";     // student's network SSID
String pass = "password1"; //student's network password

void setup()
{
  Serial.begin(115200);        // establish serial communication at baud rate 115200 || 9200 (vscode)
  connect_to_wifi(ssid, pass); // connect to the network
}

void loop()
{
}
