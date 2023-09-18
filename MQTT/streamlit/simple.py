import streamlit as st
import matplotlib.pyplot as plt
import time

colors = ['red','green','blue']
while True:
    for color in colors:
        figure, axes = plt.subplots()
        Drawing_colored_circle = plt.Circle(( 0.6 , 0.6 ), 0.2, color=color )
        
        axes.set_aspect( 1 )
        axes.add_artist( Drawing_colored_circle )
        plt.title( 'Colored Circle' )
        plt.axis('off')

        st.pyplot(figure, clear_figure=True)
        time.sleep(0.5)
