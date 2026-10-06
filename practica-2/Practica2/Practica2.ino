/**
 * Libraries
 **/
#include "UbidotsEsp32Mqtt.h"
#include <DHT.h>
#include <TFT_eSPI.h>
// =====================

/**
 * Constants
 **/
const char *UBIDOTS_TOKEN = "TU_TOKEN_DE_UBIDOTS"; // Reemplazar por el token propio. No subirlo al repositorio.
const char *WIFI_SSID = "UPBWiFi";
const char *WIFI_PASS = "";
const char *DEVICE_LABEL = "esp32";
const char *VARIABLE_LABEL = "Temperatura";
const char *VARIABLE_LABEL2 = "Humedad";
const char *SUBSCRIBE_DEVICE_LABEL = "esp32";
const char *SWITCH1_VARIABLE_LABEL = "switch_1";
const char *SWITCH2_VARIABLE_LABEL = "switch_2";

volatile bool switch1State = false;
volatile bool switch2State = false;
// =============================================================

const int PUBLISH_FREQUENCY = 5000;
unsigned long timer;
uint8_t analogPin = 33;


#define DHTPIN 27
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
TFT_eSPI tft = TFT_eSPI();
// =====================

Ubidots ubidots(UBIDOTS_TOKEN);

/**
 * Auxiliar Functions
 **/

void drawSwitchIndicators() {
  int cx1 = 210, cy1 = 20, r = 12;
  tft.fillCircle(cx1, cy1, r, switch1State ? TFT_PURPLE : TFT_DARKGREY);
  tft.drawCircle(cx1, cy1, r, TFT_WHITE);

  int cx2 = 210, cy2 = 55;
  tft.fillCircle(cx2, cy2, r, switch2State ? TFT_RED : TFT_DARKGREY);
  tft.drawCircle(cx2, cy2, r, TFT_WHITE);
}
// ==========================================================

void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  char payloadStr[length + 1];
  for (unsigned int i = 0; i < length; i++) {
    payloadStr[i] = (char)payload[i];
    Serial.print((char)payload[i]);
  }
  payloadStr[length] = '\0';
  Serial.println();

  float value = atof(payloadStr);

  String topicStr = String(topic);

  if (topicStr.indexOf(SWITCH1_VARIABLE_LABEL) != -1) {
    switch1State = (value == 1);
    drawSwitchIndicators();
  } else if (topicStr.indexOf(SWITCH2_VARIABLE_LABEL) != -1) {
    switch2State = (value == 1);
    drawSwitchIndicators();
  }
  // =======================================================================
}

/**
 * Main Functions
 **/
void setup() {
  Serial.begin(115200);
  dht.begin();
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.drawString("Iniciando...", 10, 20);
  // =====================


  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  ubidots.setCallback(callback);
  ubidots.setup();
  ubidots.reconnect();

  ubidots.subscribeLastValue(SUBSCRIBE_DEVICE_LABEL, SWITCH1_VARIABLE_LABEL);
  ubidots.subscribeLastValue(SUBSCRIBE_DEVICE_LABEL, SWITCH2_VARIABLE_LABEL);
  // ===========================================================

  timer = millis();
}

void loop() {
  if (!ubidots.connected()) {
    ubidots.reconnect();
    ubidots.subscribeLastValue(SUBSCRIBE_DEVICE_LABEL, SWITCH1_VARIABLE_LABEL);
    ubidots.subscribeLastValue(SUBSCRIBE_DEVICE_LABEL, SWITCH2_VARIABLE_LABEL);
    // ================================================================
  }

  if ((millis() - timer) > PUBLISH_FREQUENCY) {
    float value = analogRead(analogPin);
    float temperatura = dht.readTemperature();
    float humedad = dht.readHumidity();

    if (!isnan(temperatura) && !isnan(humedad)) {
      ubidots.add(VARIABLE_LABEL, temperatura);
      ubidots.add(VARIABLE_LABEL2, humedad);

      tft.fillScreen(TFT_BLACK);
      tft.setTextColor(TFT_GREEN, TFT_BLACK);
      tft.setTextSize(2);
      tft.drawString("DHT11", 65, 10);

      tft.setCursor(10, 50);
      tft.print("Temp:");
      tft.setCursor(100, 50);
      tft.print(temperatura);
      tft.print(" C");

      tft.setCursor(10, 90);
      tft.print("Hum:");
      tft.setCursor(100, 90);
      tft.print(humedad);
      tft.print(" %");

      drawSwitchIndicators();
    }
    // =====================

    ubidots.add("ADC", value);

    ubidots.publish(DEVICE_LABEL);
    timer = millis();
  }

  ubidots.loop();
}
