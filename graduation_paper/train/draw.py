#!/usr/local/bin/python3
# -*- coding: utf-8 -*-

import numpy as np
import pickle
import matplotlib.pyplot as plt

dumpfile = 'tmp/pagerank.tmp'

def sample_draw(results, labels, dump = True):
    if dump:
        dump_object = {"results": results, "labels": labels}
        with open(dumpfile, 'wb') as f:
            pickle.dump(dump_object, f, pickle.HIGHEST_PROTOCOL) 

    dr = []
    dl = []
    random_index = np.unique(np.random.randint(0, len(results), 50)) 
    for i in range(len(results)):
        if i in random_index:
            dr.append(results[i])
            dl.append(labels[i])

    fig = plt.figure()
    plt.suptitle("runtime predict")
    plt.plot(list(range(1, len(dr) + 1)), dr, label='predict', linestyle='solid', color='red', marker='*', ms=5)
    plt.plot(list(range(1, len(dr) + 1)), dl, label='real', linestyle='solid', color='green', marker='^', ms=5)
    plt.xlabel('number')
    plt.ylabel('time (ms)')
    plt.legend()
    plt.show()

if __name__ == '__main__':
    print("--")
    with open(dumpfile, 'rb') as f:
        dump_object = pickle.load(f)
    sample_draw(results = dump_object["results"], labels = dump_object["labels"], dump = False)
