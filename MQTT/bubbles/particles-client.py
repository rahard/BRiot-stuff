from PIL import Image, ImageDraw
from pathlib import Path
import time

import streamlit as st
from bubbles.emitter import Emitter
from bubbles.particle import Particle
from bubbles.particle_effect import ParticleEffect
from bubbles.renderers.image_effect_renderer import ImageEffectRenderer

import paho.mqtt.client as paho

def on_connect(client, userdata, flags, rc):
	print("Connected with result code "+str(rc))
	client.subscribe("particles")

def on_message(client, userdata, msg):
    print(f'topic: {msg.topic} - msg: {msg.payload.decode()}')
    example_file = msg.payload.decode()
    example_dir = "examples"
    IMG_DIR = f"out/{example_file}"

    if example_file not in ["bubbles", "confetti", "explosion", "fireball", "hearts", "tornado"]:
        st.write(f"particle {example_file} not recognized!")
        return

    r = ImageEffectRenderer()

    # load example json
    with open(f"{example_dir}/{example_file}.json") as f:
        import json
        pe = json.load(f)
    particle_effect = ParticleEffect.load_from_dict(pe)

    # align the effect in the frame
    particle_effect.set_pos(60, 128)

    r.register_effect(particle_effect)

    Path(IMG_DIR).mkdir(parents=True, exist_ok=True)
    for i in range(260):
        particle_effect.update()
        if i > 0:
            image = Image.new("RGB", (128, 128), (0, 0, 0, 255))
            r.render_effect(particle_effect,  image)

            # image.save(f"{IMG_DIR}/{str(i)}.png")
            image = image.resize((512,512))
            st.image(image)
            time.sleep(0.01)

if __name__ == '__main__':
    client = paho.Client()
    client.on_connect = on_connect
    client.on_message = on_message

    client.connect("mqtt.luqmanr.xyz", 1883, 60)

    st.write(f'topic: particles')
    st.write(f'particle messages (pick one): [ bubbles, confetti, explosion, fireball, hearts, tornado ]')
    with st.empty():
        client.loop_forever()