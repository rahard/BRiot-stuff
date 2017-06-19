
import paho.mqtt.client as paho

def on_connect(client, userdata, flags, rc):
	print("Connected with result code "+str(rc))
	client.subscribe("led1")

def on_message(client, userdata, msg):
	print(msg.topic+" "+str(msg.payload))

client = paho.Client()
client.on_connect = on_connect
client.on_message = on_message

#client.connect("192.168.4.242", 1883, 60)
client.connect("192.168.43.67", 1883, 60)

client.loop_forever()

