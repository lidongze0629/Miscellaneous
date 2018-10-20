// 这个题要想用动态规划的方式来解，也得从所有的条件进行分析。
// 给定包含n个元素的序列 a0, a1, a2...., an-1
// 1) 首先是划分阶段，这块就是难点，如果我们用A[i], 表示从a0到ai的最长子序列和
//    我们知道这个最长子序列求出的结果不一定以a[i]结尾(比如a[i]是负数),
//    所以，我们要想用a[i]来底推出a[j](j>i) 是不符合题意的，因此我们要改变思路
//    如果用暴力解法，分别以a0, a1 ... an-1开始，求的以他们开头的所有子序列和，
//    最终取最大的就是最后的解，比如此序列我们求出:
//    a0, a0a1, a0a2, a0a3, ..... a0an-1
//    a1, a1a2, a1a3, a1a4, ..... a1an-1
//    ....
//    an-2, an-2an-1
//    an-1
//    其中就包含了所有的子序列，我们取最大的就是结果，我们可以看出要想求出以a0开始
//    的所有子序列和，只要求出a1开始的，在确定是否加上a0这个元素就可以了，这就是阶段
//    的划分，它保证了a[i+1] 是从 a[i]来的，并且符合题意
// 2) 状态变量
//    s0 是初始状态，代表着a0 取 max{0, a0}
//    s1 ... sn-1 是每个阶段的状态，代表着分别以他们为结束的序列的最大和
//    因此状态转移方程就是 s[j] = max{s[j-1] + a[j], a[j]},解释一下就是
//    s[j]相对于s[j-1]而言，取决与我们是否把a[j]加进去，因为我们的约定是必须
//    以a[j]结尾，所以只需要考虑是a[j] 还是 s[j-1] + a[j] 这就取决于s[j-1] 是否大于0了
//
// 3) 最优子结构判断，如果s[j] 是最优的，那么s[j-1]就是最优的，否则我们就拿另一个最优的，
//    加上a[j]不就得到了更优的嘛


#include <iostream>
#include <algorithm>
#include <vector>

class MaxSum {
    public:
        MaxSum() : size_(0) {}

        void Init(std::vector<int>& input) {
            size_ = input.size();
            original_data_.resize(size_);
            result_.resize(size_);

            std::copy(input.begin(), input.end(), original_data_.begin());
        }

        void Run() {
            // 将result_[0] 设置成 max{0, original_data_[0]}
            result_[0] = std::max(0, original_data_[0]);

            DynamicPlanning();
            Output();
        }

        void Output() {
            // 从result_[0] 到 result_[n-1] 中选取一个最大的
            int max = 0;
            int begin_position = -1;
            int end_position = -1;
            for (size_t i = 0; i < size_; i++) {
                if (result_[i] >= max) {
                    max = result_[i];
                    end_position = i;
                }
            }
            
            // 求初始位置
            int last = max;
            for (int i = end_position; i >= 0; i--) {
                last -= original_data_[i];
                if (last == 0) {
                    begin_position = i;
                    break;
                }
            }

            std::cout << "the max sum is " << max << std::endl;
            std::cout << "begin position is " << begin_position << ", end position is " << end_position << std::endl;
            std::cout << "max sub list is " << std::endl;
            for (int i = begin_position; i <= end_position; i++) {
                std::cout << original_data_[i] << ", ";
            }
            std::cout << std::endl;
        }


    private:
        void DynamicPlanning() {
            for (size_t i = 1; i < size_; i++) {
                result_[i] = std::max(result_[i - 1] + original_data_[i], original_data_[i]);
            }
        }

        std::vector<int> original_data_;
        size_t size_;  

        std::vector<int> result_;
};

int main() {
    std::vector<int> input = {2,-5,8,11,-3,4,6};
    std::cout << "input array: " << std::endl;
    for (auto &iter : input) {
        std::cout << iter << ", ";
    }
    std::cout << std::endl;

    MaxSum maxsum;
    maxsum.Init(input);
    maxsum.Run();
}
