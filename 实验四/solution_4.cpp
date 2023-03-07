#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <map>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::tuple;
using std::list;
using std::map;

int main() {
    int node_num;
    cout << "Please input the number of nodes: ";
    cin >> node_num;

    int edge_num;
    cout << "Please input the number of edges: ";
    cin >> edge_num;

    cout << "Please input the indices of edges and their weights: \n";
    auto edges = vector<tuple<int, int, int>>();
    for (size_t i = 0; i < edge_num; i++) {
        int begin_node, end_node, weight;
        cin >> begin_node >> end_node >> weight;
        edges.push_back(std::make_tuple(begin_node - 1, end_node - 1, weight));
    }

    vector<int> set_idx_of_node = vector<int>(node_num, -1);    // record which set one node is in
    map<int, vector<int>> sets = map<int, vector<int>>();       // record which node is contained in one set
    
    // Sort Edges in the Vector
    std::sort(edges.begin(), edges.end(), [](tuple<int, int, int> a, tuple<int, int, int> b) {
        return std::get<2>(a) < std::get<2>(b);   
    });

    // Generate the Spanning Tree
    auto tree_edges = vector<tuple<int, int, int>>();
    int total_weight = 0;
    for (size_t i = 0; i < edge_num; i++) {
        auto edge = edges.at(i);
        int begin_node = std::get<0>(edge);
        int end_node = std::get<1>(edge);
        int weight = std::get<2>(edge);
        if (set_idx_of_node[begin_node] == -1 || set_idx_of_node[end_node] == -1) {
            if (set_idx_of_node[begin_node] == -1 && set_idx_of_node[end_node] == -1) {
                sets.insert({begin_node, vector<int>({begin_node, end_node})});
                set_idx_of_node.at(begin_node) = begin_node;
                set_idx_of_node.at(end_node) = begin_node;
            }
            else if (set_idx_of_node[begin_node] == -1) {
                int set_idx = set_idx_of_node[end_node];
                sets.find(set_idx)->second.push_back(begin_node);
                set_idx_of_node.at(begin_node) = set_idx;
            }
            else {
                int set_idx = set_idx_of_node[begin_node];
                sets.find(set_idx)->second.push_back(end_node);
                set_idx_of_node.at(end_node) = set_idx;
            }
        }
        else if (set_idx_of_node[begin_node] != set_idx_of_node[end_node]) {
            int set_idx_of_begin_node = set_idx_of_node[begin_node];
            int set_idx_of_end_node = set_idx_of_node[end_node];
            auto nodes_with_end_node = sets.find(set_idx_of_end_node)->second;
            sets.find(set_idx_of_begin_node)->second.insert(sets.find(set_idx_of_begin_node)->second.end(), 
                                                            sets.find(set_idx_of_end_node)->second.begin(), 
                                                            sets.find(set_idx_of_end_node)->second.end());
            sets.erase(set_idx_of_end_node);
            for (size_t j = 0; j < nodes_with_end_node.size(); j++) {
                set_idx_of_node.at(nodes_with_end_node.at(j)) = set_idx_of_begin_node;
            }
        }
        else {
            continue;
        }

        tree_edges.push_back(edge);
        total_weight += weight;
    }

    // Print the Spanning Tree
    cout << "The edges are: \n";
    for (size_t i = 0; i < tree_edges.size(); i++) {
        auto edge = tree_edges.at(i);
        int begin_node = std::get<0>(edge);
        int end_node = std::get<1>(edge);
        cout << '(' << begin_node + 1 << ", " << end_node + 1 << ')' << endl;
    }
    cout << "The total weight is: " << total_weight << endl;
    
    system("pause");
    return 0;
}