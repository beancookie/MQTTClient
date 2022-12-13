#include <Arduino.h>
#include <MsgPack.h>

#include "WiFiManager.h"
#include "MQTT.h"

void setup()
{
  Serial.begin(115200);

  initWiFi();
  initMQTT();
}

struct GPS
{
  float lat;
  float lon;
  MSGPACK_DEFINE(lat, lon);
};

void sendGPSMessage()
{

  GPS gps = GPS{lat : float(random(3114, 3178) / 100.0), lon : float(random(11822, 11897) / 100.0)};

  MsgPack::Packer packer;
  packer.serialize(gps);
  Serial.printf("Publish GPS: { lat: %f, lon: %f }\n", gps.lat, gps.lon);

  publishMQTT("event/gps/gktjk1545/up", 1, true, (char *)packer.data());
}

void loop()
{
  if (!MQTTConnected())
  {
    MQTTReconnect();
  }
  sendGPSMessage();
  delay(3000);
}