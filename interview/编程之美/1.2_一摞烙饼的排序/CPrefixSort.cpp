// 解析之前我们要明确一个事情，不只有分支限界法才可以使用bound进行剪枝
// 正常的回溯法也可以使用。
//
// 本题虽是一个不一样的排序问题，也很容易知道n个烙饼只需要2(n-1)次排序就
// 可以，但是既然是一个最优化问题，希望得到最小的翻转次数，那么自然就希望
// 有更优化的方案，因此，动态规划 递归回溯就可以达到这行的目的。
//
// 既然回溯找最优解（最小值），那么自然就需要一个upbound，每个扩展结点计算出来的
// 限界值比这个upbound大，就可以剪枝
//
// upperbound 和 lowerbound 是一起出现的，当需要找到问题的最大值时，自然每个结点
// 都计算他可能的最大值(记为上界)，去跟当前最好的结果(lowerbound)进行比较；同理，
// 当需要问题的最小值是，自然计算每个结点的可能的最小解，跟当前的最好结果(upperbound)
// 比较
//
// 这个问题的优化还可以从 当前结点的状态是否出现过入手，在加快剪枝
//
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>

template <typename T>
using Vector = std::vector<T>;

class CPrefixSort {
    public:
        CPrefixSort() : 
            cake_numbers_(0), deep_(0), best_value_(0), total_search_times_(0) {}

        void Init(Vector<int>& input_data) {
            cake_numbers_ = input_data.size();
            best_value_ = cake_numbers_ <= 1 ? 0 : 2 * (cake_numbers_ - 1); 

            original_data_.resize(cake_numbers_);
            result_.resize(best_value_ + 1);
            current_begin_to_reverse_data_.resize(cake_numbers_);
            current_result_.resize(best_value_ + 1);

            std::copy(input_data.begin(), input_data.end(), original_data_.begin());
            std::copy(original_data_.begin(), original_data_.end(), current_begin_to_reverse_data_.begin());
        }

        void run() {
            BackTrack(0);
            Output();
        }

        void Output() {
            std::cout << "best result: " << std::endl;
            for (size_t i = 0; i < best_value_; i++) {
                std::cout << result_[i] << ", ";
            }
            std::cout << std::endl;

            std::cout << "Total search times: " << total_search_times_ << std::endl;
            std::cout << "Best Swap times: " << best_value_ << std::endl;
        }

    private:
        bool isSort(Vector<int>& array_data) {
            for (size_t i = 0; i < array_data.size() - 1; i++) {
                if (array_data[i + 1] < array_data[i]) {
                    return false;   
                }
            }
            return true;
        }

        void BackTrack(size_t deep) {
            
            total_search_times_++;

            size_t nEstimate = LowerBound(current_begin_to_reverse_data_, cake_numbers_);
            if (deep + nEstimate > best_value_) {
                return;
            }

            if (isSort(current_begin_to_reverse_data_)) {
                if (deep < best_value_) {
                    std::cout << "find a better result: " << std::endl;
                    best_value_ = deep;
                    std::copy(current_result_.begin(), current_result_.end(), result_.begin());
                }
                return;
            }

            for (size_t i = 1; i < cake_numbers_; i++) {
                Reverse(0, i);
                current_result_[deep] = i; // 记录本次跟i这个位置交换，相当于记录结果
                BackTrack(deep + 1);
                Reverse(0, i);   
            }
        }

        size_t LowerBound(Vector<int>& array_data, size_t size) {
            size_t bound = 0;
            for (size_t i = 1; i < size; i++) {
                if (std::abs(array_data[i] - array_data[i - 1]) != 1) {
                    bound++;
                }
            }
            
            return bound;
        }

        void Reverse(size_t begin, size_t end) {
            assert(end > begin);
            
            size_t i = begin, j = end;
            while (i < j) {
                std::swap(current_begin_to_reverse_data_[i], current_begin_to_reverse_data_[j]);
                i++;
                j--;
            }
        }

        size_t cake_numbers_; // 烙饼的个数
        Vector<int> original_data_; // 原始数据

        Vector<int> result_; // 结果数组 例如[4，3，2], 代表第一个与后面的第四个翻转...
        Vector<int> current_begin_to_reverse_data_; // 将要翻转的数组
        Vector<int> current_result_; // 体现了翻转过程的数组，记录过程
        size_t deep_; // 当前搜索的深度
        size_t total_search_times_; // 总搜索次数
        size_t best_value_; // upperbound 就是目前可行解中的最小翻转次数，初始化为 2(n-1)
};

int main() {

    //Vector<int> input_data = {3,2,1,6,5,4,9,8,7,0};
    std::cout << "Please input original array, end with ctrl-d" << std::endl; 
    std::cout << "sample input: 3 2 1 6 5 4 9 8 7 0" << std::endl;
    
    Vector<int> input_data;
    int data;
    while (std::cin >> data) {
        input_data.push_back(data);
    }
    std::cout << "input data: " << std::endl;
    for (auto iter : input_data) {
        std::cout << iter << ", ";
    }  
    std::cout << std::endl;

    CPrefixSort cprefix_sort;
    cprefix_sort.Init(input_data);
    cprefix_sort.run();
}
