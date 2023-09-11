# BRiot-stuff
This is a collection of my IoT stuff.
Mainly for teaching and fun.

LED: this directory consists of LEDs related code. Loads of fun!
boards: boards that I use; pin diagrams
button: directory for button stuff

The C directory is a collection of codes in C language,
as scratchpads (for testing ideas).

The Espectro directory is a collection of examples for Espectro board.

The MQTT directory is for MQTT with IoT.
I use DycodeX Espectro dev board (which is EPS8266-based).

sensors: directory for sensors related stuff
tested with NodeMCU


Notes:
=-=-=
= platformio
  to use platformio with bluetooth devices, eg. Bluino-One,
  use the following command (assuming you have /dev/cu.Bulino-ONE20-DevB
  as your bluetooth port; check with platformio device list)

platformio run -t upload --upload-port /dev/cu.Bluino-ONE20-DevB
or
pio run -t upload --upload-port /dev/cu.Bluino-ONE20-DevB

= old platformio has "lib_install" in platformio.ini
  but it has changed

Enjoy ...

Budi Rahardjo

* twitter: @rahard
* blog: rahard.wordpress.com
* email: rahard@gmail
