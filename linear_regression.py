import numpy as  np 
import serial
train=[[0,0],[64,15.95],[128,31.95],[192,47.86],[256,63.81],[320,79.77],[384,95.72],[448,111.67],
[512,127.68],[576,143.58],[640,159.53],[704,175.48],[768,191.44],[832,207.39],[896,223.34],
[960,239.3],[1024,255.25]]
import time
m=0
b=0

lr=0.00000138715


for i in  range(100000):
	N=float(len(train))             
	b_grad=0
	m_grad=0
	for j in range(0,len(train)):
   		point=train[j]
   		m_grad += -(2/N)*point[0]*(point[1]-(m*point[0]+b))
		b_grad += -(2/N)*(point[1]-(m*point[0]+b))
    	
	new_b=b-(lr*b_grad)
	new_m=m-(lr*m_grad)
	if i%1000==0 :
		print new_m,new_b
ser=serial.Serial('COM5',baudrate=9600)

while(True):
	data=""
	datadec=''
	dataint=0
	while(ser.inWaiting()==0):
		pass
	data=ser.readline()
	datadec=data.strip()
	dataint=int(datadec)
	print dataint
	pred=dataint*new_m+new_b
	print pred
	datastr=str(pred)
	ser.write(datastr)



