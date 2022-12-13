#include <WIFI.h>
#include <AsyncMqttClient.hpp>

#include "MQTT.h"

const char *MQTTUsername = "admin";
const char *MQTTPassword = "public";

const char *MQTTHost = "175.27.192.58";
const int MQTTPort = 1883;

AsyncMqttClient mqttClient;

void initMQTT()
{
  mqttClient.setServer(MQTTHost, MQTTPort);
  mqttClient.setCredentials(MQTTUsername, MQTTPassword);
  Serial.print("Connecting to MQTT.");
  mqttClient.connect();
  while (!MQTTConnected())
  {
    Serial.print('.');
    delay(1000);
    mqttClient.connect();
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