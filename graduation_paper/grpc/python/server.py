import grpc

from concurrent import futures
import time
import math
import logging

import train_pb2
import train_pb2_grpc

_ONE_DAY_IN_SECONDS = 60 * 60 * 24

class TrainServiceImpl(train_pb2_grpc.TrainServiceServicer):
    def __init__(self, fnum):
        self.fnum = fnum
    def GetPredictResult(self, request, context):
        print("-------------- GetPredictResult --------------")
        print("feature: " + str(request.feature))
        print("feature_str: " + str(request.feature_str))
        print("label: " + str(request.label))
        return train_pb2.PredictResult(predict_result = 0.1919)
    def TrainData(self, request_iterator, context):
        print("------------- Train Data ---------------------")
        for f in request_iterator:
            print("feature: " + str(f.feature))
            print("label: " + str(f.label))
        return train_pb2.TrainResult(TrainStatus=True)

def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    train_pb2_grpc.add_TrainServiceServicer_to_server(
            TrainServiceImpl(64), server)
    server.add_insecure_port('[::]:63800')
    server.start()
    try:
        while True:
            time.sleep(_ONE_DAY_IN_SECONDS)
    except KeyboardInterrupt:
        server.stop(0)

if __name__ == '__main__':
    logging.basicConfig()
    serve()
