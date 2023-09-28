// StaticSegmentedTree.h

#pragma once

#include <vector>

using namespace std;

class StaticSegmentedTree {
private:
    class Node {
    public:
        int val;
        Node* esq;
        Node* dir;
        int num_esq;
        bool esq_aberta;
        int num_dir;
        bool dir_aberta;
        std::vector<int> segmentos;

        Node();
        Node(int v);
        ~Node();
        void print_segmentos();
    };

    Node* root;
    std::vector<int> intervalos;

    void sort_and_remove_duplicates();
    void create_tree(int t);
    Node* create_tree_skeleton(int t);
    void put_leafs(Node* node, int& t);
    void debug_rec(Node* u, int i);
    void debug_rec_filling(Node* u, int i);
    void numera_preenchendo(Node* node, int& index, std::vector<int>& segmentos);
    void put_segments();
    void put_segment(Node* u, int a, int b, int name);
    bool included(Node* u, int t);
    void print_debug_segmentos(std::vector<int> segmentos);

public:
    StaticSegmentedTree(std::vector<int> segments);
    ~StaticSegmentedTree();
    void print();
    void find_time(int t);
    std::vector<int> return_intervalos();
};

