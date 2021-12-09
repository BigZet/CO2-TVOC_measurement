
#include <ArduinoJson.h>
#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
#include "Adafruit_CCS811.h"
#include "secrets.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET 4

DynamicJsonDocument doc(1024);
WiFiClient wifiClient;
MqttClient    mqttClient(wifiClient);
Adafruit_CCS811 ccs;
Adafruit_SSD1306 screen(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char ssid[]        = SECRET_SSID;
const char pass[]        = SECRET_PASS;
const char broker[]      = BROKER;
const char accessToken[] = ACCESS_TOKEN; 
const char deviceID[]    = DEVICE_ID;

int CO2;
int TVOC;
int count = 0;
byte readLED = 13; //For read data blinking

void setup() {
  screenInit();
  pinMode(readLED, OUTPUT);
  Serial.begin(9600);
  //while(!Serial);
  sensorInit();
  networkInit();
  
}

void loop() {
  if (count==10){
    measure();
    count = 0;
  }
  if (count%5==0){
    reConnect();
  }
  count++;
  delay(1000);

}
