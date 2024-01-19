// Template ID, Device Name, and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab or Template settings
#define BLYNK_TEMPLATE_ID "TMPL36a_ZUDO6"
#define BLYNK_TEMPLATE_NAME "HOME AUTOMATION"
#define BLYNK_AUTH_TOKEN "eNjIjpM38fJQSqFWpYc-7c08UWN_OJy_"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials
// Set password to "" for open networks
char ssid[] = "FTTHBSNL";
char pass[] = "29915693";

BlynkTimer timer;

#define DHTPIN D2     // Change this to the appropriate GPIO pin for your board
#define DHTTYPE DHT11 // Change this to the appropriate DHT sensor type

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.println("DHTxx test!");
  Serial.begin(115200);
  dht.begin();
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
  timer.run();

  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index
  // Must send in temp in Fahrenheit!
  float hi = dht.computeHeatIndex(f, h);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hi);
  Serial.println(" *F");

  Blynk.virtualWrite(V4, h);
  Blynk.virtualWrite(V5, t);
}

