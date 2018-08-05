#!/usr/bin/python  
#coding=utf-8  

import json 

y=[]
f=open('../log.txt','r')
for line in f.readlines():
	t=line.find('H=')
	if t!=-1:
		if float(line[t+2:len(line)])>0.001:
			y.append(float(line[t+2:len(line)]))
print(y)
s=json.dumps(y)
fp=open('json.txt','a')
fp.write(s+'\n')
f.close()
fp.close()
