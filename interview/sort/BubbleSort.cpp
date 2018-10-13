// 稳定的排序
// 对于冒泡排序，n个数的排序，必然需要n-1趟，因为每趟确定出
// 一个最大数或最小数，所以，这个就是外层循环 [0,n-1)
// 对于内层循环，就要看每次找到一个最小值还是最大值，
//      1）当每次要找一个最大值时，那么这个最大值要定位到数组的最末端，
//         因此j每次都要从0开始，[0,n-1-i)
//      2) 每次找最小值，这个最小值就要定位到数组的最开始，
//         因此j每次都从最后n-1开始，(i,n-1]
// 
// 时间复杂度：
//      比较次数: n(n-1)/2
//      交换次数: 3n(n-1)/2
// 空间复杂度: O(1)

#include <iostream>
#include <vector>

template <typename T>
using Vector = std::vector<T>;

// 第一种方式，每一次排序使得最小的数位于第一个
// 此时外层循环 i 就是每趟排序要确定的最小值。
// 算法的复杂度是n^2, 并且没有优化的地步。
// 比较次数 n(n-1)/2 移动次数 3n(n-1)/2
size_t BubbleSort_min(Vector<int>& vec) {
    size_t times = 0;
    bool flag = true;
    for (size_t i = 0; i < vec.size() - 1 && flag; ++i) {
        flag = false;
        for (size_t j = vec.size() - 1; j > i; --j) {
            times++;
            if (vec[j] < vec[j - 1]) {
                flag = true;
                std::swap(vec[j], vec[j - 1]);
            }
        }
    }
    return times;
}

// 第二种方式，每一次排序使得最大的数位于最后一个
// 此时外层循环 i 通过内存for循环的 j < vec.size() - i - 1
// 控制着每趟排序最大值
// 算法的复杂度也是n^2，但是有优化的地步
// 通过内部加一个flag可以大幅度缩减循环次数。
size_t BubbleSort_max(Vector<int>& vec) {
    size_t times = 0;
    bool flag = true;
    for (size_t i = 0; i < vec.size() - 1 && flag; i++) {
        flag = false;
        for (size_t j = 0; j < vec.size() - 1 - i; j++) {
            times++;
            if (vec[j] > vec[j + 1]) {
                flag = true;
                std::swap(vec[j], vec[j+1]);
            }
        }
    }
    return times;
}

void TestMin() {
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

    size_t times = BubbleSort_min(input);

    std::cout << "after " << times << " sort, vector: " << std::endl;
    for(auto &iter : input) {
        std::cout << iter << ", ";
    }
    std::cout << std::endl;
    
}

void TestMax() {
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

    size_t times = BubbleSort_max(input);

    std::cout << "after " << times << " sort, vector: " << std::endl;
    for(auto &iter : input) {
        std::cout << iter << ", ";
    }
    std::cout << std::endl;
    
}
int main() {
    std::cout << "------------------------------" << std::endl; 
    std::cout << "        min                   " << std::endl;
    std::cout << "------------------------------" << std::endl; 
    TestMin();

    std::cout << "------------------------------" << std::endl; 
    std::cout << "        max                   " << std::endl;
    std::cout << "------------------------------" << std::endl; 
    TestMax();
}
