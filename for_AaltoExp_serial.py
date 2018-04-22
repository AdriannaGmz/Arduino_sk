#!/usr/bin/env python3

#	Controls Arduino functions through serial port
#
# reads data from:	sensors and velocities
# sends commands for: 	motors and lights

import serial
from time import sleep

import sys
import select	# Data input without blocking, based on https://repolinux.wordpress.com/2012/10/09/non-blocking-read-from-stdin-in-python/

# lamp1 on             l1n
# lamp2 on             l2n     
# lamp1 off            l1f     
# lamp2 off            l2f     
# lamp1 toggle         l1t
# lamp2 toggle         l2t
# movements (front, back, left, right, stop):    mf mb ml mr ms


def send_command(line):
  print('read input:', line, end='')
  # ser.write(line+',')		# ser.write('l1n,')		# ser.write('mf,') ...


def read_data():
  print('no input, so we read data')
  # print(ser.read())  # turn this into reading specific strings from sensor readings




def main():
	# If there's input ready: do send_command, else do read_data. 

	while 1:
		while sys.stdin in select.select([sys.stdin], [], [], 0)[0]:
			line = sys.stdin.readline()
			if line:
				send_command(line)
			else: 	# an empty line means stdin has been closed
				print('eof')
				exit(0)
		else:
			read_data()
		sleep(0.1) #sec


# ADDING THE SERIAL COMMUNICATION

	# while 1:
	# 	try:
	# 		#ser = serial.Serial('/dev/ttyACM0',9600)
	# 		ser = serial.Serial('/dev/ttyACM0',115200)
	# 		while sys.stdin in select.select([sys.stdin], [], [], 0)[0]:
	# 			line = sys.stdin.readline()
	# 			if line:
	# 				send_command(line)
	# 			else: 	# an empty line means stdin has been closed
	# 				print('eof')
	# 				exit(0)
	# 		else:
	# 			read_data()
	# 		sleep(0.1) #sec
	# 	except:
	# 		print('No serial device to talk to')







if __name__ == "__main__":
   main()