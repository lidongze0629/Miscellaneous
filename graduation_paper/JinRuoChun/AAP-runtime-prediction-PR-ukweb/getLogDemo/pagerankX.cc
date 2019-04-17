#include <algorithm>
#include <fstream>

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <string>

#include <thread>
#include <chrono>

using namespace std;
using namespace chrono;

#include "include/grape.h"
#include "include/util.h"
#include "app/pagerank/pagerankX_context.h"


using namespace std;
using namespace folly;

DEFINE_double(delta, 0.85, "delta");
DEFINE_double(threshold, 0.0001, "wheather convergence");
DEFINE_int32(straggler, 30, "straggler"); // the id of straggler
DEFINE_int32(step, 0, "step");
DEFINE_int32(xx, 10000000, "xx");
DEFINE_int32(wen, 0, "wen");

int sstep;

class PRWorker : public Worker {
  void PEval(Fragment &fragment, MessageBuffer &messages,
             ResultType &partial_result, shared_ptr<UDContainer> &context) {
    if(fragment.Fid() == 11)
      sstep = 0;
    int tvnum = fragment.TotalVerticesNum();
    int ivnum = fragment.InnerVerticesNum();
    partial_result.resize(ivnum + 1, 0.0);
    context = shared_ptr<UDContainer>(new PRContext);
    auto &delta = dynamic_pointer_cast<PRContext>(context)->delta;
    delta.resize(tvnum, 0.0);
    auto &pr = partial_result;
    int inner = 0;
    int outer = 0;
    double begin = get_current_time();
    double tmp = 0.0;
    for(unsigned u = 0; u < ivnum; u++) {
        delta[u] += (1 - FLAGS_delta);	
        pr[u] += delta[u];
	tmp = delta[u];
        ESlice es = fragment.GetOEdges(u);
        int OEdgesNum = es.end() - es.begin();
        if (OEdgesNum > 0) {
            auto update = FLAGS_delta * delta[u] / OEdgesNum;
	    for (auto &oe : es){
                  if(oe.id() < ivnum)
                    inner++;
                  else
                    outer++;
		  delta[oe.id()] += update;
            }
        }
        delta[u] -= tmp;
    }
    double end = get_current_time();
    double time1 = end - begin;
    if (fragment.Fid() == 14 || fragment.Fid() == 17 || fragment.Fid() == 21){
    //if(fragment.Fid() == FLAGS_straggler) {
      std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000*time1)));
     //for(int i = 0;i < FLAGS_step;i++)
      std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000*time1)));
      std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000*time1)));
      std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000*time1)));
    }
    for (int u = ivnum; u < tvnum; u++) {
            unsigned gid = fragment.OuterVertexLid2Gid(u);
            SyncStateOnOuterVertex(fragment, gid, PairMessage(gid, delta[u]));
	    delta[u] = 0;
    }
 //   LOG(WARNING) << "eta\t"<< this->LowerBound()<< " Fragment " << fragment.Fid() <<" #nodes\t" <<fragment.InnerVerticesNum() << " #inneredge\t"
   //              << inner << " #outeredge\t" << outer <<"\tPTime\t" << time1 << std::endl;
 }

  void IncEval(Fragment &fragment, MessageBuffer &messages, 
               ResultType &partial_result, shared_ptr<UDContainer> &context) {
	chrono::time_point<std::chrono::system_clock> start, end;
	start = chrono::system_clock::now();
	int frag_id = fragment.Fid();
//	VLOG(2) << "[worker_" << GetWorkerId() << "] fid: "<<frag_id << ", IE start" << std::endl;
    if(fragment.Fid() == 11)
      sstep++;
    double begin1 = get_current_time();
	
	int ovnum = fragment.TotalVerticesNum() - fragment.InnerVerticesNum();
	int total_v_num = fragment.TotalVerticesNum();
	int innner_v_num = fragment.InnerVerticesNum();
    int tvnum = fragment.TotalVerticesNum();
    int ivnum = fragment.InnerVerticesNum();
	unsigned frag_enum = 0;
    auto &delta = dynamic_pointer_cast<PRContext>(context)->delta;
    auto &pr = partial_result;
    pr[ivnum] += 1.0;
    double update_sum = 0;
    for (auto &slice : messages.GetMessages()) {
        for (auto &item : slice) {
            unsigned u = fragment.InnerVertexGid2Lid(item.id());
            double tmp = item.value();
            delta[u] += tmp;
        }
    }
    double tmp = 0;
    for (unsigned u = 0; u < ivnum; u++) {
	    tmp = delta[u];
            pr[u] += tmp;
            ESlice es = fragment.GetOEdges(u);
            int OEdgesNum = es.end() - es.begin();
			frag_enum = frag_enum + OEdgesNum;
	    if (OEdgesNum > 0) {
            	auto update = FLAGS_delta * delta[u] / OEdgesNum;
		for (auto &oe : es){
		     delta[oe.id()] += update;
		     update_sum += update;
		}
	    }
	    delta[u] -= tmp;
    }

	double end1 = get_current_time();
    double time1 = end1 - begin1;
    if (fragment.Fid() == 14 || fragment.Fid() == 17 || fragment.Fid() == 21) {
    //if(fragment.Fid() == FLAGS_straggler) {
//      for(int i = 0;i < FLAGS_step;i++)
      std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000*time1)));
      std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000*time1)));
      std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000*time1)));
      std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000*time1)));
    }
 
    if (update_sum >= FLAGS_threshold * tvnum) {
        for (int u = ivnum; u < tvnum; u++) {
            unsigned gid = fragment.OuterVertexLid2Gid(u);
            SyncStateOnOuterVertex(fragment, gid, PairMessage(gid, delta[u]));
	    delta[u] = 0;
        }
    }
	//double end = get_current_time();
   // double time1 = end - begin;
	end = chrono::system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	//VLOG(2) << "[worker_" << GetWorkerId() << "] fid: "<<frag_id<<", " << ivnum<<","<< tvnum<<","<<frag_enum<< std::endl;
	//VLOG(2) << "[worker_" << GetWorkerId() << "] fid: "<<frag_id <<", IE end" << std::endl;
	VLOG(1) << double(duration.count()) * microseconds::period::num / microseconds::period::den << ";" << total_v_num <<";"<<innner_v_num<<";"<<ovnum<<";"<<fragment.Fid()<<";"<< frag_enum << endl;

  }

  double Attl(Fragment &fragment, int un, int rmin) {
    if(fragment.Fid() == 11 && sstep >= FLAGS_xx) {
    //  LOG(INFO) << fragment.Fid() << "\t" << sstep <<  " delay" <<std::endl;
      return 20.0 * (this->LowerBound() > 1);
    }
    if (un >= this->LowerBound() || rmin < FLAGS_wen) {
    //  LOG(INFO) << fragment.Fid() << "\t" << rmin << "\t" << un << "\t" << this->LowerBound() << "  asp" <<std::endl;
      return 0.0;
    }
    else
      return this->TTL();
  }
  
  void PreparePartialResult(Fragment &fragment, ResultType &partial_result) {
    auto &pr = partial_result;
    char buf[128];
    sprintf(buf, "query%d.%d.frag%d", this->query().root(),
            this->query().lower_bound(), fragment.Fid());
    string path = buf;
    double sum = 0;
    if (this->result_file() != "") {
      path = this->result_file() + "/" + path;
      std::ofstream fout;
      fout.open(path);
      unsigned ivn = fragment.InnerVerticesNum();
      for (unsigned u = 0; u < ivn; u++) {
        unsigned oid = fragment.Lid2Oid(u);
        fout << oid << "\t" << pr[u] << endl;
        sum += pr[u];
      }
      //fout << sum << endl;
  //    LOG(WARNING) << "eta "<< this->LowerBound()<< " Fid "<< fragment.Fid() << "\t" << "sum\t" << sum << std::endl;
      fout.close();
    }
   // LOG(WARNING) << "eta "<< this->LowerBound()<< " Fid " <<fragment.Fid() << "\t" <<"#internation\t" << pr[fragment.InnerVerticesNum()] << std::endl;
  }
  
  void Assemble(vector<vector<ResultType>> &partial_results) {}
};


int main(int argc, char *argv[]) {
  FLAGS_stderrthreshold = 0;
  google::SetUsageMessage(
      "Usage: mpiexec.hydra [mpi_opts] ./pagerank [grape_opts]");
  google::ParseCommandLineFlags(&argc, &argv, true);
  WorkersInit();

  Params param;
  param.algorithm = "pagerank";
  param.enable_assemble = true;
  param.load_strategy = kOnlyOut;
  param.message_strategy = kSyncStateOnOuterVertexAsTarget;
  param.use_pattern = false;
  // params for stream_partiton
  // param.partition_strategy = kLinearDeterministicGreedy;
  // param.max_frag_size = 30000;

  google::ShutDownCommandLineFlags();

  PRWorker prWorker;

  google::InitGoogleLogging("pagerank");
  google::InstallFailureSignalHandler();
  prWorker.Run(param);
  google::ShutdownGoogleLogging();

  WorkerFinalize();
  return 0;
}

