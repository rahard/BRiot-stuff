import time
import streamlit as st
import paho.mqtt.client as paho

from PIL import Image
from pathlib import Path

from bubbles.emitter import Emitter
from bubbles.particle import Particle
from bubbles.particle_effect import ParticleEffect
from bubbles.renderers.image_effect_renderer import ImageEffectRenderer

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
    # at x=0px, y=128px
    particle_effect.set_pos(0, 128)

    r.register_effect(particle_effect)

    Path(IMG_DIR).mkdir(parents=True, exist_ok=True)
    for i in range(260):
        particle_effect.update()
        if i > 0:
            # (width, height)
            img_size = (512, 128)
            image = Image.new("RGB", img_size, (0, 0, 0, 255))

            # change particle type halfway through
            if i == 130:
                pe['emitters'][0]['particle_settings']['red'] = [55, 255]
                pe['emitters'][0]['particle_settings']['blue'] = [255, 255]
                particle_effect.update()

            # update particle position
            particle_effect.set_pos(0+(i*2), 128)

            # render particle
            r.render_effect(particle_effect,  image)
            # scale image to new size
            # original image * scale_factor
            scale_factor = 4
            image = image.resize((img_size[0]*scale_factor,img_size[1]*scale_factor))
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
