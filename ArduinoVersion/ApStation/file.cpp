#include "file.h"

WiFiAll wifiContent;

int initFile()
{
  if (!LittleFS.begin()) 
  {
    Serial.println("An Error has occurred while mounting LittleFS");
    return -1;
  }
  else
  {
    Serial.println("mounting LittleFS success!");
    return 1;
  }
}

void readFile(const char * path, String &output) 
{
  File file = LittleFS.open(path,"r");
  if (!file) {
    Serial.println("- failed to open file for reading");
    return;
  }
  output = ""; // 清空output字符串
  while (file.available()) {
    char c = file.read();
    output += c; // 将读取的字符添加到output字符串
  }
  file.close();
}


void writeFile(const char * path, const char * message) 
{
  File file = LittleFS.open(path, "w+");
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("- file was written");
  } else {
    Serial.println("- failed to write to file");
  }
  file.close();
}

void updateWifiContent()
{
  File file = LittleFS.open("/wifi.txt", "r");
  if (!file) {
    Serial.println("Failed to open file for getWifiNumber ");
    return;
  }
  file.read((uint8_t *)&wifiContent,sizeof(wifiContent));
}

int getWifiNumber()
{
  File file = LittleFS.open("/wifi.txt", "r");
  if (!file) {
    Serial.println("Failed to open file for getWifiNumber ");
    return -1;
  }
  file.read((uint8_t *)&wifiContent,sizeof(wifiContent));
  return wifiContent.wifiNumber;
}

void getWifiInfo(char * outputWifiInfo)
{
  File file = LittleFS.open("/wifi.txt", "r");
  if (!file) {
    Serial.println("Failed to open file for getWifiNumber ");
    return;
  }
  file.read((uint8_t *)&wifiContent,sizeof(wifiContent));
  
  char tempBuffer[300];
  for(int i=0;i<getWifiNumber();i++)
  {
    strcat(tempBuffer, "\nwifiName: ");
    strcat(tempBuffer, wifiContent.wifiArray[i].ssid);

    strcat(tempBuffer, "\nwifiPassword: ");
    strcat(tempBuffer, wifiContent.wifiArray[i].password);
  }
  strcpy(outputWifiInfo,tempBuffer);
  // Serial.println(tempBuffer);

}

void setWifiContent()
{
  File file = LittleFS.open("/wifi.txt", "w");
  if (!file) {
    Serial.println("Failed to open file for setWifiContent");
    return;
  }
  file.write((const uint8_t *)&wifiContent, sizeof(wifiContent));
  file.close();
  Serial.println("setWifiContent success");
}

int setaWifi(char * ssid,char * password)
{
  if(wifiContent.wifiNumber >= WIFI_MAX_NUMBER)
  {
    return -1;
  }

  strcpy(wifiContent.wifiArray[wifiContent.wifiNumber].ssid, ssid);
  strcpy(wifiContent.wifiArray[wifiContent.wifiNumber].password, password);

  wifiContent.wifiNumber++;
  setWifiContent();

  return 1;
}

void deleteWifi(int index) {
  if (index < 0 || index >= wifiContent.wifiNumber) {
    Serial.println("Invalid WiFi index!");
    return;
  }

  // 删除指定索引的 WiFi 信息，后面的 WiFi 信息向前移动
  for (int i = index; i < wifiContent.wifiNumber - 1; i++) {
    wifiContent.wifiArray[i] = wifiContent.wifiArray[i + 1];
  }

  // 清空最后一个 WiFi 信息
  memset(&wifiContent.wifiArray[wifiContent.wifiNumber - 1], 0, sizeof(WiFiInfo));

  // 更新 WiFi 数量
  wifiContent.wifiNumber--;

  // 更新文件系统
  setWifiContent();

  Serial.println("WiFi info deleted successfully!");
}

String generateWiFiInfoHTML() {
  String html = "";
  for (int i = 0; i < wifiContent.wifiNumber; i++) {
    html += "<p>WiFi Name: {{ssid" + String(i) + "}} <br> Password  : {{password" + String(i) + "}} ";
    html += "<form action='/deletewifi' method='POST' style='display:inline;'>";
    html += "<input type='hidden' name='index' value='" + String(i) + "'>";
    html += "<input type='submit' value='Delete'>";
    html += "</form></p>";
  }
  return html;
}

String processTemplate(String templateContent) {
  for (int i = 0; i < wifiContent.wifiNumber; i++) {
    templateContent.replace("{{ssid" + String(i) + "}}", wifiContent.wifiArray[i].ssid);
    templateContent.replace("{{password" + String(i) + "}}", wifiContent.wifiArray[i].password);
  }
  return templateContent;
}
