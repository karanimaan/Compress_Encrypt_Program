import os
import serial

# Program must not be run before STM sends data

serialPort = serial.Serial(port="COM4", baudrate=9600, bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE)

os.system(r"gcc .\main.c")  # compile decompression program

while True:
    # Wait until there is data waiting in the serial buffer
    if serialPort.in_waiting > 0:
        # Read data out of the buffer until a carriage return / new line is found
        original = serialPort.readline().strip()  # STM -> PC
        print(original)
        with open("original.txt", "wb") as f:
            f.write(original)
        with open("original.txt", "r") as f:
            original = f.read()
        print(original)

        serialString = serialPort.readline().strip()

        # write input from STM to file to be decompressed
        with open("compressed.txt", "wb") as f:
            f.write(serialString)
        os.system("a.exe")  # run decompression program

        print()
