import os
import serial

serialPort = serial.Serial(port="COM9", baudrate=9600, bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE)

serialString = ""  # Used to hold data coming over UART

while (1):
    # Wait until there is data waiting in the serial buffer
    if (serialPort.in_waiting > 0):

        # Read data out of the buffer until a carraige return / new line is found
        serialString = serialPort.readline()    # STM -> PC

        # Print the contents of the serial data
        print(serialString.decode('Ascii'))

        # write input from STM to file to be decoded
        '''with open("encoded.txt", "w") as f:
            f.write(serialString)
        os.system("a.exe")'''