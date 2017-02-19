Files for LED-related codes/examples.

These files (examples) should work for Arduino boards and
ESPectro board (and perhaps other ESP-based boards).
The only thing that we have to consider is the pin arrangement.

Due to PlatformIO's configuration, current code is in "src" directory.
It's just for compiling. 

CODES and VIDEOS
* alternate.ino: 101010, then 010101, then 101010, ... etc
** video: https://www.youtube.com/watch?v=0iDvJEF6xGo

* enterexit.ino: lights entering ... then exiting ...
** video: https://www.youtube.com/watch?v=aHfWg2HMA3w

* knightrider.ino: lights going left to right to left ...
** video: https://www.youtube.com/watch?v=mcaNzt9-HAI
** for Arduino: https://www.youtube.com/watch?v=H4V8DN9CDO8

* ledmeter.ino: using LED as a meter (sort of), graphic equalizer?
** video: https://www.youtube.com/watch?v=0ADAIgwpQ5o

* rotate.ino: rotate (left/right) the content of LED 

* turnoff.ino: just to turn off LEDs

I will update those links with video links


BLUINO
To use bluino, check the device first
   platformio device list

   platformio run -t upload --upload-port /dev/cu.Bluino-ONE20-DevB

NodeMCU
   platformio run -t upload --upload-port /dev/cu.wchusbserial1410p
