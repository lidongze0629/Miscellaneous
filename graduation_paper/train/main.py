from parse import *
from metric import printErrorMetrics

import matplotlib.pyplot as plt
from sklearn.ensemble import RandomForestRegressor
import numpy as np

import sys, time, random

# usa_road 23947348 
# com-friendster 65608366
# livejournal 4847572

if __name__ == '__main__':
    if len(sys.argv) != 6:
        print("Usage: python3 main.py <algorithm> <log_path> <fnum> <total_vertex_num> <L>")
        sys.exit()
    
    algo = sys.argv[1]
    log_path = sys.argv[2]
    fnum = int(sys.argv[3])
    total_vertex_num = int(sys.argv[4])
    L = int(sys.argv[5])
    
    print("--------------- user params -----------------")
    print("L: " + str(L))
    print("fnum: " + str(fnum))
    print("total_vertex_num:" + str(total_vertex_num))
    print("log_path: " + log_path)

    print("--------------- parse log -------------------")
    # which t means train, v means validate
    if algo == "wcc_hashmin":
        t_data, t_label, v_data, v_label = parse_wcc_hashmin_log(fnum, log_path, total_vertex_num, L, "random", 0.98)
    elif algo == "pagerankx":
        t_data, t_label, v_data, v_label = parse_pagerankx_log(fnum, log_path, "random", 0.9)
    elif algo == "sssp":
        t_data, t_label, v_data, v_label = parse_sssp_log(fnum, log_path, total_vertex_num, L, "random", 0.9)
    elif algo == "sampling":
        t_data, t_label, v_data, v_label = parse_sampling_log(fnum, log_path, "random", 0.7)
    else:
        print("unsupport algo " + algo)
        sys.exit()

    print("-------- random forest model train ----------")
    t_results = []
    t_labels = []
    regr = RandomForestRegressor(n_estimators=100)
    for i in range(fnum):
        # print(str(i) + ", " + str(len(v_data[i])) + ", " + str(len(v_label[i])))
        start = time.process_time()
        regr.fit(t_data[i], t_label[i]);
        end = time.process_time()
        print("----- fid-" + str(i) + ": train time is " + str(end-start))
        print(regr.feature_importances_)
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

    if algo == "wcc_hashmin":
        plt.suptitle("wcc-hashmin usa-road predict result")
    elif algo == "pagerankx":
        plt.suptitle("pagerank dbpedia predict result")
    elif algo == "sssp":
        plt.suptitle("sssp com-friendster predict result")
    elif algo == "sampling":
        plt.suptitle("sampling livejournal predict presult")

    plt.plot(list(range(1, predict_num)), figure_results, label='predict')
    plt.plot(list(range(1, predict_num)), figure_labels, label='real')
    plt.xlabel('number')
    plt.ylabel('running time (ms)')
    plt.legend()
    plt.show()
