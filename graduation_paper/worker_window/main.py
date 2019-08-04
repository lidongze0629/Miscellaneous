import os
import sys

import matplotlib.pyplot as plt

# com-friendster 65608366

if __name__ == '__main__':
    logfile = sys.argv[1]
    fnum = int(sys.argv[2])

    # init worker windows
    worker_windows = []
    total_windows = []
    for i in range(fnum):
        worker_windows.append([])
    for i in range(100):
        total_windows.append(0)

    max_step = 0

    with open(logfile, 'r') as f:
        all_lines = f.readlines()
        for line in all_lines:
            if line.find('worker window') != -1:
               data = line[line.find('worker window'):]
               dlist = data.split(' ')
               fid = int(dlist[2])
               step = int(dlist[3])
               num = int(dlist[4])
               worker_windows[fid].append(num)
               total_windows[step] = total_windows[step] + num
               if step > max_step:
                   max_step = step
    with open(logfile + '.output', 'w') as f:
        f.write(str(total_windows[:max_step + 1]))

    # print(len(list(range(1, max_step + 1))))
    # print(len(total_windows[:max_step + 1]))
    for i in range(step + 1):
        # here you should seted by graph
        total_windows[i] = total_windows[i] / 65608366
    plt.plot(list(range(1, max_step + 2)), total_windows[:max_step + 1], linestyle='dotted', color='black', marker='*', ms=6)
    plt.xlabel('superstep')
    plt.ylabel('window size')
    plt.legend()
    plt.savefig(logfile + '.png')
    plt.show()
