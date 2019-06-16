from sklearn.ensemble import RandomForestRegressor
from sklearn.datasets import make_regression

import sys, math, time

# usa_road vertex num is 23947348

def parseLogData(line, total_vertex_number, L):
    interval = math.ceil(int(total_vertex_number) / int(L))
    message_embedding = [0] * interval

    data = line[line.find('TrainLog'):]
    data_array = data.split(';')
    fid = data_array[0][14:]
    running_time = data_array[1]
    ivnum = data_array[2]
    ovnum = data_array[3]
    tvnum = data_array[4]
    edge_num = data_array[5]
    received_msg_num = data_array[6]
    available_msg_num = data_array[7]
    active_node_num = data_array[8]
    update_node_num = data_array[9]

    if int(update_node_num) > 0:
        update_node = data_array[10] 
        update_node_list = update_node.split(',')
        del update_node_list[len(update_node_list) - 1]
        for item in update_node_list:
            belong_interval = math.floor(int(item) / int(L))
            message_embedding[belong_interval] = message_embedding[belong_interval] + 1

    # construct feature vector
    feature_vector = []
    feature_vector.append(ivnum)
    feature_vector.append(ovnum)
    feature_vector.append(tvnum)
    feature_vector.append(edge_num)
    feature_vector.append(received_msg_num)
    feature_vector.append(available_msg_num)
    feature_vector.append(active_node_num)
    feature_vector.append(update_node_num)
    for item in message_embedding:
        feature_vector.append(item)

    return fid, running_time, feature_vector

if __name__ == '__main__':

    fnum = sys.argv[1]
    total_vertex_number = sys.argv[2]
    L = sys.argv[3] # L for message embedding

    print("fragment number is " + str(fnum) + ", vextex_number is " + str(total_vertex_number) + ", L is " + str(L))

    # parse trian data
    print("-------------- begin parse train data ----------------")
    train_datas = [None] * int(fnum)
    labels = [None] * int(fnum)

    logfile = open("wcc_hashmin_usa_road_bsp_64.out", "r");
    lines = logfile.readlines()
    for line in lines:
        if line.find('TrainLog') != -1:
            fid, running_time, feature_vector = parseLogData(line, total_vertex_number, L)
            if train_datas[int(fid)] == None:
                train_datas[int(fid)] = []
                labels[int(fid)] = []
            train_datas[int(fid)].append(feature_vector)
            labels[int(fid)].append(running_time)

    logfile.close()
    regr = RandomForestRegressor(n_estimators=100);
    start = time.process_time();
    regr.fit(train_datas[8], labels[8])
    end = time.process_time();
    print("train time is " + str(end - start))
    print(regr.feature_importances_)
    #print(regr.predict([['374804', '339', '375143', '920744', '339', '7', '326588', '7', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 1, 0, 0, 0, 0, 0, 0]]));
