import os
import sys
import time

from metric import printErrorMetrics

import numpy as np
from sklearn.model_selection import KFold
from sklearn.linear_model import Ridge

def rr(datasets, labels, fnum):
    print('--- ridge regression ---')
    TMSE = 0; TMAE = 0; TRMSE = 0; TMSRE = 0
    sample_results = []
    sample_labels = []
    times = []
    predict_times = []
    sample_number = 0

    for i in range(fnum):
        """ set sample_number """
        sample_number = sample_number + len(datasets[i])
        """ change to numpy """
        datasets_np = np.array(datasets[i])
        labels_np = np.array(labels[i])
        """ KFold """
        index = 1
        MSE = 0; MAE = 0; RMSE = 0; MSRE = 0
        rlf = Ridge(alpha=1.0)
        kf = KFold(n_splits=10, shuffle=True, random_state=np.random.randint(0,100))

        for train_index, test_index in kf.split(datasets_np):
            # if index % 5 == 0:
            #     print("cross validate - ", str(index))
            x_train, x_test = datasets_np[train_index], datasets_np[test_index]
            y_train, y_test = labels_np[train_index], labels_np[test_index]
            start = time.process_time()
            rlf.fit(x_train, y_train)
            end = time.process_time()
            times.append(end - start)
            # print(regr.feature_importances_)
            predict_start = time.process_time()
            result = rlf.predict(x_test)
            predict_end = time.process_time()
            predict_times.append((predict_end - predict_start) / len(x_test))
            a, b, c, d = printErrorMetrics(result, y_test)
            sample_labels.extend(y_test)
            sample_results.extend(result)
            MSE = MSE + a
            MAE = MAE + b
            RMSE = RMSE + c
            MSRE = MSRE + d
            index = index + 1
    
        TMSE = TMSE + MSE / index
        TMAE = TMAE + MAE / index
        TRMSE = TRMSE + RMSE / index
        TMSRE = TMSRE + MSRE / index
        # print("MSE = ", MSE / index, ", MAE = ", MAE / index, ", RMSE = ", RMSE / index, ", MSRE = ", MSRE / index)
    print("MSE = ", TMSE / fnum, ", MAE = ", TMAE / fnum, ", RMSE = ", TRMSE / fnum, ", MSRE = ", TMSRE / fnum)
    print("train time is(avg) ", str(sum(times) / len(times)))
    print("predict time is(avg) ", str(sum(predict_times) / len(predict_times)))
    print("sample number is ", str(sample_number))
    return sample_results, sample_labels
