# Python MQTT Test Program

# https://testclient-cloud.mqtt.cool/
import paho.mqtt.client as mqtt

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe("subTopic")

def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

# client.connect("broker.mqtt.cool", 1883, 60)
client.connect("broker.emqx.io", 1883, 60)
client.publish("willingblank", "Hello, World willingblank!")

client.loop_forever()
