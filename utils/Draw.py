#!/usr/bin/python  
#coding=utf-8  

import numpy as np
import matplotlib.pyplot as plt
import json

y0=[]
y1=[]
y2=[]	
fp=open('json.txt','r')
y=fp.readlines()
y0=json.loads(y[0])
y1=json.loads(y[1])
y2=json.loads(y[2])
x0=[]
x1=[]
x2=[]
#for i in range(len(y0)):
#	x0.append(i*5+5)
#for i in range(len(y1)):
#	x1.append(i*10+10)
#for i in range(len(y2)):
#	x2.append(i*20+20)
for i in range(len(y0)):
	x0.append(i*5+5)
for i in range(len(y1)):
	x1.append(i*5+5)
for i in range(len(y2)):
	x2.append(i*5+5)

plt.figure(figsize=(12,8)) #创建绘图对象  
##plt.plot(x0,y0,"ro-",x0,y0,'k',label='Attack')   #在当前绘图对象绘图（X轴，Y轴，蓝色虚线，线宽度）  
##plt.plot(x1,y1,"go-",x1,y1,'k',label='Normal')
##plt.plot(x0,y0,"ro-",label='Attack_C')   #在当前绘图对象绘图（X轴，Y轴，蓝色虚线，线宽度）  
#plt.plot(x1,y1,"bo-",label='Attack_S')
#plt.plot(x0,y0,"ro",label='min tax')
plt.plot(x0,y0,"-o",label='a = 1')
plt.plot(x1,y1,"-o",label='a = 4')
plt.plot(x2,y2,"-o",label='a = 7')
plt.xlabel("Time(s)") #X轴标签  
plt.ylabel("Normalized Entropy Value")  #Y轴标签  
plt.title("The normalized entropy value") #图标题 
my_x_ticks = np.arange(0, 650,50)
my_y_ticks = np.arange(0, 1.2, 0.1)
plt.xticks(my_x_ticks)
plt.yticks(my_y_ticks)

plt.legend()
plt.show()  #显示图
