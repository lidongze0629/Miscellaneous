// 快速排序，不稳定的排序
// 本意是每一趟排序都确定一个基准值的位置，理想的情况下，
// 这个基准值就是序列的中间位置，这样把这个序列一分为二，
// 就好比是一个树的结构，而树的深度正好是递归快排最大的
// 递归调用层次。
//
// 快排中，Partition函数很重要，主要理解好每次要先j--，
// 之后在i++，这样保证指针最终停的位置满足j的判断条件，
// 即，这个值小于基准值，这样i最终也会定位到这个位置，
// 因为，最开始我们选的是最左面的第一个作为基准值，这样
// 于基准值交换之后，保证了它在基准值的左侧且小于基准值，
// 否则的话（先i++）最终定位的位置可能大于基准值，交换到
// 最左侧是错误的。
//
// 时间复杂度：O(nlogn)
// 空间复杂度: O(logn) // 递归调用
//
// 快排依赖元素的初始化序列顺序，因为每次找一个基准，并
// 确定下来，基准找的好（意味着二分这个序列），时间就少，
// 否则，每次都找的是把头的基准，那么就是O(n^2)
//

#include <iostream>
#include <vector>

template <typename T>
using Vector = std::vector<T>;

int Partition(Vector<int>& vec, int left, int right) {
    size_t i = left, j = right;
    int temp = vec[i];

    while (i < j) {
        while (vec[j] >= temp && i < j) { j--; }
        while (vec[i] <= temp && i < j) { i++; }

        if (i < j) { std::swap(vec[i], vec[j]); }
    }

    std::swap(vec[left], vec[i]);
    return i;
}

void QuickSort(Vector<int>& vec, int left, int right) {
    if (left < right) {
        int benchmark = Partition(vec, left, right);
        QuickSort(vec, left, benchmark - 1);
        QuickSort(vec, benchmark + 1, right);
    }
}

void Test1() {
    Vector<int> input;
    input.push_back(42);
    input.push_back(55);
    input.push_back(12);
    input.push_back(44);
    input.push_back(94);
    input.push_back(6);
    input.push_back(18);
    input.push_back(68);

    std::cout << "input vector: " << std::endl;
    for(auto &iter : input) {
        std::cout << iter << ", ";
    }
    std::cout << std::endl;

    QuickSort(input, 0, input.size() - 1);  

    std::cout << "after sort, vector: " << std::endl;
    for(auto &iter : input) {
        std::cout << iter << ", ";
    }
    std::cout << std::endl;
    
}

int main() {
    Test1();
}
