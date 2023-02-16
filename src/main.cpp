#include <Arduino.h>
#include <MsgPack.h>
#include <AsyncMqttClient.hpp>

#include "sdkconfig.h"
#include "WiFiManager.h"
#include "MQTT.h"

#define DEFAULT_RATE 5         
#define QOS_0 0         
#define QOS_1 1         
#define QOS_2 2         

struct GPS
{
  float lat;
  float lon;
  MSGPACK_DEFINE(lat, lon);
};

int rate;

void onMessageCallback(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
  Serial.printf("onMqttMessage %s \n", payload);
  rate = atoi(payload);
}

void setup()
{
  Serial.begin(115200);

  initWiFi();
  initMQTT();
  subscribe("event/gps/gktjk1545/down", QOS_2);
  onMessage(onMessageCallback);
  rate = DEFAULT_RATE;
}

void sendGPSMessage()
{

  GPS gps = GPS{lat : float(random(3114, 3178) / 100.0), lon : float(random(11822, 11897) / 100.0)};

  MsgPack::Packer packer;
  packer.serialize(gps);
  Serial.printf("Publish GPS: { lat: %f, lon: %f }\n", gps.lat, gps.lon);

  publishMQTT("event/gps/gktjk1545/up", QOS_1, true, (char *)packer.data());
}

void loop()
{
  if (!MQTTConnected())
  {
    MQTTReconnect();
  }
  sendGPSMessage();
  delay(rate * 1000);
}