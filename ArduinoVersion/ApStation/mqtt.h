#ifndef MQTT_H
#define MQTT_H
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include "wifi.h"
#include <stdio.h>
 
typedef void(*MqttReceiveCallback_FuncPtr)(char* , byte* , unsigned int);
void mqtt_Init();
void mqttServerStart();
void subscribeTopic(const char * subTopic);
void connectMQTTserver(const char* subTopic);
void receiveCallback(char* topic, byte* payload, unsigned int length);
void setMqttServer(const char *mqttServer, int port);
void setMqttReceiveCallback(MqttReceiveCallback_FuncPtr funcPrt);
void connectWifi(const char* ssid,const char* password);
#endif // MQTT_H