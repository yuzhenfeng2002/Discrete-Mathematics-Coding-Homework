#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::tuple;
using std::pair;

// Define the node of a tree
struct node {
    int value;
    node* left = NULL;
    node* right = NULL;
};

// Pre-order walk and print the Huffman code
void preorderWalk(node* x, vector<bool> code)
{
    if (x->left) {
        auto code_left = code;
        code_left.push_back(0);
        preorderWalk(x->left, code_left);
    }
    if (x->right) {
        auto code_right = code;
        code_right.push_back(1);
        preorderWalk(x->right, code_right);
    }
    if (!x->left && !x->right)
    {
        cout << x->value << '\t';
        for (size_t i = 0; i < code.size(); i++)
        {
            cout << code.at(i);
        }
        cout << endl;
        return;
    }
}

int main() {
    int node_num;
    cout << "Please input the number of nodes: ";
    cin >> node_num;

    cout << "Please input the frequencies of these nodes: \n";
    auto nodes = vector<node*>();
    for (size_t i = 0; i < node_num; i++) {
        node* new_node = new node;
        cin >> new_node->value;
        nodes.push_back(new_node);
    }

    // Build a Min-heap
    std::make_heap(nodes.begin(), nodes.end(), [](node* a, node* b) {
        return a->value > b->value;
    });

    while (nodes.size() > 1) {
        // Extract two minimum elements from the heap
        std::pop_heap(nodes.begin(), nodes.end(), [](node* a, node* b) {
            return a->value > b->value;
        });
        node* node1 = nodes.back();
        nodes.pop_back();

        std::pop_heap(nodes.begin(), nodes.end(), [](node* a, node* b) {
            return a->value > b->value;
        });
        node* node2 = nodes.back();
        nodes.pop_back();

        // Sum the two elements and push them into the heap
        node* new_node = new node;
        new_node->left = node2;
        new_node->right = node1;
        new_node->value = node1->value + node2->value;
        nodes.push_back(new_node);
        std::push_heap(nodes.begin(), nodes.end(), [](node* a, node* b) {
            return a->value > b->value;
        });
    }

    preorderWalk(nodes.at(0), vector<bool>());

    system("pause");
    return 0;
}