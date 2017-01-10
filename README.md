# BRiot-stuff
This is a collection of my IoT stuff.
Mainly for teaching and fun.

LED: this directory consists of LEDs related code. Loads of fun!
button: directory for button stuff

The C directory is a collection of codes in C language,
as scratchpads (for testing ideas).

The MQTT directory is for MQTT with IoT.
I use DycodeX Espectro dev board (which is EPS8266-based).

Notes:
= platformio
  to use platformio with bluetooth devices, eg. Bluino-One,
  use the following command (assuming you have /dev/cu.Bulino-ONE20-DevB
  as your bluetooth port; check with platformio device list)

platformio run -t upload --upload-port /dev/cu.Bluino-ONE20-DevB

=

Enjoy

Budi Rahardjo

* twitter: @rahard
* blog: rahard.wordpress.com
* email: rahard@gmail
