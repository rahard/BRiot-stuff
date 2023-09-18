import paho.mqtt.client as paho

def on_connect(client, userdata, flags, rc):
	print("Connected with result code "+str(rc))
	client.subscribe("inTopic")

def on_message(client, userdata, msg):
	print(f'topic: {msg.topic} - msg: {msg.payload.decode()}')

client = paho.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("mqtt.luqmanr.xyz", 1883, 60)

client.loop_forever()
