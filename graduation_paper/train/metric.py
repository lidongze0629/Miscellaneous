import math

def printErrorMetrics(result, labels):
    if len(result) != len(labels):
        print("size error when printError")

    error = []
    relative_error = []

    absError = []
    squaredError = []
    relativeError = []

    for i in range(len(labels)):
        error.append(float(labels[i]) - float(result[i]))
        relative_error.append((float(labels[i]) - float(result[i])) / float(labels[i]))

    for val in error:
        squaredError.append(val * val)
        absError.append(abs(val))

    for val in relative_error:
        relativeError.append(val * val)

    print("MSE = " + str(sum(squaredError) / len(squaredError)))
    print("MAE = " + str(sum(absError) / len(absError)))
    print("RMSE = " + str(math.sqrt(sum(squaredError) / len(squaredError)))) 
    print("MSRE = " + str(sum(relativeError) / len(relativeError)))

