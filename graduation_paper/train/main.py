from parse import parse_log
from metric import printErrorMetrics

import matplotlib.pyplot as plt
from sklearn.ensemble import RandomForestRegressor
import numpy as np

import sys, time, random

if __name__ == '__main__':
    if len(sys.argv) != 5:
        print("Usage: python3 main.py <log_path> <fnum> <total_vertex_num> <L>")
        sys.exit()

    log_path = sys.argv[1]
    fnum = int(sys.argv[2])
    total_vertex_num = int(sys.argv[3])
    L = int(sys.argv[4])
    
    print("--------------- user params -----------------")
    print("L: " + str(L))
    print("fnum: " + str(fnum))
    print("total_vertex_num:" + str(total_vertex_num))
    print("log_path: " + log_path)

    print("--------------- parse log -------------------")
    # which t means train, v means validate
    t_data, t_label, v_data, v_label = parse_log(fnum, log_path, total_vertex_num, L, "random", 0.99)
    
    print("-------- random forest model train ----------")
    t_results = []
    t_labels = []
    regr = RandomForestRegressor(n_estimators=100)
    for i in range(fnum):
        start = time.process_time()
        regr.fit(t_data[i], t_label[i]);
        end = time.process_time()
        print("----- fid-" + str(i) + ": train time is " + str(end-start))
        # print(regr.feature_importances_)
        result = regr.predict(v_data[i])
        # printErrorMetrics(result, v_label[i])
        for r in range(len(result)):
            t_results.append(result[r])
            t_labels.append(v_label[i][r])

    print("----------------- metrics --------------------")
    printErrorMetrics(t_results, t_labels)
    
    print("----------------- figure ---------------------")
    random_list = np.unique(np.random.randint(0, len(t_results), 50))
    figure_results = []
    figure_labels = []
    for i in random_list:
        figure_results.append(t_results[i])
        figure_labels.append(t_labels[i])

    predict_num = len(figure_results) + 1
    fig = plt.figure()
    plt.suptitle("wcc-hashmin usa-road predict result")
    plt.plot(list(range(1, predict_num)), figure_results, label='predict')
    plt.plot(list(range(1, predict_num)), figure_labels, label='real')
    plt.xlabel('number')
    plt.ylabel('running time (ms)')
    plt.legend()
    plt.show()
