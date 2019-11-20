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
        if (float(labels[i]) != 0): 
            relative_error.append((float(labels[i]) - float(result[i])) / float(labels[i]))

    for val in error:
        squaredError.append(val * val)
        absError.append(abs(val))

    for val in relative_error:
        relativeError.append(val * val)

    MSE = sum(squaredError) / len(squaredError)
    MAE = sum(absError) / len(absError)
    RMSE = math.sqrt(sum(squaredError) / len(squaredError))
    MSRE = sum(relativeError) / len(relativeError)

    # print("MSE = ", MSE, ", MAE = ", MAE, ", RMSE = ", RMSE, ", MSRE = ", MSRE)

    # print("MSE = " + str(sum(squaredError) / len(squaredError)))
    # print("MAE = " + str(sum(absError) / len(absError)))
    # print("RMSE = " + str(math.sqrt(sum(squaredError) / len(squaredError)))) 
    # print("MSRE = " + str(sum(relativeError) / len(relativeError)))
    
    return MSE, MAE, RMSE, MSRE 

