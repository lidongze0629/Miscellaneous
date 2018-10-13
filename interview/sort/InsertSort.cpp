// 稳定排序，但是前提是排序码的判断符号是'<',而不是'<='
// 直接插入排序
// 时间复杂度：
//      1） 比较次数: n(n-1)/2
//          交换次数: (n+4)(n-1)/2 = n^2/2
// 空间复杂度：O(1)
// 最好的情况下，比较了n-1次，交换0次，所以插入排序与原始带排数组的
// 序列密切相关，这也造成了希尔排序算法块的的一个原因。
//

#include <iostream>
#include <vector>

template <typename T>
using Vector = std::vector<T>;

void InsertSort(Vector<int>& vec) {
    for (size_t i = 1; i < vec.size(); i++) {
        int temp;
        if (vec[i] < vec[i - 1]) {
            temp = vec[i];

            int j;
            for (j = i - 1;j >= 0 && vec[j] > temp; j--) {
                vec[j + 1] = vec[j];
            }
            vec[j + 1] = temp;
        }
    }
}

// 对于二分插入排序，有以下几点需要注意的地方
//  1) 主要用到二分查找，首先就要考虑end的值是n还是n-1 ，
//     本题既然是n-1，也就是说这个end是一个确切的数，而不是
//     所谓的尾后数。因此while循环就是 begin <= end
//  2) 第二处就是二分查找如果mid和查找的值相等就要返回，但此处
//     我们是要找到一个空的位置，因此这个相等理论上来说可以放到>=,
//     也可以是<=，但是既然我们要稳定排序，因此智能放到mid+1 这一块
//  3) 最后，找到位置就是begin 
//
//  二分插入排序，交换的次数没有减少，但是比较的次数减少了，因为采用了
//  二分查找，变成了O(nlogn);
void BinaryInsertSort(Vector<int>& vec) {
    for (size_t i = 1; i < vec.size(); i++) {
        int temp;
        if (vec[i] < vec[i - 1]) {
            temp = vec[i];
            // 二分查找到需要插入的位置
            int begin = 0, end = i - 1;
            while (begin <= end) { // 这块也需要调节，begin < end
                int mid = begin + ((end - begin) >> 1);
                if (vec[mid] > temp) {
                    end = mid - 1; // 这块要注意调节，如果end = i, 则为 end = mid;
                } else {
                    begin = mid + 1;
                }
            }
            
            int j;
            for (j = i - 1; j >= begin; j--) {
                vec[j + 1] = vec[j];
            }

            vec[j + 1] = temp;
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

    InsertSort(input);

    std::cout << "after sort, vector: " << std::endl;
    for(auto &iter : input) {
        std::cout << iter << ", ";
    }
    std::cout << std::endl;
}

void Test2() {
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

    BinaryInsertSort(input);

    std::cout << "after sort, vector: " << std::endl;
    for(auto &iter : input) {
        std::cout << iter << ", ";
    }
    std::cout << std::endl;
}
int main() {
    Test1();
    std::cout << "---------------------------" << std::endl;
    Test2();
}
