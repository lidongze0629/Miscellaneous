#include <iostream>

#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/security/server_credentials.h>

#include "train.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;

using grape::rpc::TrainService;

using grape::rpc::Feature;
using grape::rpc::PredictResult;
using grape::rpc::TrainResult;

class TrainServerImpl final : public TrainService::Service {
  Status GetPredictResult(ServerContext* context, const Feature* request, PredictResult* response) {
    std::cout << "feature: "<< std::endl;
    for (int i = 0; i < request->feature_size(); ++i) {
      std::cout << request->feature(i) << ", ";
    }
    std::cout << std::endl;
    response->set_predict_result(0.183);
    return Status::OK;
  }

  Status TrainData(ServerContext* context, ServerReader<Feature>* reader, TrainResult* response) {
    Feature feature;
    while (reader->Read(&feature)) {
      std::cout << "feature: "<< std::endl;
      for (int i = 0; i < feature.feature_size(); ++i) {
        std::cout << feature.feature(i) << ", ";
      }
      std::cout << std::endl; 
    }
    response->set_trainstatus(true);
    return Status::OK;
  }
};

void RunServer() {
  std::string server_address("0.0.0.0:63800");
  TrainServerImpl service;

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
}

int main(int argc, char **argv) {
  RunServer();
  return 0;
}
