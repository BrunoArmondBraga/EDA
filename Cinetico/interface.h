#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <climits>

using namespace std;

struct Certificate {
    int position;
    double expiration_date;
};

struct Element {
    int id;
    int x0;
    int v;
};


class MinHeap;

class MaxHeap {
public:
    MaxHeap();
    double time;
    MinHeap* minheap;
    map<int, int> TS1;

    void change_time(double t);
    double calculate_cert_with_dad(int index);
    void print_hash();
    void updateKey(int index);
    void changeKey(int index, int newVal);
    void insert(int id, int x, int v);
    int extractMax();
    void print();
    void debug_print();
    void troca_interna(int index1, int index2);
    void change_velocity(int id, int new_v);
    void delete_elem(int index);
    int find_pos_with_id(int id);

private:
    vector<Element> heap;
    void heapifyUp(int index);
    void heapifyDown(int index);
    void debug_rec(int index, int i);


};

class MinHeap {
public:
    MinHeap();
    map<int, int> TS2;
    MaxHeap* maxheap;

    void print_hash();
    void updateKey(int index);
    void changeKey(int index, int newVal);
    void insert(double value);
    void atualiza_certificados_relacionados(int index);
    void realiza_troca_certificados(int index);
    void realiza_certificados_change(int index);
    void update_certificate(int index);
    double extractMin();
    int getMin();
    double Min();
    void print();
    void delete_last_index_certificate(int index);

private:
    vector<Certificate> heap;
    void heapifyUp(int index);
    void heapifyDown(int index);
    void troca_interna(int index1, int index2);
    int sibling(int index);
};

int main();
