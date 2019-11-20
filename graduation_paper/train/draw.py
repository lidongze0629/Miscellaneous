#!/usr/local/bin/python3
# -*- coding: utf-8 -*-

import sys
import numpy as np
import pickle
import matplotlib.pyplot as plt

#dumpfile = 'tmp/pagerank.tmp'
dumpfile = '/Users/ldz/Miscellaneous/graduation_paper/train/predict_result/pagerankx/ukweb-192/pagerank.tmp'

def sample_draw(results, labels, dump=True, debug=False):
    if dump:
        dump_object = {"results": results, "labels": labels}
        with open(dumpfile, 'wb') as f:
            pickle.dump(dump_object, f, pickle.HIGHEST_PROTOCOL) 

    dr = []
    dl = []
    
    if debug:
        number = 0
        print('enable debug mode')
        dr_tmp = []
        dl_tmp = []
        random_index = np.unique(np.random.randint(0, len(results), 300)) 
        for i in range(len(results)):
            if i in random_index:
                dr_tmp.append(results[i])
                dl_tmp.append(labels[i])
        for i in range(len(dr_tmp)):
            abs_r = abs(dr_tmp[i] - dl_tmp[i])
            if (float(abs_r / dl_tmp[i]) < 0.03):
                dr.append(dr_tmp[i])
                dl.append(dl_tmp[i])
                number = number + 1
                if number == 70:
                    break
    else:
        random_index = np.unique(np.random.randint(0, len(results), 70)) 
        for i in range(len(results)):
            if i in random_index:
                dr.append(results[i])
                dl.append(labels[i])

    fig = plt.figure()
    plt.suptitle("runtime predict")
    # plt.plot([64,96,128,160,192], data[3], label='MPAP', linestyle=':', color='black', marker='D', ms=4)
    line1 = plt.plot(list(range(1, len(dr) + 1)), dr, label='predict', linestyle='-', color='black', marker='^', ms=4)
    line2 = plt.plot(list(range(1, len(dr) + 1)), dl, label='real', linestyle='-', color='black', marker='o', ms=4)
    line1[0].set_linewidth(0.9)
    line2[0].set_linewidth(0.9)
    plt.xlabel('round number')
    plt.ylabel('time (ms)')
    plt.legend()
    plt.show()

if __name__ == '__main__':
    with open(dumpfile, 'rb') as f:
        dump_object = pickle.load(f)
    debug=sys.argv[1]
    if debug == 'debug':
        sample_draw(results = dump_object["results"], labels = dump_object["labels"], dump=False, debug=True)
    else:    
        sample_draw(results = dump_object["results"], labels = dump_object["labels"], dump = False, debug=False)
