// 总结回溯法：
// 如果一个实际的问题可以用回溯法来解，那么需要具备以下的一些条件：
// (1) 首先看看解空间是什么样的，解向量有事什么样的，比如01背包问题
//     输入是n个物品，输出是含有n个数的向量，向量的每个值代表这个物品
//     是否选取(1选 0不选), 解空间数也是一个二叉树。在比如货郎担问题，
//     输入也是n个城市，输出是一个含有n个城市的一个向量；同样n皇后问题
//     也是如此，因为每个皇后必然在单独的一行，因此输出也可以看作每个皇后
//     最终所在列的一个向量。
// (2) 在具备1的条件后，我们就可以从第一个分支开始分了，这就正式进入BackTrack的循环，
//     记住，只要在本函数体内（没有进入下一层递归调用），就相当于在一层进行选择，所以
//     要有一个while循环遍历所有的分枝数，其实就是当前结点的所有选择。之后针对每一个选择，
//     判断此选择是否可用，这就要求满足约束函数了（剪枝的过程）
// (3) 整个搜索过程就是一个深度递归遍历的过程，直到遍历数中的所有点，找到问题的所有可行解为止
//
// 一句话：一个问题能否用回溯法来解，一看解空间树和解向量如何表示，二看约束函数，缺一不可。

#include <iostream>
#include <vector>
#include <cmath>

int result_number = 0;


// 这个就是约束条件满足：
// (1) xi != xj
// (2) |xi - xj| != |i - j|
bool place(std::vector<int>& result, int deep) {
    for (int i = 0; i < deep; i++) {
        if ((result[deep] == result[i]) || 
                (std::abs(deep - i) == std::abs(result[deep] - result[i]))) {
            return false;
        }
    }
    return true;
}

void BackTrack(int deep, int number, std::vector<int>& result) {
    if (deep >= number) {
        result_number++;
        std::cout << "find a feasible result:" << std::endl;
        for (auto iter : result) {
            std::cout << iter << ", ";
        }
        std::cout << std::endl;
        return;
    }

    // 此处number本意是n皇后问题，但是n皇后所在的棋盘也是n维的
    // 就是扩展结点的时候有多少个分支，01背包问题就两分支，因此
    // 不需要这个循环，但是n皇后问题有n个分支，就要这个循环
    for (int i = 1; i<= number; i++) {
        // 每个皇后都从第一个位置开始放，看是否能放的下
        result[deep] = i;
        if (place(result, deep)) {
            // 说明这个位置目前放这个皇后没有问题
            // 就要递归调用放下一个皇后
            BackTrack(deep + 1, number, result);
        }
    }
}


int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "./n_queen <number>" << std::endl;
    }

    int queen_number = atoi(argv[1]);
    std::vector<int> result(queen_number, 0);
    BackTrack(0, queen_number, result);
    std::cout << "Total result number: " << result_number << std::endl;
}
