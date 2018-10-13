// 不稳定排序，但是如果是链表实现就是稳定的排序（还不知道什么原因）
// 对于选择排序，每一趟选出一个最小值或最大值，但是大部分时间只是比较
// 而真正交换的操作很少。
// 例如：当数组本身有序的时候，虽然我们还是比较了n(n-1)/2次，但是确交换了0次，
// 最差情况下，也是交换了3(n-1)次。因此这个排序适用于体积较大，但是排序码比较
// 简单的情况。

#include <iostream>
#include <vector>

template <typename T>
using Vector = std::vector<T>;

void SelectSort(Vector<int>& vec) {
    for (size_t i = 0; i < vec.size() - 1; ++i) {
        size_t k = i;
        for (size_t j = i + 1; j < vec.size(); ++j) {
            if (vec[j] <  vec[k]) {
                k = j;
            }
        }

        if (k != i) {
            std::swap(vec[i], vec[k]);
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

    SelectSort(input);

    std::cout << "after sort, vector: " << std::endl;
    for(auto &iter : input) {
        std::cout << iter << ", ";
    }
    std::cout << std::endl;
    
}


int main() {
    Test1();
}
