import serial
import time
from datetime import datetime

def readlineCR(port):
    rv = ""
    while True:
        ch = port.read()
        rv += ch
        if ch=='\r' or ch=='':
            return rv

ser = serial.Serial('/dev/ttyUSB0', 38400)  # open serial port
print(ser.name)         # check which port was really used

while True:
	comando = readlineCR(ser)
	time.sleep(0.1)
	date = datetime.now().strftime("%d/%m/%Y %H:%M:%S");
	print(date +" > " + comando)
	if ("ATZ" in comando):
		ser.write("ELM327 v1.5 >")
	elif ("0100\r" in comando):
		time.sleep(0.5)
		ser.write("BUS INIT: ")
		time.sleep(1)
		ser.write("OK 4100BE3EB811 >")

	elif ("ATRV" in comando):
		ser.write("12.5 >")

	elif ("0105" in comando):
		ser.write("41057A >")

	elif ("010C" in comando):
		ser.write("410C1AF8 >")

	elif ("010F" in comando):
		ser.write("41054A >")

	elif ("010B" in comando):
		ser.write("410519 >")

	elif ("010E" in comando):
		ser.write("410519 >")

	elif ("0111" in comando):
		ser.write("410532 >")


