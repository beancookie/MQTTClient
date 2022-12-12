#include <WIFI.h>
#include <AsyncMqttClient.hpp>

#include "MQTT.h"

const char *MQTTUsername = "***";
const char *MQTTPassword = "***";

const char *MQTTHost = "***";
const int MQTTPort = 1883;

AsyncMqttClient mqttClient;

void initMQTT()
{
  mqttClient.setServer(MQTTHost, MQTTPort);
  mqttClient.setCredentials(MQTTUsername, MQTTPassword);
  Serial.print("Connecting to MQTT.");
  while (!MQTTConnected())
  {
    Serial.print('.');
    delay(1000);
  }
  Serial.println("Connected");
}

void MQTTReconnect()
{
  mqttClient.connect();
}

uint16_t publishMQTT(const char *topic, uint8_t qos, bool retain, const char *payload)
{
  return mqttClient.publish(topic, qos, retain, payload);
}

bool MQTTConnected()
{
  return mqttClient.connected();
}