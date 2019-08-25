#!/usr/local/bin/python3
# -*- coding: utf-8 -*-

import sys

import numpy as np
import matplotlib.pyplot as plt

def readFromFile(path):
    data = []
    for i in range(4):
        data.append([])

    with open(path, 'r') as f:
        lines = f.readlines()
        for line in lines:
            line_array = line.split(' ')
            data[0].append(float(line_array[0]))
            data[1].append(float(line_array[1]))
            data[2].append(float(line_array[2]))
            data[3].append(float(line_array[3].strip()))
    return data

if __name__ == '__main__':
    data = readFromFile(sys.argv[1])
    # print(data)

    fig = plt.figure()
    plt.xticks(np.arange(64,193,32))
    # plt.yticks(np.arange(0,50,2))
    plt.plot([64,96,128,160,192], data[0], label='BSP', linestyle='-', color='black', marker='*', ms=4)
    plt.plot([64,96,128,160,192], data[1], label='AP', linestyle='--', color='black', marker='^', ms=4)
    plt.plot([64,96,128,160,192], data[2], label='AAP', linestyle='-.', color='black', marker='o', ms=4)
    plt.plot([64,96,128,160,192], data[3], label='MPAP', linestyle=':', color='black', marker='D', ms=4)
    plt.ylabel('Time (seconds)')
    plt.legend()
    plt.show()
