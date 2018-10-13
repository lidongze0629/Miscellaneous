// 希尔排序，一种不稳定排序
// 最重要的地方是希尔增量(gap)的选择，本例子中是n/2
// 但是，这个不是最好的，因为基数要想和偶数比较只有gap等于1的时候
// 因此只是作为一个范例，目前最好的希尔增量是  下限（(gqp/3)）+ 1
//
// 希尔排序的思想初始化一个gap(size/2),意味着分为gap组，那么每组都是2个(或三个)
// 之后组内直接插入排序，之后gap = gap ／2
// 
// 代码中用一层for循环模拟不同组就可以

#include <iostream>
#include <vector>

template <typename T>
using Vector = std::vector<T>;

void ShellSort(Vector<int>& vec) {
    int gap = vec.size() / 2;
    // 希尔增量选取的是n/2 那么每组的元素个数就是
    // 2，4，8，16.....
    for (; gap >= 1; gap /= 2) {
        for (int i = gap; i < vec.size(); i++) {
            // 这里开始针对每一个i，往前面i-gap,i-gap-gap... 
            // 执行插入排序
            int j = i;
            int temp;

            if (vec[j] < vec[j - gap]) {
                temp = vec[j];

                for (;temp < vec[j - gap] && (j - gap) >= 0; j -= gap) {
                    vec[j] = vec[j - gap];
                }

                vec[j] = temp;
            }
        }
    }
}

void Test1() {
    Vector<int> input;
    for (unsigned i = 1; i < 11; ++i) {
        input.push_back(i);
    }

    for (unsigned i = 15; i > 10; --i) {
        input.push_back(i);
    }

    std::cout << "input vector: " << std::endl;
    for(auto &iter : input) {
        std::cout << iter << ", ";
    }
    std::cout << std::endl;

    ShellSort(input);

    std::cout << "after sort, vector: " << std::endl;
    for(auto &iter : input) {
        std::cout << iter << ", ";
    }
    std::cout << std::endl;
}


int main() {
    Test1();
}
