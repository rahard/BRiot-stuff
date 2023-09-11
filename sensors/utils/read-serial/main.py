import serial

s = serial.Serial('/dev/cu.usbserial-10')
for x in range(100):
   res = s.read()
   print(res)
