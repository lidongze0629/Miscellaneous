具体内容如下：
1．getLogDemo文件夹：包含如何在GRAPE legacy系统中打印每一个线程运行时间的log的c++程序
2．log2vec文件夹：运行顺序为：先log2dataPAGERANK.m，后combine_all_data.m（相关文件路径需要更改）
该文件夹将打印出的log文本文件转化为特征向量，用于后续模型训练。
3．rdmForestTrain文件夹：包含模型训练代码和训练用特征向量。直接运行rdmForest_for_paper_exp.m即可
4．tianhe-log文件夹：我用getLogDemo中的log打印代码打印出的运行log
 
我觉得后续你可以打印出log后，写c++代码转换成特征向量，然后用c++上的随机森林回归模型进行训练，这样效率更高。我这个MATLAB版本只是为了测试预测模型是否可行，并不具有实用价值。
 
至于其他几种图算法，你可以仿照这个样例代码的思路打印log、转换为特征向量，然后训练。
