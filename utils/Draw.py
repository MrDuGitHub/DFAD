#!/usr/bin/python  
#coding=utf-8  

import numpy as np
import matplotlib.pyplot as plt

def readfile(filename):
    with open(filename,'r') as f:
        for line in f.readlines():
			if line[0]=='H':
				#print line
				#print line[2,len(line)]
				y.append(float(line[2:len(line)]))

y=[]
readfile('/home/mrd/桌面/log.txt')
x=[]
for i in range(len(y)):
	x.append(i*5+5)
plt.figure(figsize=(12,8)) #创建绘图对象  
plt.plot(x,y,"bo",x,y,'k')   #在当前绘图对象绘图（X轴，Y轴，蓝色虚线，线宽度）  
plt.xlabel("Time(s)") #X轴标签  
plt.ylabel("Entropy")  #Y轴标签  
plt.title("DDos attack") #图标题 
my_x_ticks = np.arange(0, 210, 10)
my_y_ticks = np.arange(0, 1.2, 0.1)
plt.xticks(my_x_ticks)
plt.yticks(my_y_ticks)
 
plt.show()  #显示图  
plt.savefig("line.jpg") #保存
