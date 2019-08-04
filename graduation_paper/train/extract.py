#!/usr/local/bin/python3
# -*- coding: utf-8 -*-

import sys

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('Usage: python3 extract.py <log path>')
        sys.exit()

    logfile = sys.argv[1]

    # store train log
    extract_datas = []

    with open(logfile, 'r') as f:
        all_lines = f.readlines()
        for line in all_lines:
            if line.find('TrainLog') != -1:
                extract_datas.append(line[line.find('TrainLog') + 10:])

    with open(logfile + '.extract', 'w') as f:
        for data in extract_datas:
            f.write(data)
