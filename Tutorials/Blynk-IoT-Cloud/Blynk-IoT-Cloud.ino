
// Fill-in information from your Blynk Template here
//#define BLYNK_TEMPLATE_ID           "TMPLxxxxxx"
//#define BLYNK_DEVICE_NAME           "Device"

#define BLYNK_TEMPLATE_ID "TMPLj7TTwisG"
#define BLYNK_DEVICE_NAME "Esp Smart home"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"

#define RELAY1 5
#define RELAY2 4
#define RELAY3 15
#define RELAY4 12

BLYNK_WRITE(V0){
  int pinValue = param.asInt();
  digitalWrite(RELAY1, pinValue);
}

BLYNK_WRITE(V1){
  int pinValue = param.asInt();
  digitalWrite(RELAY2, pinValue);
}

BLYNK_WRITE(V2){
  int pinValue = param.asInt();
  digitalWrite(RELAY3, pinValue);
}

BLYNK_WRITE(V3){
  int pinValue = param.asInt();
  digitalWrite(RELAY4, pinValue);
}

void setup()
{
  Serial.begin(115200);
  delay(100);

  BlynkEdgent.begin();
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
}

void loop() {
  BlynkEdgent.run();
}
