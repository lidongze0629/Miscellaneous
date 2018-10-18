#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

class Investment {
    public:
        Investment() : total_money_(0), project_number_(0) {}

        void Init(std::vector<std::vector<int>>& input, int total_money, int project_number) {
            project_number_ = project_number;
            total_money_ = total_money;
            project_benefit_table_ = input;

            // 初始化结果数组， +1 是为了不想用0 而已，直接明了
            final_benefit_.resize(project_number_ + 1);
            for (auto &each_project : final_benefit_) {
                each_project.resize(total_money_ + 1);
            }

            // 动态规划的程序的状态转移方程，从S0 -> S1 -> .... SN
            // 那么就要有边界条件，就是递推的终止条件
            // 此问题中的结束条件是将钱都投给第一个项目，根据
            // 输入的效益表，自然都是已知的
            // final_benefit_[1][i] 中的1代表第一个项目就是S0状态
            for (int i = 0; i < total_money_; i++) {
                final_benefit_[1][i] = project_benefit_table_[0][i];
            }

            std::string key = "11";
            flag_[key] = 1;
        }

        void Run() {
            DynamicPlanning();
            Output();
        }

        void Output() {
            std::cout << "The max benefit is: " << final_benefit_[project_number_][total_money_] << std::endl;
            int remain_money = total_money_;
            for (int project = project_number_; project >= 1; project--) {
                std::string key = std::to_string(project) + std::to_string(remain_money);
                std::cout << "project_" << project << " invest " << flag_[key] << std::endl;
                remain_money -= flag_[key];
            }
        }
    private:
        void DynamicPlanning() {
            // 状态S0 是初始状态，那么我们从S1开始，相当于钱都
            // 投给前两个项目
            for (int project = 2; project <= project_number_; project++) {
                // 对于每次投资，我们都有total_money_ 这个多钱，
                // 我们都要考虑到
                for (int current_investment_money = 1; current_investment_money <= total_money_; current_investment_money++) {
                    // 这对要投资的钱数，我们要分xk 为给第project的项目的钱，
                    // 剩下的current_investment_money - xk 就是分给之前的 project - 1 个项目的钱，
                    // 这样也就用上了动态规划的备忘录思想
                    for (int xk = 0; xk <= current_investment_money; xk++) {
                         if (final_benefit_[project - 1][current_investment_money - xk] + 
                                 project_benefit_table_[project - 1][xk] > final_benefit_[project][current_investment_money]) {
                            final_benefit_[project][current_investment_money] = 
                                final_benefit_[project - 1][current_investment_money - xk] + project_benefit_table_[project - 1][xk];
                            std::string key = std::to_string(project) + std::to_string(current_investment_money);
                            flag_[key] = xk;
                         } 
                    }
                }
            }    
        }

        int total_money_;  // 投资的总钱数
        int project_number_; // 项目个数
        // 每个项目不同投资额的效益表, 输入数据
        std::vector<std::vector<int>> project_benefit_table_;

        // 最终的收益
        // 最后的结果
        // 也是用于存放各个子问题的二维数组，减少重复计算
        std::vector<std::vector<int>> final_benefit_;
    
        // 用于最后回溯出来最有解的决策链，即决策过程
        std::map<std::string, int> flag_;
};

int main() {
    int money = 5; // 5万元
    int project_number = 4; // 4个项目
    std::vector<std::vector<int>> benefit_table = {
        {0, 11, 12, 13, 14, 15},
        {0, 0, 5, 10, 15, 20},
        {0, 2, 10, 30, 32, 40},
        {0, 20, 21, 22, 23, 24}
    };

    Investment invest;
    invest.Init(benefit_table, 5, 4);
    invest.Run();
}
