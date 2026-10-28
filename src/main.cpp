// ******************************************************************
// Dallas Semiconductor DS18B20 Temperature Sensor Demo Program
// COMP-10184
// Mohawk College
// library for Arduino framework
#include <Arduino.h>
// 1-Wire sensor communication libary
#include <OneWire.h>
// DS18B20 sensor library
#include <DallasTemperature.h>
// Pin that the DS18B20 is connected to
const int oneWireBus = D3;
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);
// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature DS18B20(&oneWire);

DeviceAddress tempSensorAddress;

bool sensorConnected;


void getAddress(DeviceAddress tempSensorAddress) {
   // Printing hexadecimal address.
   // Ref: https://forum.arduino.cc/t/how-to-get-ds18b20-address-es-as-a-text-string/1034110
   for(uint8_t i = 0; i < 8; i++)
   {
   // zero pad the address if necessary
      if (tempSensorAddress[i] < 16) Serial.print("0");
         Serial.print(tempSensorAddress[i], HEX);
   }
   Serial.println();
}
void setup() {
// configure the USB serial monitor
 Serial.begin(15200);
 // Start the DS18B20 sensor
 DS18B20.begin();
 
 if(!DS18B20.getAddress(tempSensorAddress, 0)) {
   sensorConnected = false;
   Serial.println("No DS18B20 temperature sensors are installed!");
 } else {
   sensorConnected = true;
   Serial.print("Found DS18B20 sensor with address ");
   getAddress(tempSensorAddress);
   Serial.println("Temperature Application");
 }

}

void loop() {

   // Check if sensor was connected at initialization.
   if(!sensorConnected) {
      return;
   }

   float fTemp;
   // ask DS18B20 for the current temperature
   DS18B20.requestTemperatures();
   // fetch the temperature. We only have 1 sensor, so the index is 0.
   fTemp = DS18B20.getTempCByIndex(0);

   // Temperature output-handling logic.
   if(fTemp < 10.0f) {

      Serial.println("Current temperature is: " + String(fTemp) + "°C or cold");

   } else if(fTemp >= 10.0f && fTemp < 15.0f) {

      Serial.println("Current temperature is: " + String(fTemp) + "°C or cool");

   } else if(fTemp >= 15.0f && fTemp < 25.0f) {

      Serial.println("Current temperature is: " + String(fTemp) + "°C or perfect");

   } else if(fTemp >= 25.0f && fTemp < 30.0f) {

      Serial.println("Current temperature is: " + String(fTemp) + "°C or warm");

   } else if(fTemp >= 30.0f && fTemp <= 35.0f) {

      Serial.println("Current temperature is: " + String(fTemp) + "°C or hot");

   } else if(fTemp > 35.0f) {

      Serial.println("Current temperature is: " + String(fTemp) + "°C or too hot");

   }

   // wait 5s (5000ms) before doing this again
   delay(5000);

}