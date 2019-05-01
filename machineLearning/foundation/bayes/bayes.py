import math
import numpy as np;

def createDataSet():
    dataSet = [['my', 'dog', 'has', 'flea', 'problems', 'help', 'please'],
               ['maybe', 'not', 'take', 'him', 'to', 'dog', 'park', 'stupid'],
               ['my', 'dalmation', 'is', 'so', 'cute', 'I', 'love', 'him'],
               ['stop', 'posting', 'stupid', 'worthless', 'garbage'],
               ['mr', 'licks', 'ate', 'my', 'steak', 'how', 'to', 'stop', 'him'],
               ['quit', 'buying', 'worthless', 'dog', 'food', 'stupid']]
    labels = [0, 1, 0, 1, 0, 1]
    return dataSet, labels

def createVocabList(dataSet):
    vocabSet = set([])
    for doc in dataSet:
        vocabSet = vocabSet | set(doc)
    return list(vocabSet)

def doc2Vec(doc, vocabList):
    vec = [0] * len(vocabList)
    for word in doc:
        if word in vocabList:
            vec[vocabList.index(word)] = 1
        else:
            print ("the word: %s is not in my vocabulary!" % word)
    return vec

def trainNB0(dataSetVec, labels):
    numDocs = len(dataSetVec)
    numWords = len(dataSetVec[0])
    pAbusive = sum(labels) / float(numDocs)
   
    p0Num = np.ones(numWords); p1Num = np.ones(numWords)
    p0Denom = 2.0; p1Denom = 2.0
    for i in range(numDocs):
        if labels[i] == 1:
            p1Num += dataSetVec[i]
            p1Denom += sum(dataSetVec[i])
        else:
            p0Num += dataSetVec[i]
            p0Denom += sum(dataSetVec[i])
    p1Vect = np.log(p1Num / p1Denom)
    p0Vect = np.log(p0Num / p0Denom)
    return p0Vect, p1Vect, pAbusive 

def classifyNB(vec2Classify, p0Vect, p1Vect, pClass):
    p1 = sum(vec2Classify * p1Vect) + np.log(pClass)
    p0 = sum(vec2Classify * p0Vect) + np.log(1.0 - pClass)
    if p1 > p0:
        return 1
    else:
        return 0

def main():
    dataSet, labels = createDataSet()
    vocabList = createVocabList(dataSet)
    #print(vocabList)
    #print("===================")
    dataSetVec = []
    for doc in dataSet:
        dataSetVec.append(doc2Vec(doc, vocabList))
    p0Vect, p1Vect, pAbusive = trainNB0(dataSetVec, labels)
    #print(p0Vect)
    #print("=================")
    #print(p1Vect)
    #print("=================")
    #print(pAbusive)
    Entry = ['stupid']
    thisDoc = np.array(doc2Vec(Entry, vocabList))
    print (Entry)
    print (" classify as ")
    print (classifyNB(thisDoc, p0Vect, p1Vect, pAbusive))

if __name__ == '__main__':
    main()
