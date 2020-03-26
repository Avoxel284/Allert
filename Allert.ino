/* Allert - Written by FlashDrive284
 * 
 * Instructions of use:
 *  Connect to Allert (Scan project QR Code)
 *  
 * TODO: APIs!
 * An application (most likely HTML with JS will fetch data from Blynk API and return into a rendered HTML page. (Possibly using Firebase :) ))
 */

 //https://www.sensitivechoice.com/wp-content/uploads/2015/04/20140624_Graph-1024x640.jpg is used for the data ranges (level#Max/Min arrays)

#include <Blynk.h>                //Blynk - Blynk library for monitoring app and API
#include <avr/pgmspace.h>
#include <Wire.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>
#include "DHT.h"                  //DHT - Humidity and Temperature sensor library

#define BLYNK_PRINT Serial
#define DHTTYPE DHT11
#define DHTPIN 2


//Attachments
DHT dht(DHTPIN, DHTTYPE);
WidgetTerminal terminal(V1);
//WidgetLED led

//Variables 
int sensor1Pin = 0; //Oxygen sensor (Skipping this sensor!)
int sensor2Pin = 2; //Temperature sensor [DIGITAL]
int sensor3Pin = 2; //Humidity sensor    [DIGITAL]
int sensor4Pin = 0;
int sensor5Pin = 0;
String deviceName = "{DEVICE_NAME}";
int data = 0;
int dangerLevel = 0; //0:Good, 1:Uncomforting, 2:Dangerous

int level0Max[] = {0,25,60}; // <Sensor1,Sensor2,Sensor3, so on...>
int level0Min[] = {0,15,30}; // <Sensor1,Sensor2,Sensor3, so on...>
int level1Max[] = {0,30,70}; // <Sensor1,Sensor2,Sensor3, so on...>
int level1Min[] = {0,25,60}; // <Sensor1,Sensor2,Sensor3, so on...>
int level2Max[] = {0,100,100}; // <Sensor1,Sensor2,Sensor3, so on...>
int level2Min[] = {0,30,70}; // <Sensor1,Sensor2,Sensor3, so on...>

char blynkAuth[] = "udlcqV_hyfHNgpbgFTZS3-yvt-FAm3mB";
char ssid[] = "DeltaServer";
char pass[] = "726630094E";


void setup() {
  digitalWrite(13,HIGH);
  Serial.begin(9600); //Serial for debug purposes TODO: Error in Serial...
  pinMode(12,OUTPUT);
  Serial.println("Welcome to Allert!");
  delay(15);
  Blynk.begin(blynkAuth,ssid,pass);
  error(false);
  Blynk.notify("Welcome to Allert!");
  terminal.clear();
  terminal.println("Welcome to Allert! Booting up...");
  terminal.flush();
  dht.begin();
  Blynk.virtualWrite(4,0);
  delay(1000);
  digitalWrite(13,LOW);
}

void loop() {
  Blynk.run();
  Blynk.virtualWrite(2,readSensor(2));
  Blynk.virtualWrite(3,readSensor(3));
  terminal.flush();
  terminal.print("Sensor 2 (Temp): ");
  terminal.println(readSensor(2));
  terminal.print("Sensor 3 (Humi): ");
  terminal.println(readSensor(3));
  checkDanger();
  delay(15);
}
