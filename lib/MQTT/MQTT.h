#ifndef MQTT_H
#define MQTT_H
void initMQTT();
uint16_t publishMQTT(const char *topic, uint8_t qos, bool retain, const char *payload);
void subscribe(const char* topic, uint8_t qos);
void onMessage(AsyncMqttClientInternals::OnMessageUserCallback callback);
bool MQTTConnected();
void MQTTReconnect();
#endif