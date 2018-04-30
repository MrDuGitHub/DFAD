#!/usr/bin/python  
#coding=utf-8  

import numpy as np
import matplotlib.pyplot as plt
import json

y0=[]
y1=[]
fp=open('/home/mrd/桌面/json.txt','r')
#for line in fp.readlines():
y=fp.readlines()
y0=json.loads(y[0])
y1=json.loads(y[1])
x0=[]
x1=[]
for i in range(len(y0)):
	x0.append(i*5+5)
for i in range(len(y1)):
	x1.append(i*5+5)
plt.figure(figsize=(12,8)) #创建绘图对象  
plt.plot(x0,y0,"bo",x0,y0,'k')   #在当前绘图对象绘图（X轴，Y轴，蓝色虚线，线宽度）  
plt.plot(x1,y1,"ro",x1,y1,'k')
plt.xlabel("Time(s)") #X轴标签  
plt.ylabel("Entropy")  #Y轴标签  
plt.title("DDos attack") #图标题 
my_x_ticks = np.arange(0, 210, 10)
my_y_ticks = np.arange(0, 1.2, 0.1)
plt.xticks(my_x_ticks)
plt.yticks(my_y_ticks)
 
plt.show()  #显示图
