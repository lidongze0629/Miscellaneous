import numpy as np
import math, random

def parse_log(fnum, log_path, total_vertex_num, L, mode, proportion):
    total_datasets = [None] * fnum
    total_labels = [None] * fnum
    
    t_data = [None] * fnum
    t_label = [None] * fnum
    v_data = [None] * fnum
    v_label = [None] * fnum

    for i in range(fnum):
        v_data[i] = []
        v_label[i] = []

    log_file = open(log_path, 'r')
    lines = log_file.readlines()
    for line in lines:
        if line.find('TrainLog') != -1:
            fid, running_time, feature_vector = parse_log_data(line, total_vertex_num, L)
            if total_datasets[fid] == None:
                total_datasets[fid] = []
                total_labels[fid] = []
            total_datasets[fid].append(feature_vector)
            total_labels[fid].append(running_time)
    log_file.close()

    if mode == "random":
        for i in range(fnum):
            total_num = len(total_datasets[i])
            train_num = math.ceil(total_num * proportion)
            validate_num = total_num - train_num
            # print("fid-" + str(i) + " total number " + str(total_num) + " train number " + str(train_num) + "validate number " + str(validate_num))
            random_list = np.unique(np.random.randint(0, total_num, validate_num))
            random_list_reverse = random_list[::-1]
            for j in random_list_reverse:
                v_data[i].append(total_datasets[i][j])
                v_label[i].append(total_labels[i][j])
                del total_datasets[i][j]
                del total_labels[i][j]
            t_data[i] = total_datasets[i]
            t_label[i] = total_labels[i]
    return t_data, t_label, v_data, v_label

def parse_log_data(line, total_vertex_num, L):
    interval = math.ceil(total_vertex_num / L);
    message_embedding = [0] * interval
    
    data = line[line.find('TrainLog'):]
    data_array = data.split(';')
    fid = int(data_array[0][14:])
    running_time = float(data_array[1]) * 1000
    ivnum = int(data_array[2])
    ovnum = int(data_array[3])
    tvnum = int(data_array[4])
    edge_num = int(data_array[5])
    received_msg_num = int(data_array[6])
    available_msg_num = int(data_array[7])
    active_node_num = int(data_array[8])
    update_node_num = int(data_array[9])

    if int(update_node_num) > 0:
        update_node = data_array[10]
        update_node_list = update_node.split(',')
        del update_node_list[len(update_node_list) - 1]
        for item in update_node_list:
            belong_interval = math.floor(int(item) / L)
            if belong_interval > interval:
                continue
            # print(str(interval) + ", " + str(belong_interval)+ ", " + str(item))
            message_embedding[belong_interval] = message_embedding[belong_interval] + 1

    # construct feature vector
    feature_vector = []
    #feature_vector.append(ivnum)
    #feature_vector.append(ovnum)
    #feature_vector.append(tvnum)
    #feature_vector.append(edge_num)
    feature_vector.append(received_msg_num)
    feature_vector.append(available_msg_num)
    feature_vector.append(active_node_num)
    feature_vector.append(update_node_num)
    for item in message_embedding:
        feature_vector.append(item)

    return fid, running_time, feature_vector
