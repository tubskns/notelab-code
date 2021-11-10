const int trigPin = D4; // HC-SR04's trigger pin is connected to WeMos GPIO 4 (D4)
const int echoPin = D5; // HC-SR04's echo pin is connected to WeMos GPIO 14 (D5)

long duration; // storing time elapsed for sending and receiving pulse wave 
int dist; //storing distance to an object
unsigned long previousSend = 0; // storing last time HCSR04 was updated

void setup() {
  Serial.begin(115200); // establish serial communication at baud rate 115200
  pinMode(trigPin, OUTPUT); // set the trigger pin as output
  pinMode(echoPin, INPUT); // set the echo pin as input
  Serial.println("HC-SR04 test!");
  Serial.println("Collecting distance data:"); 
}

// function for reading HC-SR04 sensor data
void getDistanceData() { 
  // write a pulse: when trigger pin is set to HIGH, stary transmitting
  digitalWrite(trigPin, LOW); // clear the trigger pin
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH); //set the trigger pin to HIGH for 10 ms
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration=pulseIn(echoPin, HIGH); // read the echo pin 
  dist=duration*0.034/2; // calculate distance in cm 
  String distance = String (dist); // convert int to string
    
  Serial.print("Distance: " + distance + " cm\n");
  delay(300); // add delay
}

void loop() {
  if (millis() - previousSend > 1000) { // update and send sensor data only after 1 s
   getDistanceData();
   previousSend = millis();
  }
}
