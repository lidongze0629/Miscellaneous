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


if __name__ == '__main__':
    extract_dir = sys.argv[1]
    fnum = int(sys.argv[2])

    """ datasets and labels's size is fnum """
    datasets, labels = GetAllData(extract_dir, fnum, 'pagerankx')

    """ random forest """
    # sr, sl = rf(datasets, labels, fnum)
    # sample_draw(sr, sl)

    """ ridge regression """
    # sr, sl = rr(datasets, labels, fnum)
    # sample_draw(sr, sl)

    """ neural network """
    sr, sl = nn(datasets, labels, fnum)
    sample_draw(sr, sl)
    
