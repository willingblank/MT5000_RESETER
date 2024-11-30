
#include <mqtt.h>

WiFiClient wifiClient = getWifiClient();
PubSubClient mqttClient(wifiClient);

const char* mqttServer = "broker.mqtt.cool";
const char* subTopic = "willingblank_MT5000_RESETER";

void mqtt_Init()
{
  setMqttServer(mqttServer,1883);
  setMqttReceiveCallback(receiveCallback);
  connectMQTTserver(subTopic);
}

void mqttServerStart()
{
  if(mqttClient.connected())
  {
    mqttClient.loop();
  }
  else                          // Device connect to Server Failed
  {                           
    connectMQTTserver(subTopic);        // Try to reconnect to the Server
  }
}

void subscribeTopic(const char * subTopic)
{
  if(mqttClient.subscribe(subTopic))
  {
    Serial.printf("Subscrib Topic = [%s] \r\n",subTopic);
  }
  else
  {
    Serial.println("Subscribe Topic Failed...");
  }  
}

void connectMQTTserver(const char* subTopic)
{
  // 根据ESP8266的MAC地址生成客户端ID（避免与其它ESP8266的客户端ID重名）
  String clientId = "ESP01S-" + WiFi.macAddress();
 
  // Connect to MQTT Server
  if (mqttClient.connect(clientId.c_str())) 
  { 
    Serial.println("MQTT Server Connected.");
    Serial.print("ClientId:  ");
    Serial.println(clientId);
    subscribeTopic(subTopic);
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

void setMqttServer(const char *mqttServer, int port)
{
  mqttClient.setServer(mqttServer, port);
}


void setMqttReceiveCallback(MqttReceiveCallback_FuncPtr funcPrt)
{
    mqttClient.setCallback(funcPrt);
}

