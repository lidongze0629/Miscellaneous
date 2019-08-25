import os
import sys

import matplotlib.pyplot as plt

# com-friendster 65608366
# livejournal 4847572
# usa_road 23947348

if __name__ == '__main__':
    logfile = sys.argv[1]
    fnum = int(sys.argv[2])

    total_windows = []
    with open(logfile, 'r') as f:
        lines = f.readlines()
        for line in lines:
            total_windows = line.split(",")

    max_step=len(total_windows)
    for i in range(max_step):
        # here you should seted by graph
        total_windows[i] = int(total_windows[i]) / 4847572
    plt.plot(list(range(1, max_step + 1)), total_windows[:max_step], linestyle='dotted', color='black', marker='*', ms=6)
    plt.xlabel('superstep')
    plt.ylabel('window size')
    #plt.ylim(0.0, 1.2)
    plt.legend()
    plt.savefig(logfile + '.png')
    plt.show()
