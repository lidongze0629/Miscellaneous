// 划分过程:
//      要求长度为m和长度为n的序列的公共子序列长度, 每个过程就是求
//   长度小于m, 和n的任何一个序列的公共子序列长度.
// 状态变量:
//      m[i][j] 的大小,即当前的长度就是状态变量, i代表序列a的第i个位置, j代表b的第j个位置
// 初始状态: 
//      m[i][0] ,m[0][j] 都是0, 这也是递归的终止条件
//  状态转移方程:
//      m[i][j] =  
//                  0                              (i = 0 || j = 0)
//                  max{ m[i-1][j]} , m[i][j-1] }  (0 < i,j    list1[i] != list2[j])
//                  m[i-1][j-1] + 1                (0 < i,j    list1[i] == list2[j])

#include <iostream>
#include <stack>
#include <vector>

class LCS {
    public:

        LCS() : a_size_(0), b_size_(0) {}

        void Init(std::vector<int>& list_a, std::vector<int>& list_b) {
            a_size_ = list_a.size();
            b_size_ = list_b.size();

            list_a_.resize(a_size_);
            list_b_.resize(b_size_);

            std::copy(list_a.begin(), list_a.end(), list_a_.begin());
            std::copy(list_b.begin(), list_b.end(), list_b_.begin());

            result_.resize(a_size_ + 1);
            for (auto &iter : result_) {
                iter.resize(b_size_ + 1);
            }

            path_.resize(a_size_ + 1);
            for (auto &iter : path_) {
                iter.resize(b_size_ + 1);
            }
        }

        void Run() {
            // 初始化边界条件,就是终止边界
            for (size_t i = 0; i <= a_size_; i++) {
                result_[i][0] = 0;
            }

            for (size_t j = 0; j <= b_size_; j++) {
                result_[0][j] = 0;
            }

            DynamicPlanning();
            Output();
        } 

        void Output() {
            std::stack<int> res_stack;
            std::cout << "longest substr size is: " << result_[a_size_][b_size_] << std::endl;
            

            int a = a_size_, b = b_size_;
            //std::cout << path_[8][8] <<  std::endl;
            while (a > 0 && b > 0) {
                int flag = path_[a][b];
                switch(flag) {
                    case 1:
                        res_stack.push(list_a_[a - 1]);
                        a -= 1;
                        b -= 1;
                        break;
                    case 2:
                        a -= 1;
                        break;
                    case 3:
                        b -= 1;
                        break;
                }
            }

            while (!res_stack.empty()) {
                std::cout << res_stack.top() << ", ";
                res_stack.pop();
            }

            std::cout << std::endl;
        }

    private:
        void DynamicPlanning() {
            // 1 左上方向来的
            // 2 上方向来的
            // 3 左方向来的

            for (size_t i = 1; i <= a_size_; i++) {
                for (size_t j = 1; j <= b_size_; j++) {
                    if (list_a_[i - 1] == list_b_[j - 1]) {
                        result_[i][j] = result_[i - 1][j - 1] + 1;
                        path_[i][j] = 1;
                    } else if (result_[i - 1][j] >= result_[i][j - 1]) {
                        // 相当于从上面下来
                        result_[i][j] = result_[i - 1][j];
                        path_[i][j] = 2;
                    } else {
                        // 相当与从左边来
                        result_[i][j] = result_[i][j - 1];
                        path_[i][j] = 3;
                    }
                }
            }
        }

        // 输入的两个子序列
        size_t a_size_;
        size_t b_size_;
        std::vector<int> list_a_;
        std::vector<int> list_b_;

        // 记录最长子序列的长度
        std::vector<std::vector<int>> result_;
        // 追溯路径
        std::vector<std::vector<int>> path_;
};

int main() {
    std::vector<int> list_a = {1,3,4,5,6,7,7,8};
    std::vector<int> list_b = {3,5,7,4,8,6,7,8,2};

    LCS lcs;
    lcs.Init(list_a, list_b);
    lcs.Run();
}
