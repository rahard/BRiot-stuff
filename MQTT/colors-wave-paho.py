import paho.mqtt.client as paho
import time

def on_connect(client, userdata, flags, rc):
	print("Connected with result code "+str(rc))
	client.subscribe("inTopic")

def on_message(client, userdata, msg):
	print(f'topic: {msg.topic} - msg: {msg.payload.decode()}')

def shift(seq, n=0):
    a = n % len(seq)
    return seq[-a:] + seq[:-a]

def synchronous_colors(colors):
	i = 0
	while True:
		if i == 3:
			i = 0
		client.publish(f'color1', colors[i])
		time.sleep(0.25)
		client.publish(f'color2', colors[i])
		time.sleep(0.25)
		client.publish(f'color3', colors[i])
		time.sleep(0.25)
		client.publish(f'color4', colors[i])
		time.sleep(0.25)
		i += 1

def shifting_colors(colors):
	while True:
		client.publish(f'color1', colors[0])
		time.sleep(0.25)
		client.publish(f'color2', colors[1])
		time.sleep(0.25)
		client.publish(f'color3', colors[2])
		time.sleep(0.25)
		client.publish(f'color4', colors[3])
		time.sleep(0.75)
		colors = shift(colors, 1)

client = paho.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("mqtt.luqmanr.xyz", 1883, 60)

colors = ['red', 'green', 'blue', 'white']

# shifting_colors(colors)
synchronous_colors(colors)