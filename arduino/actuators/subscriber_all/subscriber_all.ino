#include "MqttClient.h"
#include "WifiClient.h"
#include <ArduinoJson.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

char *ssid_wifi = "netw0";
char *pass_wifi = "password1";

const char *mqtt_broker_ip = "MQTT_BROKER_IP";
const int mqtt_broker_port = 1883;
const char *client_id = "subscriber_sensors";
const int num_subscribe_topics = 3;
String subscribe_topics[num_subscribe_topics] = {"motion_topic", "dist_topic", "temp_topic"};
uint8_t leds[3] = {1, 8, 9}; // green, yellow, red
WifiClient wifi_client(ssid_wifi, pass_wifi);
MqttClient mqtt_client(mqtt_broker_ip, mqtt_broker_port, subscribe_topics, num_subscribe_topics);

DynamicJsonDocument msg_doc(1024);
float prev_temp = 0;
int led2_state = LOW;
long led2_interval = 1000000;
unsigned long prev_millis = 0;
LiquidCrystal_I2C lcd(0x27,16,2);

void setup()
{
  Serial.begin(9600); 
  wifi_client.connect();
  mqtt_client.connect(client_id);
  for (int i = 0; i < (sizeof(leds) / sizeof(leds[0])); i++)
    pinMode(leds[i], OUTPUT);
  lcd.init();
  lcd.backlight();
}

void loop()
{ 
  mqtt_client.check_connection(client_id);
  String msg = mqtt_client.get_msg();
  String topic = mqtt_client.get_topic();
  unsigned long current_millis = millis();
  deserializeJson(msg_doc, msg);
  if (topic == subscribe_topics[0])
  {
    bool motion = msg_doc["motion"];
    if (motion == true){
      digitalWrite(leds[0], HIGH);
      lcd.setCursor(13, 0); 
      lcd.print("ON ");
    }
    else{
      digitalWrite(leds[0], LOW);
      lcd.setCursor(13, 0); 
      lcd.print("OFF");
    }
  }
  else if (topic == subscribe_topics[1])
  {
    if (current_millis - prev_millis >= led2_interval)
    {
      prev_millis = current_millis;
      if (led2_state == LOW)
        led2_state = HIGH;
      else
        led2_state = LOW;
      digitalWrite(leds[1], led2_state);
    }
    float distance = msg_doc["distance"];
    if (distance <= 3.0)
      led2_interval = 500;
    else if (distance > 3.0 && distance < 15)
      led2_interval = 2000;
    else {
      led2_interval = 1000000;
      digitalWrite(leds[1], LOW);
      distance = 0;
    }
    lcd.setCursor(0, 1); // second row
    lcd.print("Dist. ");
    String distance_str = String(distance, 1);
    lcd.print(distance_str);
    lcd.print(" cm");
  }
  else if (topic == subscribe_topics[2])
  {
    float temperature = msg_doc["temperature"];
    if (temperature != prev_temp)
    {
      digitalWrite(leds[2], HIGH);
      prev_temp = temperature;
    }
    else
      digitalWrite(leds[2], LOW);
    lcd.setCursor(0, 0); // first row
    lcd.print("Temp. ");
    String temperature_str = String(temperature, 1);
    lcd.print(temperature_str);
    lcd.print((char) 223); // celsius char
  }
  else
  { // ignore
  }
  mqtt_client.reset_msg();
}
