import math

def printErrorMetrics(result, labels):
    if len(result) != len(labels):
        print("size error when printError")

    error = []
    absError = []
    squaredError = []
    for i in range(len(labels)):
        error.append(float(labels[i]) - float(result[i]))

    for val in error:
        squaredError.append(val * val)
        absError.append(abs(val))

    print("MSE = " + str(sum(squaredError) / len(squaredError)))
    print("MAE = " + str(sum(absError) / len(absError)))
    print("RMSE = " + str(math.sqrt(sum(squaredError) / len(squaredError)))) 
