import os
import serial

serialPort = serial.Serial(port="COM4", baudrate=9600, bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE)

os.system("gcc .\main.c")

while 1:
    # Wait until there is data waiting in the serial buffer
    if serialPort.in_waiting > 0:
        # Read data out of the buffer until a carriage return / new line is found
        serialString = serialPort.readline()  # STM -> PC
        serialString = serialString.strip()

        # Print the contents of the serial data
        #print(serialString)

        # write input from STM to file to be decoded
        with open("encoded.txt", "wb") as f:
            f.write(serialString)
        os.system("a.exe")
