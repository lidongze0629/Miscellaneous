import numpy as np
import operator
import sys

def createDataSet():
    group = np.array([[1.0,1.1], [1.0,1.0], [0,0], [0,0.1]])
    labels = ['A', 'A', 'B', 'B']
    return group, labels

def classify0(inX, dataSet, labels, k):
    dataSetSize = dataSet.shape[0]
    diffMat = np.tile(inX, (dataSetSize, 1)) - dataSet
    sqDiffMat = diffMat**2
    sqDistances = sqDiffMat.sum(axis=1)
    distances = sqDistances**0.5
    # print(distances)
    sortedDistIndicies = distances.argsort()
    # print(sortedDistIndicies)
    classCount = {}
    for i in range(k):
        voteIlabel = labels[sortedDistIndicies[i]]
        classCount[voteIlabel] = classCount.get(voteIlabel, 0) + 1
    # print(classCount)
    sortedClassCount = sorted(classCount.items(), key = operator.itemgetter(1), reverse = True)
    # print (sortedClassCount)
    return sortedClassCount[0][0]

if __name__ == '__main__':
    group, labels = createDataSet()
    
    print(classify0([0.5,0.7], group, labels, 2))
