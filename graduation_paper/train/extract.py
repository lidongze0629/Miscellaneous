#!/usr/local/bin/python3
# -*- coding: utf-8 -*-

import os
import sys

def ParsePagerankx(line):
    data_array = line.split(';')
    fid = int(data_array[0][4:])
    runtime = float(data_array[1]) * 1000

    """ construct feature vector 
        ivnum, ovnum, tvnum, enum, msgnum
    """
    feature_vector = []
    feature_vector.append(int(data_array[2]))
    feature_vector.append(int(data_array[3]))
    feature_vector.append(int(data_array[4]))
    feature_vector.append(int(data_array[5]))
    feature_vector.append(int(data_array[6]))

    return fid, runtime, feature_vector
    
def ParseRoute(line, algo):
    if (algo == 'pagerankx'):
        return ParsePagerankx(line)
    else:
        raise NameError

""" moudle extern """
def GetAllData(extract_dir, fnum, algo):
    """ init data structure """
    datasets = []; labels = []
    for i in range(fnum):
        datasets.append([])
        labels.append([])

    """ scan '.extract' file  """
    files = [f for f in os.listdir(extract_dir) if os.path.splitext(os.path.join(extract_dir, f))[1] == '.extract']

    """ extract datasets and labels  """
    for file in files:
        with open(os.path.join(extract_dir, file), 'r') as f:
            all_lines = f.readlines()
            for line in all_lines:
                fid, label, features = ParseRoute(line, algo)
                datasets[fid].append(features)
                labels[fid].append(label)
    
    """ check  """
    for i in range(fnum):
        if len(datasets[i]) != len(labels[i]):
            raise IndexError

    return datasets, labels

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
