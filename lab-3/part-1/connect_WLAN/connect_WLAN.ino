#include <ESP8266WiFi.h> // wifi module library 

String ssid = "netw1"; // student's network SSID
String pass = "password1"; //student's network password 

void setup() {
  Serial.begin(115200); // establish serial communication at baud rate 115200
  ConnectoToWiFi(); // connect to the network
}
 
void ConnectoToWiFi() {
  Serial.println("Trying to connect to " + ssid);
  WiFi.begin(ssid,pass); // connect to WiFi
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500); // add delay until network connected 
    Serial.print(".");
  }
  Serial.print("Connected to WiFi, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
}
