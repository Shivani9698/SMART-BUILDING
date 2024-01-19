// Template ID, Device Name, and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab or Template settings
#define BLYNK_TEMPLATE_ID "TMPL36a_ZUDO6"
#define BLYNK_TEMPLATE_NAME "HOME AUTOMATION"
#define BLYNK_AUTH_TOKEN "eNjIjpM38fJQSqFWpYc-7c08UWN_OJy_"
// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial
#define timeSeconds 10

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials
// Set password to "" for open networks
char ssid[] = "FTTHBSNL";
char pass[] = "29915693";

BlynkTimer timer;
const int led = D2; // Change this to the appropriate GPIO pin for your board
const int motionSensor = D6; // Change this to the appropriate GPIO pin for your board

// Timer: Auxiliary variables
unsigned long now = millis();
unsigned long lastTrigger = 0;
boolean startTimer = false;
boolean motion = false;

// Checks if motion was detected, sets LED HIGH, and starts a timer
void detectsMovement() {
  digitalWrite(led, HIGH);
  startTimer = true;
  lastTrigger = millis();
}

void setup() {
  pinMode(motionSensor, INPUT_PULLUP);
  // Set motionSensor pin as interrupt, assign interrupt function and set RISING mode
  attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);

  // Set LED to LOW
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  
  // Debug console
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();

  now = millis();
  if ((digitalRead(led) == HIGH) && (motion == false)) {
    Serial.println("MOTION DETECTED!!!");
    motion = true;
  }
  // Turn off the LED after the number of seconds defined in the timeSeconds variable
  if (startTimer && (now - lastTrigger > (timeSeconds * 1000))) {
    Serial.println("Motion stopped...");
    digitalWrite(led, LOW);
    startTimer = false;
    motion = false;
  }

  Blynk.virtualWrite(V6, motion);
}
