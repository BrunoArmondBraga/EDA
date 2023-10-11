#pragma once

#include <vector>

struct Certificate {
    int position;
    int expiration_date;
};

class MinHeap;

class MaxHeap {
public:
    MaxHeap();
    MaxHeap(std::vector<int>* symbol_table, std::vector<int>* hash_table, int* time);
    void insert(int item);
    void extractMax();
    int getMax();
    bool isEmpty();
    void print();
    void print_cru();
    void updateKey(int index);
    void add_last_item();
    void set_min_heap(MinHeap* minh);
    void troca_interna(int index1, int index2);
    void recursive_print(int x, int back);

private:
    std::vector<int>* TS;
    std::vector<int>* hash;
    int* t;
    std::vector<int> heap;
    MinHeap* minheap;
    void heapify(int index);  // Adicionei a declaração do método heapify
};

class MinHeap {
public:
    MinHeap();
    MinHeap(std::vector<int>* hash_table);
    void insert(int position, int date);
    void extractMin();
    int getMin();
    bool isEmpty();
    void print();
    void updateKey(int position, int newExpirationDate);
    void print_cru();
    void print_hash();
    void set_max_heap(MaxHeap* maxh);
    void print_max_do_min();

private:
    std::vector<int>* min_hash;
    std::vector<Certificate> heap;
    MaxHeap* maxheap;
    void heapify(int index);  // Adicionei a declaração do método heapify
};

class KinecticHeap {
public:
    KinecticHeap();
    void Insert_inicial_certificates(int x, int v);
    void deletar_depois();
    std::vector<int> symbol_table;
    std::vector<int> max_hash_table;

private:
    MinHeap minheap;
    MaxHeap maxHeap;
    int time;
};

int main();
