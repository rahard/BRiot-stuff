import time
import streamlit as st
import paho.mqtt.client as paho
# from multiprocessing import Process
import threading
from streamlit.runtime.scriptrunner import add_script_run_ctx

from PIL import Image
from pathlib import Path

from bubbles.emitter import Emitter
from bubbles.particle import Particle
from bubbles.particle_effect import ParticleEffect
from bubbles.renderers.image_effect_renderer import ImageEffectRenderer

def ultrasonic_mode():
    st.session_state["mode"] = st.selectbox(
        'Select interactivity mode',
        ('particles', 'color', 'position', 'intensity'))

def on_connect(client, userdata, flags, rc):
	print("Connected with result code " + str(rc))
	client.subscribe("particles")
	client.subscribe("color")
	client.subscribe("position")

def on_message(client, userdata, msg):
    # st.write(f'topic: particles - msg: {msg.payload.decode()}')
    global PARTICLE_TYPE
    global PARTICLE_POSITION
    global PARTICLE_COLOR
    global particle_effect
    print(f'message:{msg.payload.decode()} - topic: {msg.topic}')
    if msg.topic == 'particles':
        PARTICLE_TYPE = msg.payload.decode()
        # load example json
        example_dir = "examples"
        with open(f"{example_dir}/{PARTICLE_TYPE}.json") as f:
            import json
            pe = json.load(f)
        particle_effect = ParticleEffect.load_from_dict(pe)
    elif msg.topic == 'color':
        PARTICLE_COLOR = msg.payload.decode()
    elif msg.topic == 'position':
        PARTICLE_POSITION = int(msg.payload.decode())

def render_particle():
    global PARTICLE_TYPE
    global PARTICLE_POSITION
    global PARTICLE_COLOR
    global particle_effect

    # render particle
    example_dir = "examples"
    r = ImageEffectRenderer()

    # load example json
    with open(f"{example_dir}/{PARTICLE_TYPE}.json") as f:
        import json
        pe = json.load(f)
    particle_effect = ParticleEffect.load_from_dict(pe)

    while True:
        # align the effect in the frame
        # at x=0px, y=128px
        if PARTICLE_POSITION >= 100:
            PARTICLE_POSITION = 5
        particle_effect.set_pos(PARTICLE_POSITION*13, 128)
        r.register_effect(particle_effect)
        # st.write(f'PARTICLE_TYPE: {PARTICLE_TYPE}')
        particle_effect.update()
        # (width, height)
        img_size = (512, 128)
        image = Image.new("RGB", img_size, (0, 0, 0, 255))

        # render particle
        r.render_effect(particle_effect,  image)

        # scale image to new size
        # original image * scale_factor
        scale_factor = 4
        image = image.resize((img_size[0]*scale_factor,img_size[1]*scale_factor))
        st.image(image)
        # time.sleep(0.01)

if __name__ == '__main__':
    PARTICLE_TYPE = "fireball"
    PARTICLE_POSITION = 0
    PARTICLE_COLOR = (255,255,255,255)
    mqtt_host = "192.168.249.249"
    mqtt_port = 1883

    client = paho.Client()
    client.on_connect = on_connect
    client.on_message = on_message

    # # call options
    # ultrasonic_mode()

    st.write(f'MQTT Host: `{mqtt_host}`')
    st.write(f'MQTT Port: `{mqtt_port}`')
    st.write(f'topic: `particles` -  messages (pick one): `[ bubbles, confetti, explosion, fireball, hearts, tornado ]`')
    st.write(f'topic: `position` - messages (pick one): `[0-512]`')
    with st.empty():
        client.connect_async(mqtt_host, mqtt_port, 60)
        client.loop_start()
        render_particle()