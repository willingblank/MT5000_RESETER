#include "ATcmd.h"
#include "file.h"

void atcmd_handle()
{
  if (Serial.available() > 0) {
    String receivedData = Serial.readStringUntil('\n');
    Serial.println(receivedData);
    if(receivedData == "hello")
    {
      Serial.println("hello MT5000 RESTER");
    }
    else if(receivedData == "wifilist")
    {
      // String temp;
      // readFile("/wifi.txt", temp);
      // Serial.println(temp);
      char tempBuffer[300];
      getWifiInfo(tempBuffer);
      Serial.println(tempBuffer);
    }

  }
}