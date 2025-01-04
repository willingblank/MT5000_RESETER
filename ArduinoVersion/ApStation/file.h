#ifndef FILE_H
#define FILE_H

#include <Arduino.h>
#include <LittleFS.h>

#define WIFI_MAX_NUMBER 10

typedef struct {
    char ssid[32];      // WiFi名称，假设最大长度为31个字符，加上一个结束符'\0'
    char password[12];  // WiFi密码，假设最大长度为63个字符，加上一个结束符'\0'
} WiFiInfo;

typedef struct {
  int wifiNumber;
  WiFiInfo wifiArray[WIFI_MAX_NUMBER];
} WiFiAll;

int initFile();
void readFile(const char * path, String &output);
void writeFile(const char * path, const char * message);
void getWifiInfo(char * outputWifiInfo);
void setWifiContent();
int setaWifi(char * ssid,char * password);
void deleteWifi(int index);
void updateWifiContent();
String generateWiFiInfoHTML();
String processTemplate(String templateContent);

#endif  //FILE_H