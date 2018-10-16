#include <iostream>
#include <vector>

#define number 5
int graph[number][number] = {
    {0,1,1,1,0},
    {1,0,1,1,1},
    {1,1,0,1,0},
    {1,1,1,0,1},
    {0,1,0,1,0}
};

int result_number = 0;

bool ok(std::vector<int>& result, int deep) {
    for (int i = 0; i < number; i++) {
        if (graph[deep][i] && result[deep] == result[i]) {
            return false;
        }
    }
    return true;
}

void BackTrack(int deep, int color, std::vector<int>& result) {
    if (deep >= number) {
        std::cout << "find a feasible result:" << std::endl;
        result_number++;
        for (auto iter : result) {
            std::cout << iter << ", ";
        }
        std::cout << std::endl;
        return;
    }

    for (int i = 1; i <= color; i++) {
        result[deep] = i;
        if (ok(result, deep)) {
            BackTrack(deep + 1, color, result);
        }
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "./graphColor <number>" << std::endl;
        return 0;
    }

    int color_number = atoi(argv[1]);

    std::vector<int> result(number, 0);
    BackTrack(0, color_number, result); 
    std::cout << "Total result number: " << result_number << std::endl;
}
