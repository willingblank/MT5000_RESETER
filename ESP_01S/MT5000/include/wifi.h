#ifndef WIFI_H
#define WIFI_H
#include <ESP8266WiFi.h>

WiFiClient getWifiClient();
void wifi_Init();
void connectWifi(const char* ssid,const char* password);
#endif  //WIFI_H