// 回溯法解决背包问题，回溯的思想就是深度优先搜索的过程
// 它找到的是问题的全部可行解
//
// 第一次进入BackTrack函数看似deep = 0 ，这是根结点，进入函数
// 后就要开始选择第一次分支了，在此问题中，只有0 | 1这两种选择，
// 因此没有对所有选择进行循环，只是一个if条件，划分了两个分支
// 否则的话，对于类似于货郎担这样的问题就要对每次不同的选择加一个
// 循环了。

#include <iostream>
#include <vector>

template <typename T>
using Vector = std::vector<T>;

Vector<double> weight = {1,2,3,4,5,6,7,8,9,10};
Vector<int> value = {1,4,5,25,14,8,15,14,14,10};
double pack_weight = 34;
int numbers = weight.size();

double current_weight = 0;
int current_value = 0;
int best_value = 0;

void BackTrack(int deep, Vector<int>& result) {
    // BackTrack 的递归截止条件
    if (deep >= numbers) {
        if (current_value > best_value) {
            std::cout << "find a feasible solution" << std::endl;
            best_value = current_value > best_value ? current_value : best_value;
            std::cout << "current best value: " << best_value << std::endl;
                for (auto &iter : result) {
                std::cout << iter << ", ";
            }
            std::cout << std::endl;
        }
        return;
    }

    // 这个就是约束条件, 也算是一个剪枝的过程
    // 如果加进来超重了，相当于之后的所有东西都不会加进来了
    if ((current_weight + weight[deep]) <= pack_weight) {
        // 意味着我们可以拿这个物品
        current_weight += weight[deep];
        current_value += value[deep];
        result[deep] = 1;
        // 此时我们已经拿完了这个物品接下来
        // 考虑拿下一个物品
        BackTrack(deep + 1, result);
        // 回溯回来了，要进入右分支，因此把之前
        // 左分枝的内容删除
        current_value -= value[deep];
        current_weight -= weight[deep];
    }

    // 这就是01背包的另一个分支，之所以没有else，是因为所有的
    // 结点都要走右分支。
    result[deep] = 0;
    BackTrack(deep + 1, result);
}

int main(int argc, char **argv) {
    Vector<int> result(numbers);
     /**
      * 进入回溯函数之前就相当于根结点，进去之后
      * 就要考虑拿与不拿进行分支，但是不论如何分支，
      * 分多少支，都在这一个函数内，不回递归调用自己，
      *如果递归调用就相当于进入下一层
      */
    BackTrack(0, result);
}
