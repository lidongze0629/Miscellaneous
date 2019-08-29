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
    
    mpap = data[3]
    for i in range(len(data)):
        if i == 0:
            print("bsp")
        elif i == 1:
            print("ap")
        elif i == 2:
            print("aap")
        else:
            continue
        compair_data = data[i]
        for j in range(len(mpap)):
            if (compair_data[j] >= mpap[j]):
                print("j " + str((compair_data[j]-mpap[j]) / compair_data[j]))
            else:
                print("-j " + str((mpap[j] - compair_data[j]) / compair_data[j]))

