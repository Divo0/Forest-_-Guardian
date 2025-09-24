#include "DHT.h"
#include <Adafruit_Sensor.h>
#include "BluetoothSerial.h" // <-- ADD THIS LIBRARY

// Check if Bluetooth is available on the ESP32
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to enable it
#endif

// Define sensor pins and types
#define DHT_PIN 4
#define DHT_TYPE DHT11
#define MQ2_PIN 34
#define LIGHT_PIN 35 

// Initialize the DHT sensor
DHT dht(DHT_PIN, DHT_TYPE);

// Create a Bluetooth Serial object
BluetoothSerial SerialBT; // <-- CREATE BLUETOOTH OBJECT

void setup() {
  // Start serial communication for USB debugging
  Serial.begin(115200);
  Serial.println("ESP32 Fire Sensor Node starting...");

  // Start the Bluetooth serial port with a unique name
  SerialBT.begin("ESP32_Fire_Sensor"); // <-- START BLUETOOTH SERVICE
  Serial.println("Bluetooth device is ready to pair.");

  // Initialize the DHT sensor
  dht.begin();
  
  // Set the pin modes for the analog sensors
  pinMode(MQ2_PIN, INPUT);
  pinMode(LIGHT_PIN, INPUT);
}

void loop() {
  // Wait a few seconds between measurements
  delay(2000);

  // Read sensor values
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();
  int light = analogRead(LIGHT_PIN);
  int gas = analogRead(MQ2_PIN);

  // Check for DHT read errors
  if (isnan(temp) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    SerialBT.println("{\"error\":\"DHT Read Fail\"}");
    return;
  }
  
  // Map analog gas reading for consistency (optional, but good for display)
  // Your original mapping was 0-100, which is fine for a relative value.
  int light_mapped = map(light, 0, 4095, 0, 1000);
  int gas_mapped = map(gas, 0, 4095, 0, 100);
  
  // Create the JSON string
  String jsonString = "";
  jsonString += "{";
  jsonString += "\"temp\":" + String(temp);
  jsonString += ",\"humidity\":" + String(humidity);
  jsonString += ",\"light\":" + String(light_mapped);
  jsonString += ",\"gas\":" + String(gas_mapped);
  jsonString += "}";
  
  // --- Send data to both outputs ---
  
  // 1. Send to USB Serial for debugging in Arduino IDE
  Serial.print("Sending via USB: ");
  Serial.println(jsonString);

  // 2. Send to Bluetooth for the Web Dashboard
  SerialBT.println(jsonString);
}