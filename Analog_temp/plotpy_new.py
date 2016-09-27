import matplotlib.pyplot as plt
from numpy import *
import serial
from drawnow import *

_valuesSerial = []
_valuesTemp = []

plt.ion()

serialPort = serial.Serial('/dev/cu.usbmodem1411', 9600)

def thermister(RawADC):         ##Function to convert serial reading into temperature
    Temp = log(((10240000/RawADC) - 10000))
    ##Temp = log(1000.0 / (1024.0/ RawADC -1))
    Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp )
    Temp = Temp - 273.15; ## Convert Kelvin to Celcius
    print("%.2f degree Celsius \n" %(float(Temp)))

def plotGraph(x,y):
    la = plt.plot(x,y,'b-',label='Temperature')
    lx = plt.xlabel("seconds")
    ly = plt.ylabel("Temperature")
    grd = plt.grid(True)
    ttl = plt.title("Realtime Temperature")
    leg = plt.legend(loc="upper right")
    ##return la

while True:
    while (serialPort.inWaiting()==0): ##Getter:Get the number of bytes in the input buffer; Type: int
        pass
    serialReading = serialPort.readline(500) ## timeout necessary with readline(try 500)

    try:
        serialReadingInt = int(serialReading)
        print("\nSerial Reading: %d" %(serialReadingInt))
        if (serialReadingInt <= 1024 and serialReadingInt >=0):
            for i in range(500):
                TemperatureC = float(thermister(serialReadingInt))
                ##print("\n %d degree Celsius \n" % (TemperatureC))
                _valuesSerial.append(serialReadingInt)
                _valuesTemp.append(TemperatureC)
                ##drawnow(plotGraph(i,_valuesTemp))
                drawnow(plotGraph(i,TemperatureC))               
        else:
            print("Invalid Serial reading!")
    except ValueError:
        print("Invalid Value.")

serialPort.close()

        
                
                
            
            
            
