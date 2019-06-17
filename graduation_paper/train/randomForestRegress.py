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
    running_time = float(data_array[1]) * 1000
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

def printError(result, labels):
    if len(result) != len(labels):
        print("size error when printError")
    error = []
    absError = []
    squaredError = []
    for i in range(len(labels)):
        print(str(result[i]) + " -> " + str(labels[i]))
        error.append(float(labels[i]) - float(result[i]))

    for val in error:
        squaredError.append(val * val)
        absError.append(abs(val))

    
    print("MSE = " + str(sum(squaredError) / len(squaredError)))
    print("MAE = " + str(sum(absError) / len(absError)))
    print("RMSE = " + str(math.sqrt(sum(squaredError) / len(squaredError))))


if __name__ == '__main__':

    fnum = sys.argv[1]
    total_vertex_number = sys.argv[2]
    L = sys.argv[3] # L for message embedding

    print("fragment number is " + str(fnum) + ", vextex_number is " + str(total_vertex_number) + ", L is " + str(L))

    # parse trian data
    print("-------------- begin parse train data ----------------")
    total_dataset = [None] * int(fnum)
    total_labels = [None] * int(fnum)
    train_dataset = [None] * int(fnum)
    train_labels = [None] * int(fnum)
    validate_dataset = [None] * int(fnum)
    validate_labels = [None] * int(fnum)

    logfile = open("wcc_hashmin_usa_road_bsp_64.out", "r");
    lines = logfile.readlines()
    for line in lines:
        if line.find('TrainLog') != -1:
            fid, running_time, feature_vector = parseLogData(line, total_vertex_number, L)
            if total_dataset[int(fid)] == None:
                total_dataset[int(fid)] = []
                total_labels[int(fid)] = []
            total_dataset[int(fid)].append(feature_vector)
            total_labels[int(fid)].append(running_time)
    logfile.close()

    for i in range(int(fnum)):
        train_num = math.ceil(len(total_dataset[i]) * 0.95)
        train_dataset[i] = total_dataset[i][0:train_num]
        train_labels[i] = total_labels[i][0:train_num]
        validate_dataset[i] = total_dataset[i][train_num:]
        validate_labels[i] = total_labels[i][train_num:]

    # random forest model train
    regr = RandomForestRegressor(n_estimators=100);
    for i in range(int(fnum)):
        start = time.process_time();
        regr.fit(train_dataset[i], train_labels[i])
        end = time.process_time();
        print("-----------------  fid-" + str(i) + "  -----------------")
        print("train time is " + str(end-start))
        print(regr.feature_importances_)
        result = regr.predict(validate_dataset[i])
        print(validate_dataset[i])
        print(validate_labels[i])
        printError(result, validate_labels[i])

    # print(regr.predict([['374804', '339', '375143', '920744', '339', '7', '326588', '7', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 1, 0, 0, 0, 0, 0, 0]]));
