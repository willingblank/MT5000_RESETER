#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WebServer.h>
#include <string.h>
#include "ATcmd.h"
#include "file.h"
#include "mqtt.h"
#include "wifi.h"

ESP8266WiFiMulti wifiMulti;

//创建ESP8266WebServer对象
ESP8266WebServer server(80);
extern String html_Content;
extern WiFiAll wifiContent;

void setup(void) {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);    
  //初始化串口
  Serial.begin(115200);
  Serial.println("");
  Serial.println("MT5000 RESTER TEST CODE");
  if(initFile())
  {
    Serial.println("file system mount success");
  }
  else
  {
    Serial.println("file system mount fail!");
  }
  updateWifiContent();

  Serial.printf("wifiContent.wifiNumber = %d \r\n",wifiContent.wifiNumber);
  for(int i=0;i<wifiContent.wifiNumber;i++)
  {
    wifiMulti.addAP(wifiContent.wifiArray[i].ssid,wifiContent.wifiArray[i].password);
  }

  //初始化网络
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("ESP8266-AP", "123456789");  // 创建 AP
  Serial.println("Access Point Started");
  Serial.print("Access Point IP Address: ");
  Serial.println(WiFi.softAPIP());  // 输出 AP 模式下的 IP 地址

  Serial.println("Connecting ...");         // 通过串口监视器输出信息告知用户NodeMCU正在尝试连接WiFi
  int i = 0;                                 
  while (wifiMulti.run() != WL_CONNECTED) {  // 此处的wifiMulti.run()是重点。通过wifiMulti.run()，NodeMCU将会在当前
    delay(1000);                             // 环境中搜索addAP函数所存储的WiFi。如果搜到多个存储的WiFi那么NodeMCU
    Serial.print('.');                       // 将会连接信号最强的那一个WiFi信号。
  }   
  Serial.println("");
  Serial.print("Connected to ");            // NodeMCU将通过串口监视器输出。
  Serial.println(WiFi.SSID());              // 连接的WiFI名称
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
 
  //初始化WebServer
  server.begin();
  //设置主页处理函数
  server.on("/", homepage);
  server.on("/wifilist", wifiInfoPage);
  server.on("/setwifi", handlePost);
  server.on("/deletewifi", handleDelete);
  //设置404页面
  server.onNotFound(handleNotFound);
  //串口输出服务器准备完成信息
  Serial.println("HTTP server started");

  mqtt_Init();
}
 
void loop(void) {
  //监听客户请求并处理
  server.handleClient();
  atcmd_handle();
  mqttServerStart();
}
 
//自定义返回请求体信息
void handle_args() {
  Serial.print("请求体参数a的值:"); 
  Serial.println(server.arg("wifiname"));
  Serial.print("请求体第2个参数的值:"); 
  Serial.println(server.arg("wifipassword"));

  const char* wifiname = server.arg("wifiname").c_str();
  const char* wifipassword = server.arg("wifipassword").c_str();
  setaWifi((char *)wifiname,(char *)wifipassword);
}
 
// 设置主页请求处理函数
void homepage() {
  String page = html_Content;
  updateWifiContent();
  String wifiInfoHTML = generateWiFiInfoHTML();
  page.replace("{{wifiInfo}}", wifiInfoHTML);
  page = processTemplate(page);

  server.send(200, "text/html", page);
  Serial.println("用户访问了主页");
}

void wifiInfoPage()
{
  char tempBuffer[300];
  getWifiInfo(tempBuffer);
  server.send(200, "text/html", tempBuffer);
}
 
// 设置处理404情况的函数'handleNotFound'
void handleNotFound() {                                       // 当浏览器请求的网络资源无法在服务器找到时，
  server.send(404, "text/plain", "404: Not found");           // NodeMCU将调用此函数。
}

void handlePost()
{
  // handle_args();
  Serial.printf("请求设置Wifi ssid=%s password=%s \r\n",server.arg("wifiname"),server.arg("wifipassword"));

  const char* wifiname = server.arg("wifiname").c_str();
  const char* wifipassword = server.arg("wifipassword").c_str();
  setaWifi((char *)wifiname,(char *)wifipassword);
  server.send(200, "text/html", "Set wifi Parameter Success!!! <meta http-equiv='refresh' content='0.9;url=/'>");
}

void handleDelete()
{
  int wifiIndex = server.arg("index").toInt();
  Serial.printf("请求删除 wifiArray[%d] 的值 \r\n",wifiIndex); 
  deleteWifi(wifiIndex);
  server.send(200, "text/html", "Delet Wifi Parameter Success. <meta http-equiv='refresh' content='0;url=/'>");
}