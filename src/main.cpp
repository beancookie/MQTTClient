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

void sendGPSMessage()
{
  MsgPack::map_t<String, float> m{{"one", 1.1}, {"two", 2.2}, {"three", 3.3}};

  MsgPack::Packer packer;
  packer.serialize(m);
  Serial.print("Publish GPS: ");
  Serial.println((char *)packer.data());

  publishMQTT("event/gktjk1545/up", 1, true, (char *)packer.data());
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