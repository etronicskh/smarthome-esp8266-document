#include <FS.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>

char ssid[] = "";
char pass[] = "";
const char* blynk_auth = "";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  WiFiManager wifiManager;

  WiFiManagerParameter custom_blynk_token("Blynk", "Blynk Auth", "", 32);
  wifiManager.addParameter(&custom_blynk_token);

  wifiManager.autoConnect("BLYNK_Config", "password");

  Serial.println("Wifi connecting ...");

  const char* blynk_auth = custom_blynk_token.getValue();
  delay(1000);

  Blynk.begin(blynk_auth, ssid, pass);
  Serial.print("blynk:");
  Serial.println(blynk_auth);
  Serial.println("Yeah, start working.");
}

void loop() {
  Blynk.run();
}
