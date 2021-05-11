import serial as sr
import matplotlib.pyplot as plt
import smtplib

sender = 'liheng1012000@gmail.com'
receivers = ['liheng1012000@gmail.com']

message = """From: From Person <liheng1012000@gmail.com>
To: To Person <liheng1012000@gmail.com>
Subject: Error Alert

The speed of the water flow is too quick.
"""


plt.close('all')
s=sr.Serial('COM7',9600) # COM7 is the input from Xbee
plt.figure(1)
plt.grid()
plt.figure(2)
plt.grid()
plt.ion()
plt.show()

y1=0
y2=0
i=1
arry1=[]
arry2=[]
arry3=[]
arrx=[]
count=0
alpha= 0.73
Vprev=0
while i<10000:
    a=s.readline()  #Value before filter
    b=float(a.decode())
    arry1.append(b)
    c=alpha*Vprev + (1-alpha)*b #Low pass filter
    Vprev=c
    arry2.append(c)
    v=((c*10)/1.1304)
    arry3.append(v) #Value of speed 
    arrx.append(0.5*i)


    print(b)
    print(c)
    print(v)
    plt.figure(1)
    plt.title("Flow sensor value before and after filter")
    plt.xlabel("Time(Sec)")
    plt.ylabel("Liters/Min")
    plt.plot(arrx,arry1,'r.-',arrx,arry2,'b.-')
    plt.legend(('Value before filter','Value after filter'),loc='upper left')


    plt.figure(2)
    plt.title("Speed of the surf-board vehicle")
    plt.xlabel("Time(Sec)")
    plt.ylabel("Meters/Min")
    plt.plot(arrx,arry3,'y.-')

    plt.pause(0.001)
    i+=1
    if v>40:
        count+=1
        if count>5:
            smtpObj = smtplib.SMTP('localhost')
            smtpObj.sendmail(sender, receivers, message)
    else:
        count=0
    

s.close()