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
y0=json.loads(y[2])
y1=json.loads(y[0])
x0=[]
x1=[]
for i in range(len(y0)):
	x0.append(i*5+5)
for i in range(len(y1)):
	x1.append(i*5+5)
plt.figure(figsize=(12,8)) #创建绘图对象  
##plt.plot(x0,y0,"ro-",x0,y0,'k',label='Attack')   #在当前绘图对象绘图（X轴，Y轴，蓝色虚线，线宽度）  
##plt.plot(x1,y1,"go-",x1,y1,'k',label='Normal')
plt.plot(x0,y0,"ro-",label='Attack_C')   #在当前绘图对象绘图（X轴，Y轴，蓝色虚线，线宽度）  
plt.plot(x1,y1,"bo-",label='Attack_S')
##plt.plot(x0,y0,"ro",label='min tax')
plt.xlabel("Time(s)") #X轴标签  
plt.ylabel("Normalized Entropy Value")  #Y轴标签  
plt.title("The normalized entropy value") #图标题 
my_x_ticks = np.arange(0, 210, 10)
my_y_ticks = np.arange(0, 1.2, 0.1)
plt.xticks(my_x_ticks)
plt.yticks(my_y_ticks)

plt.legend()
plt.show()  #显示图
