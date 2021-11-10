const int pirSensor = 13; // PIR's pin is connected to NodeMCU's GPIO 13 (D7)
int calibrationTime=30; //time for sensor to calibrate
int pinState = 0; // store pin status 

void setup() {
  Serial.begin(115200);
  Serial.println("PIR test!");
  pinMode(pirSensor, INPUT); // set sensor pin as input:
  Serial.print("Calibrating sensor ");
  for (int i=0; i<calibrationTime; i++) // give some time to calibrate
    {
       Serial.print(".");
       delay(100);
    }
  Serial.println("Sensor active");
}


void loop() {
  pinState = digitalRead(pirSensor); // read the digital value of output pin 
  delay(1000);
  if (pinState == HIGH) {
   Serial.println("Motion detected!");
  }
  else {
   Serial.println("Motion absent!");
  }
} 
