#include <iostream>
#include <thread>
#include <vector>

void CpuTest(int i) {
    while (true) {
        int j = i;
    }
}

int main(int argc, char **argv) {
    int numbers = atoi(argv[1]);
    std::vector<std::thread> threads(numbers);
    
    for (int i = 0; i < numbers; i++) {
        threads[i] = std::thread(CpuTest, i + 1);
    }

    for (auto &t : threads) {
        t.join();
    }

    return 0;

}
