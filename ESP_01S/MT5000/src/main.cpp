/*==========================================================================
  FileName:  main.cpp
  Author:    willingblank
  Creation Date:  November 30, 2024
  Description:    Main File of MT5000_RESETER, show the main logic
  ==========================================================================*/
  // MQTT Test Website  
  // https://testclient-cloud.mqtt.cool/
  
#include <mqtt.h>
#include <wifi.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);    
  Serial.begin(115200);  
  
  wifi_Init();
  mqtt_Init();
}

void loop() 
{
  mqttServerStart();
}
