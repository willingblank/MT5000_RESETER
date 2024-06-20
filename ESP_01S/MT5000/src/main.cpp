
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// MQTT Test Website  
// https://testclient-cloud.mqtt.cool/

// 设置wifi接入信息(请根据您的WiFi信息进行修改)
const char* ssid = "willingblank";
const char* password = "13255089190";
const char* mqttServer = "broker.mqtt.cool";
char subTopic[30] = "willingblank_MT5000_RESETER";




WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void subscribeTopic()
{
  // 通过串口监视器输出是否成功订阅主题以及订阅的主题名称
  if(mqttClient.subscribe(subTopic))
  {
    Serial.print("Subscrib Topic = [");
    Serial.print(subTopic);
    Serial.println("] ");
  }
  else
  {
    Serial.print("Subscribe Topic Failed...");
  }  
}

// 连接MQTT服务器并订阅信息
void connectMQTTserver()
{
  // 根据ESP8266的MAC地址生成客户端ID（避免与其它ESP8266的客户端ID重名）
  String clientId = "esp8266-" + WiFi.macAddress();
 
  // Connect to MQTT Server
  if (mqttClient.connect(clientId.c_str())) 
  { 
    Serial.println("MQTT Server Connected.");
    Serial.print("Server Address:  ");
    Serial.println(mqttServer);
    Serial.print("ClientId:  ");
    Serial.println(clientId);
    subscribeTopic();
  } 
  else 
  {
    Serial.print("MQTT Server Connect Failed. Client State:");
    Serial.println(mqttClient.state());
    delay(5000);
  }   
}
 
// 收到信息后的回调函数
void receiveCallback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print(length);
  Serial.print(" (Byte) Message Received From [");
  Serial.print(topic);
  Serial.print("]: ");
  for (unsigned int i = 0; i < length; i++) 
  {
    Serial.print((char)payload[i]);
  }
  Serial.println("");
  // Serial.print("Message Length(Bytes) = ");
  // Serial.println(length);
 
  if ((char)payload[0] == '1')  // 如果收到的信息以“1”为开始
  {     
    digitalWrite(LED_BUILTIN, LOW);  // 则点亮LED。
    Serial.println("<LED ON>");
  } 
  else 
  {                           
    digitalWrite(LED_BUILTIN, HIGH); // 否则熄灭LED。
    Serial.println("<LED OFF>");
  }
}

// ESP8266连接wifi
void connectWifi()
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

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);    
  Serial.begin(115200);               
  
  //设置ESP8266工作模式为无线终端模式
  WiFi.mode(WIFI_STA);
  
  // 连接WiFi
  connectWifi();
  
  // 设置MQTT服务器和端口号
  mqttClient.setServer(mqttServer, 1883);
  // 设置MQTT订阅回调函数
  mqttClient.setCallback(receiveCallback);
 
  // 连接MQTT服务器
  connectMQTTserver();
}
 
void loop() 
{
  if (mqttClient.connected())   // Device connected to server successfully
  { 
    mqttClient.loop();          // MQTT Loop 
  } 
  else                          // Device connect to Server Failed
  {                           
    connectMQTTserver();        // Try to reconnect to the Server
  }
}