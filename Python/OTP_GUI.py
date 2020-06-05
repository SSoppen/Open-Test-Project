import serial
import time
from tkinter import *
from decimal import Decimal
import csv

#Set the default values that appear in GUI
defaultPort = 'COM8'
defaultFrequency = 9600



def start():
    start_time = time.time()
    CSVName = filename.get() + "OTP" + ".csv"
    try:
        ser = serial.Serial(port.get(), frequency.get(), timeout=3) # Set your port and frequency

        print("Connecting on: " + port.get() + " at " + frequency.get() + "hz")
        while 1:

            #Determines how long the program has been running for
            runTime = Decimal(time.time() - start_time)
            runTime = round(runTime,2)

            data = ser.readline().decode('ascii')

            if data != "":
                print(data + " " + str(runTime) + " " + time.asctime())

                #Write to CSV file
                with open(CSVName, "a") as file:
                    writer = csv.writer(file, delimiter=",")
                    writer.writerow([data, str(runTime), time.asctime()])
        else:
            print("Error reading data")
    except:
       print("Failed to connect")

#Tkinter values
root = Tk()

root.title("Open Test Project")
labelfilename = Label(root, text="CSV Filename")
filename = Entry(root, width=20, borderwidth=2)
filename.grid(row=0, column=1, pady=(10, 20), padx=(0, 15))
labelfilename.grid(row=0, column=0, pady=(10, 20), padx=(0, 15))

labelPort = Label(root, text="port")
labelFrequency = Label(root, text="frequency",)
port = Entry(root, width=20, borderwidth=2)
port.insert(0, defaultPort)
frequency = Entry(root, width=20, borderwidth=2)
frequency.insert(0, defaultFrequency)
port.grid(row=1, column=1, pady=(5, 0), padx=(0, 15))
frequency.grid(row=2, column=1, pady=(5, 0), padx=(0, 15))
labelPort.grid(row=1, column=0, padx=(15, 0))
labelFrequency.grid(row=2, column=0, padx=(15, 0))

startButton = Button(root, text="Start", command=start)
startButton.grid(row=9, column=1)

def startEnter(event):
    start()

root.bind("<Return>", startEnter)

root.mainloop()
