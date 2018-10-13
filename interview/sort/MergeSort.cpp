// 归并排序，稳定排序
// 分治思想，但重点不再分。而是合并。
// 合并的思路其实就是两个有序表的合并：
//      两个表的指针比较，小的放入新数组中，知道一个表空
//      如果另一个表不空，就把另一个都加如新数组中
//
// 时间复杂度： O(nlogn)
// 空间复杂度： O(n)
//
// 归并排序在有序的数组上面，由于大量的移动元素，导致比比较上
// 所花的时间多的多，因此可以在链表上进行归并排序

#include <iostream>
#include <memory>
#include <vector>

template <typename T>
using Vector = std::vector<T>;

void Merge(Vector<int>& vec, int left, int mid, int right) {
    Vector<int> result;
    
    int i = left, j = mid + 1;
    while (i <= mid && j <= right) {
        if (vec[i] <= vec[j]) { // 稳定排序的关键
            result.push_back(vec[i++]);
        } else {
            result.push_back(vec[j++]);
        }
    }

    while (i <= mid) { result.push_back(vec[i++]); }
    while (j <= right) { result.push_back(vec[j++]); }

    std::copy(result.begin(), result.end(), (vec.begin() + left));
}

void MergeSort(Vector<int>& vec, int left, int right) {
    if (left < right) {
        int mid = left + ((right - left) >> 1);
        MergeSort(vec, left, mid);
        MergeSort(vec, mid + 1, right);
        Merge(vec, left, mid, right);
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

    MergeSort(input, 0, input.size() - 1);

    std::cout << "after sort, vector: " << std::endl;
    for(auto &iter : input) {
        std::cout << iter << ", ";
    }
    std::cout << std::endl;
}

int main() {
    Test1();
}
