#include <iostream>
#include <memory>

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include "train.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;

using grape::rpc::TrainService;

using grape::rpc::Feature;
using grape::rpc::PredictResult;
using grape::rpc::TrainResult;

class TrainClientImpl {
  public:
    TrainClientImpl(std::shared_ptr<Channel> channel) : stub_(TrainService::NewStub(channel)) {}

    void GetPredictResult() {
      Feature f;
      f.add_feature(1.0);
      f.add_feature(2.0);
      f.set_label(0.8272727);
      PredictResult pr;

      ClientContext context;
      Status status = stub_->GetPredictResult(&context, f, &pr);
      if (!status.ok()) {
        std::cout << "GetPredictResult rpc failed." << std::endl;
        return;
      }

      std::cout << "predict result is " << pr.predict_result() << std::endl;
      return;
    }

    void TrainData() {
      ClientContext context;
      TrainResult stats;
      const int number = 2;
      
      std::unique_ptr<ClientWriter<Feature>> writer(stub_->TrainData(&context, &stats));
      for (int i = 0; i < number; ++i) {
        Feature f;
        f.add_feature(1.0);
        f.add_feature(2.0);
        f.add_feature(3.0);
        f.set_label(0.3737);
        if (!writer->Write(f)) {
          break;
        }
      }
      writer->WritesDone();
      Status status = writer->Finish();
      if (status.ok()) {
        std::cout << "train over with return state is " << stats.trainstatus() << std::endl;
      } else {
        std::cout << "TrainDate rpc failed." << std::endl;
      }

    }

  private:
    std::unique_ptr<TrainService::Stub> stub_;
};

int main(int argc, char** argv) {
  TrainClientImpl client(grpc::CreateChannel("localhost:63800", grpc::InsecureChannelCredentials()));
  std::cout << "------------------ GetPredictResult ----------------" << std::endl;
  client.GetPredictResult();
  std::cout << "------------------ TrainData ----------------" << std::endl;
  client.TrainData();

  return 0;
}


