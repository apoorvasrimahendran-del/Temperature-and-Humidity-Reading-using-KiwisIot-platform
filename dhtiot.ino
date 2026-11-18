#include <ESP8266WiFi.h>
#include <KiwisIoT.h>
#include <DHT.h>

// WiFi credentials
const char* ssid = "Name";
const char* pass = "Password";

// KiwisIoT Topic ID
const char* topic = "Topic ID";

// DHT11 sensor
#define DHTPIN D1
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Create KiwisIoT object
KiwisIoT kiwisiot(ssid, pass, topic);

void setup() {

  Serial.begin(115200);

  Serial.println();
  Serial.println("DHT11 Temperature and Humidity");

  dht.begin();

  kiwisiot.begin();

  Serial.println("KiwisIoT Initialized");
}

void loop() {

  // Maintain KiwisIoT connection
  kiwisiot.run();

  // Read sensor values
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check sensor readings
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read DHT11!");
    delay(3000);
    return;
  }

  // Send temperature to Channel 0
  kiwisiot.send("0", temperature);

  // Send humidity to Channel 1
  kiwisiot.send("1", humidity);

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  delay(3000);
}
