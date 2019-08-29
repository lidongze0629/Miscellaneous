#!/usr/local/bin/python3
# -*- coding: utf-8 -*-

import numpy as np
import pickle
import matplotlib.pyplot as plt


def sample_draw():
    dr = [2636,2573,2562,2552,2532,2482,2485,2437,2441,2390,2385,2373,2390,2401,2407,2409,2410,2409,2427,2430,2467,2478,2489,2482,2497,2503,2510,2512,2518,2523,2548,2552,2563,2574,2581,2575,2577,2565,2542,2431,2392,2375,2341,2211,2197,2100,2004,1899,1765,1562,1302,1129,1072,992,887,875,776,754,738,658,643,562,512,472,412,331,2109,109,82,0]
    dl = [2636,2573,2562,2552,2532,2482,2485,2437,2441,2390,2385,2373,2390,2401,2407,2409,2410,2409,2427,2430,2467,2478,2489,2482,2497,2503,2510,2512,2518,2523,2548,2552,2563,2574,2581,2575,2577,2565,2542,2431,2392,2375,2341,2211,2197,2100,2004,1899,1765,1562,1302,1129,1072,992,887,875,776,754,738,658,643,562,512,472,412,331,2109,109,82,0]

    fig = plt.figure()
    plt.suptitle("runtime predict")
    plt.plot(list(range(1, len(dr) + 1)), dr, label='real arrival rate', linestyle='solid', color='black', marker='*', ms=2)
    plt.plot(list(range(1, len(dr) + 1)), dl, label='arrival rate estimation', linestyle='solid', color='black', marker='^', ms=2)
    plt.xlabel('Time (second)')
    plt.ylabel('Message Number / ms')
    plt.legend()
    plt.show()

if __name__ == '__main__':
    sample_draw()
