#!/usr/local/bin/python3
# -*- coding: utf-8 -*-

import os
import sys
import time

import numpy as np
import matplotlib.pyplot as plt

from draw import sample_draw
from extract import GetAllData
from metric import printErrorMetrics

from rf import rf
from rr import rr
from nn import nn
from lr import lr


if __name__ == '__main__':
    extract_dir = sys.argv[1]
    fnum = int(sys.argv[2])

    """ datasets and labels's size is fnum """
    datasets, labels = GetAllData(extract_dir, fnum, 'sssp', total_vertex_num=23947348, L=1000000)
    # datasets, labels = GetAllData(extract_dir, fnum, 'sssp', total_vertex_num=65608366, L=10000000)

    """ ridge regression """
    sr, sl = rr(datasets, labels, fnum)

    """ neural network """
    #sr, sl = nn(datasets, labels, fnum)
    
    """ liner regression """
    #sr, sl = lr(datasets, labels, fnum)

    """ random forest """
    #sr, sl = rf(datasets, labels, fnum)

    """ draw picture """
    sample_draw(sr,sl)
