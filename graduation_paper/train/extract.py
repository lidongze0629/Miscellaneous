#!/usr/local/bin/python3
# -*- coding: utf-8 -*-

import os
import sys
import math

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

def ParseHITS(line):
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
    feature_vector.append(int(data_array[7]))

    return fid, runtime, feature_vector

def ParseLP(line):
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

    return fid, runtime, feature_vector

def ParseWcc(line):
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
    feature_vector.append(int(data_array[7]))

    return fid, runtime, feature_vector

def ParseSampling(line):
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
    feature_vector.append(int(data_array[7]))
    feature_vector.append(int(data_array[8]))
    feature_vector.append(int(data_array[9]))
    feature_vector.append(int(data_array[10]))

    return fid, runtime, feature_vector

def ParseWccHashmin(line, total_vertex_num, L):
    interval = math.ceil(total_vertex_num / L);
    message_embedding = [0] * (interval + 1)

    data_array = line.split(';')
    fid = int(data_array[0][4:])
    running_time = float(data_array[1]) * 1000
    ivnum = int(data_array[2])
    ovnum = int(data_array[3])
    tvnum = int(data_array[4])
    edge_num = int(data_array[5])
    received_msg_num = int(data_array[6])
    available_msg_num = int(data_array[7])
    active_vertex_num = int(data_array[8])
    updateOidOutputSize = int(data_array[9])

    if int(updateOidOutputSize) > 0:
        update_node = data_array[10]
        update_node_list = update_node.split(',')
        del update_node_list[len(update_node_list) - 1]
        for item in update_node_list:
            if item == '':
                continue
            belong_interval = math.floor(int(item) / L)
            if belong_interval > interval:
                continue
            # print(str(interval) + ", " + str(belong_interval)+ ", " + str(item))
            message_embedding[belong_interval] = message_embedding[belong_interval] + 1
    
    # construct feature vector
    feature_vector = []
    feature_vector.append(ivnum)
    feature_vector.append(ovnum)
    feature_vector.append(tvnum)
    feature_vector.append(edge_num)
    feature_vector.append(received_msg_num)
    feature_vector.append(available_msg_num)
    feature_vector.append(active_vertex_num)
    for item in message_embedding:
        feature_vector.append(item)

    return fid, running_time, feature_vector
    
def ParseSSSP(line, total_vertex_num, L):
    interval = math.ceil(total_vertex_num / L);
    message_embedding = [0] * (interval + 1)

    data_array = line.split(';')
    fid = int(data_array[0][4:])
    running_time = float(data_array[1]) * 1000
    ivnum = int(data_array[2])
    ovnum = int(data_array[3])
    tvnum = int(data_array[4])
    edge_num = int(data_array[5])
    received_msg_num = int(data_array[6])
    heap_size = int(data_array[7])
    available_msg_num = int(data_array[8])

    if int(available_msg_num) > 0:
        update_node = data_array[9]
        update_node_list = update_node.split(',')
        del update_node_list[len(update_node_list) - 1]
        for item in update_node_list:
            if item == '':
                continue
            belong_interval = math.floor(int(item) / L)
            if belong_interval > interval:
                continue
            # print(str(interval) + ", " + str(belong_interval)+ ", " + str(item))
            message_embedding[belong_interval] = message_embedding[belong_interval] + 1
    
    # construct feature vector
    feature_vector = []
    feature_vector.append(ivnum)
    feature_vector.append(ovnum)
    feature_vector.append(tvnum)
    feature_vector.append(edge_num)
    feature_vector.append(received_msg_num)
    feature_vector.append(heap_size)
    for item in message_embedding:
        feature_vector.append(item)

    return fid, running_time, feature_vector

def ParseBFS(line, total_vertex_num, L):
    interval = math.ceil(total_vertex_num / L);
    message_embedding = [0] * (interval + 1)

    data_array = line.split(';')
    fid = int(data_array[0][4:])
    running_time = float(data_array[1]) * 1000
    ivnum = int(data_array[2])
    ovnum = int(data_array[3])
    tvnum = int(data_array[4])
    edge_num = int(data_array[5])
    received_msg_num = int(data_array[6])
    heap_size = int(data_array[7])
    available_msg_num = int(data_array[8])

    if int(available_msg_num) > 0:
        update_node = data_array[9]
        update_node_list = update_node.split(',')
        del update_node_list[len(update_node_list) - 1]
        for item in update_node_list:
            if item == '':
                continue
            belong_interval = math.floor(int(item) / L)
            if belong_interval > interval:
                continue
            # print(str(interval) + ", " + str(belong_interval)+ ", " + str(item))
            message_embedding[belong_interval] = message_embedding[belong_interval] + 1
    
    # construct feature vector
    feature_vector = []
    feature_vector.append(ivnum)
    feature_vector.append(ovnum)
    feature_vector.append(tvnum)
    feature_vector.append(edge_num)
    feature_vector.append(received_msg_num)
    feature_vector.append(heap_size)
    for item in message_embedding:
        feature_vector.append(item)

    return fid, running_time, feature_vector

def ParseRoute(line, algo, total_vertex_num=None, L=None):
    if (algo == 'pagerankx'):
        return ParsePagerankx(line)
    elif (algo == 'sampling'):
        return ParseSampling(line)
    elif (algo == 'wcc'):
        return ParseWcc(line)
    elif (algo == "wcc-hashmin"):
        return ParseWccHashmin(line, total_vertex_num, L)
    elif (algo == "sssp"):
        return ParseSSSP(line, total_vertex_num, L)
    elif (algo == "lp"):
        return ParseLP(line)
    elif (algo == "bfs"):
        return ParseBFS(line, total_vertex_num, L)
    elif (algo == "hits"):
        return ParseHITS(line)
    else:
        raise NameError

""" moudle extern """
def GetAllData(extract_dir, fnum, algo, total_vertex_num=None, L=None):
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
                fid, label, features = ParseRoute(line, algo, total_vertex_num=total_vertex_num, L=L)
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
