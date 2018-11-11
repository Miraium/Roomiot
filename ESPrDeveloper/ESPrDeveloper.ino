#include <Ticker.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include "MyConst.h"

//===================================================
// BME280
//===================================================
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

//===================================================
// ESP8266 Wifi
//===================================================
WiFiClient client;
#define SSID MY_SSID
#define PASS MY_PASS

unsigned long delayTime;
#define DELAY_TIME 15000

void setup()
{
  // シリアル通信の開始
  Serial.begin(9600);
  
  // I2C通信の開始
  Serial.println("Start I2C");
  Wire.begin();

  // BME280 - 設定
  Serial.println("Start Setup BME280");
  setupBME280();

  // Wifi - 設定
  Serial.println("Start Setup WiFi");
  setupWifi();

  delayTime = DELAY_TIME;
}

void setupBME280() {
  bool status;
    
  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  status = bme.begin();  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}

void setupWifi() {
  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(SSID);

  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() { 
//    printValues();
    printValuesCompact();
    delay(delayTime);
}


void printValues() {
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");

    Serial.print("Pressure = ");
    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");
    Serial.println();
}

void printValuesCompact() {
    Serial.print(bme.readTemperature());
    Serial.print(", ");

    Serial.print(bme.readPressure() / 100.0F);
    Serial.print(", ");

    Serial.print(bme.readHumidity());
    Serial.println();
}
