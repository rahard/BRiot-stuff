from PIL import Image, ImageDraw
from pathlib import Path
import time

import streamlit as st
from bubbles.emitter import Emitter
from bubbles.particle import Particle
from bubbles.particle_effect import ParticleEffect
from bubbles.renderers.image_effect_renderer import ImageEffectRenderer

EXAMPLE_FILE = "fireball"
EXAMPLE_DIR = "examples"
IMG_DIR = f"out/{EXAMPLE_FILE}"

r = ImageEffectRenderer()

# load example json
with open(f"{EXAMPLE_DIR}/{EXAMPLE_FILE}.json") as f:
    import json
    pe = json.load(f)
particle_effect = ParticleEffect.load_from_dict(pe)

# align the effect in the frame
particle_effect.set_pos(60, 128)

r.register_effect(particle_effect)

Path(IMG_DIR).mkdir(parents=True, exist_ok=True)
with st.empty():
    while True:
        for i in range(240):
            particle_effect.update()
            if i > 0:
                image = Image.new("RGB", (128, 128), (0, 0, 0, 255))
                r.render_effect(particle_effect,  image)

                # image.save(f"{IMG_DIR}/{str(i)}.png")
                image = image.resize((512,512))
                st.image(image)
                time.sleep(0.01)
