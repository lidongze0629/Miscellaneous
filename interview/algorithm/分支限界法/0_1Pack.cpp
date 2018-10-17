// 分支限界法总结：
// 分支限界法的思想是为了在回溯法的基础上尽快发生剪枝，以达到加快搜索的目的，
// 因此为了尽快剪枝，就要增加约束条件，从而引入了新的函数：
//      (1) 代价函数:`upbound`或`lowerbound`. 当问题需要得到一个最大解的时候，比如01背包
//          问题得到的max value，那我们对每一个结点计算它的upbound(意思是，以这个结点为
//          数的所有结点的最大期望值),如果这个最大期望值比我们目前得到的可行解中最好的还要差，
//          就说明以这个结点为树的分支都不用考虑了，直接剪。那lowerbound体现在何处呢，就是目前
//          我们得到可行解中最好的就设为lowerbound，因此初始化为0（min），所以我们可以看出，找到
//          第一个可行解前仍是盲目搜索，改进的办法就是找到一个可能性，哪怕这个解不好(但总比初始化为0好)
//          ，比如可以使用贪心思想先贪出一个解来。
// 除此之外，一个问题要想用分支限界法解答，
//  1）首先要看这个问题是否可以用回溯的思想解答，毕竟是回溯的改进
//  2）其次，我们既然要使用优先队列，就要找到优先队列的排序依据(也就是下一次扩展结点的方向，即搜索的方向)，
//     这个依据就可以用代价函数来使用，比如01背包问题的依据就是这个结点使劲装能装多少，再不路径问题，就可以
//     用这个结点到目的结点的单元最短路径来恒量。
//  3) 最后我们就可以根据广度遍历，找到拓展结点的所有孩子，满足约束条件的和限界函数的就加入到队列中，自然就
//     会扩展到他们，只是相对于深度搜索，结果的记录不是那么方面，这一点需要而外的空间指引。
//

#include <iostream>
#include <queue>
#include <vector>

template <typename T>
using Vector = std::vector<T>;

struct Node {
    double current_weight = 0;
    double current_value = 0;
    int level = 0;
    Node* parent;

    Node() : parent(nullptr) {}
    ~Node() {
        if (parent != nullptr) {
            parent = nullptr; 
        }
    }
};

// 必须是但是质量的价钱从高到低
/*Vector<double> weight = {1,2,3,4,5,6,7,8,9,10};*/
//Vector<int> value = {1,4,5,25,14,8,15,14,14,10};
//double pack_weight = 34;
//int numbers = weight.size();

Vector<double> weight = {16,15,15};
Vector<double> value = {48,30,30};
double pack_weight = 30;
int numbers = weight.size();

// 限界值 下界
double best_value = 0;

double upbound(Node *node) {
    double left_weight = pack_weight - node->current_weight;
    double max_value = node->current_value;

    int i = node->level;
    for (;i < numbers; i++) {
        if (weight[i] <= left_weight) {
            max_value += value[i];
            left_weight -= weight[i];
        } else {
            break;
        }
    }
    if (i < numbers) {
        max_value += (value[i] / weight[i]) * left_weight;
    }

    return max_value;
}

int main() {
    size_t loop_times = 0;
    
    std::priority_queue<std::pair<double, Node*>> pqueue;
    Node* root = new Node();

    pqueue.push(std::make_pair(9999, root));
    while (!pqueue.empty()) {
        loop_times++;
        auto node = pqueue.top().second;
        int deep = node->level;
        double current_value = node->current_value;
        double current_weight = node->current_weight;
        pqueue.pop();

        // 01背包问题的分支,取和不取 分别算出upbound
        if (current_weight + weight[deep] <= pack_weight) {
            Node *new_node_with_1 = new Node();
            new_node_with_1->level = deep + 1;
            new_node_with_1->current_weight = current_weight + weight[deep];
            new_node_with_1->current_value = current_value + value[deep];
            new_node_with_1->parent = node;

            if (new_node_with_1->level >= numbers) {
                if (new_node_with_1->current_value > best_value) {
                    best_value = new_node_with_1->current_value;
                    std::cout << "find a better result: " << best_value << std::endl;
                }
            } else {
                // 限界函数进行剪枝
                double expect_max_value = upbound(new_node_with_1);
                if (expect_max_value> best_value) {
                    pqueue.push(std::make_pair(expect_max_value, new_node_with_1));
                }
            }
        }

        Node *new_node_with_0 = new Node();
        new_node_with_0->level = deep + 1;
        new_node_with_0->current_weight = current_weight;
        new_node_with_0->current_value = current_value;
        new_node_with_0->parent = node;

        if (new_node_with_0->level >= numbers) {
            if (new_node_with_0->current_value > best_value) {
                best_value = new_node_with_0->current_value;
                std::cout << "find a better result: "<<  best_value << std::endl;
            }
        } else {
            double expect_max_value = upbound(new_node_with_0);
            if (expect_max_value > best_value) {
                pqueue.push(std::make_pair(expect_max_value, new_node_with_0));
            }
        }

        delete node;  
    }

    std::cout << "Total search times: " <<  loop_times << std::endl;
}
