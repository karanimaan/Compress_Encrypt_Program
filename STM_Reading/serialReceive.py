import os
import numpy as np
import serial
from matplotlib import pyplot as plt

# Program must not be run before STM sends data

# connect to UART
serialPort = serial.Serial(port="COM4", baudrate=9600, bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE)

os.system(r"gcc .\main.c")  # compile decompression program

i = -1  # index of data: (accel_x, accel_y, accel_z, gyro_x, gyro_y, gyro_z)
headings = 'accel_x, accel_y, accel_z, gyro_x, gyro_y, gyro_z'.split(', ')

# init set of lists that hold recordings of either accel_x, accel_y, accel_z, gyro_x, gyro_y, or gyro_z
original_list = [[] for i in range(6)]  # data before compression
decompressed_list = [[] for i in range(6)]  # data after decompression

while len(original_list[0]) < 10:    # We want 10 recordings of each field
    # Wait until there is data waiting in the serial buffer
    if serialPort.in_waiting > 0:

        # We are reading one data value at a time (e.g. accel_x)
        # original data is only being transmitted from STM to be compared to compressed and decompressed data
        original_bytes = serialPort.readline().strip()

        # This is to make sure data starts reading from accel_x first
        if original_bytes == b'':
            i = 0
            continue
        if i == -1:
            continue

        # Write bytes and read string (This is done to convert bytes to string)
        with open("original.txt", "wb") as f:
            f.write(original_bytes)
        with open("original.txt", "r") as f:
            original_str = f.read()
        original_list[i].append(float(original_str))

        compressed_str = serialPort.readline().strip()  # read the compressed data of original_str

        # write input from STM to file to be decompressed
        with open("compressed.txt", "wb") as f:
            f.write(compressed_str)
        os.system("a.exe")  # run decompression program

        # read from decompressed.txt and print
        with open("decompressed.txt", "r") as f:
            decompressed_str = f.read().strip()

        decompressed_list[i].append(float(decompressed_str))

        # ATPs
        print()
        print('Compare contents of original data and decompressed data:')
        print(f'original_str = {original_str}')
        print(f'decompressed_str = {decompressed_str}')
        print(f'Decompressed string is identical to original :)' if decompressed_str == original_str else '')
        print()
        print('Compare size of original data and compressed data:')
        print(f'length of original = {len(original_str)}')
        print(f'length of compressed string = {len(compressed_str)}')
        print(f'Compressed string is smaller than original :)' if len(compressed_str) < len(original_str) else '')
        print()

        i += 1
        if i == 6:
            print(headings)

            # print latest values
            print([v[-1] for v in original_list])
            print([v[-1] for v in decompressed_list])

for i in range(6):  # for data in [accel_x, accel_y, accel_z, gyro_x, gyro_y, gyro_z]

    # fft original data
    original_freq = np.abs(np.fft.fft(original_list[i]))    # list of Fourier coefficients
    print(f'original_freq = {original_freq}')

    # fft decompressed data
    decompressed_freq = np.abs(np.fft.fft(original_list[i]))
    print(f'decompressed_freq = {decompressed_freq}')

    # Check if original and decompressed data's Fourier transforms identical
    print('\nAre original and decompressed data\'s Fourier transforms identical?')
    print(all(original_freq == decompressed_freq))

    # Plot FFTs
    fig, axs = plt.subplots(2)
    fig.suptitle(headings[i])
    axs[0].stem(original_freq)
    axs[1].stem(decompressed_freq)
    plt.savefig(f'Fourier_Plots/{headings[i]}.png')
