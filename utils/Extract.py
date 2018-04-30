#!/usr/bin/python  
#coding=utf-8  

import json 

y=[]
f=open('/home/mrd/桌面/log.txt','r')
for line in f.readlines():
	t=line.find('H=')
	if t!=-1:
		y.append(float(line[t+2:len(line)]))
s=json.dumps(y)
fp=open('/home/mrd/桌面/json.txt','a')
fp.write(s+'\n')
f.close()
fp.close()
