#include <wifi.h>

WiFiClient wifiClient_entity;
const char* ssid = "willingblank";
const char* password = "13255089190";

void wifi_Init()
{
    WiFi.mode(WIFI_STA);
    connectWifi(ssid, password);
}

WiFiClient getWifiClient()
{
    return wifiClient_entity;
}

void connectWifi(const char* ssid,const char* password)
{
  WiFi.begin(ssid, password);
 
  //等待WiFi连接,成功连接后输出成功信息
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected!");  
  Serial.println(""); 
}

