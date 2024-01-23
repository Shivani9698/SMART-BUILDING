// Template ID, Device Name, and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab or Template settings
#define BLYNK_TEMPLATE_ID "TMPL3XUDIMBEO"
#define BLYNK_TEMPLATE_NAME "POT AND LED"
#define BLYNK_AUTH_TOKEN "sfYj2irrsPy_DoBXn3UPrKQ40ZynWsVC"
// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials
// Set password to "" for open networks
char ssid[] = "AirFiber";
char pass[] = "Hnasetty09";

BlynkTimer timer;
int Status = 2;  // Digital pin D6

int sensor = 13;  // Digital pin D7

// Timer: Auxiliary variables

void setup() {
  Serial.begin(115200);

  pinMode(sensor, INPUT);   // declare sensor as input
  pinMode(Status, OUTPUT);  // declare LED as output

  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
  timer.run();
  
  delay(2000);

 long state = digitalRead(sensor);
    if(state == HIGH) {
      digitalWrite (Status, 0);
      Serial.println("Motion detected!");
      delay(1000);
      
    }
    else {
      digitalWrite (Status, 1);
      Serial.println("Motion absent!");
      delay(1000);
      
      }
  

  Blynk.virtualWrite(V6, state);
}
