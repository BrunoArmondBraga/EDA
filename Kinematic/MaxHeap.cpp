#include <iostream>
#include <vector>
#include <climits>
#include "teste.h"

using namespace std;

MaxHeap::MaxHeap() {
}

MaxHeap::MaxHeap(vector<int>* symbol_table, vector<int>* hash_table, int* time) {
    TS = symbol_table;
    hash = hash_table;
    t = time;
}

void MaxHeap::insert(int item) {
    heap.push_back(item);
    int index = heap.size() - 1;
    int tempo = *t;

    while (index > 0) {
        int parent_index = (index - 1) / 2;
        if (TS->at(2 * heap[index]) + TS->at(2 * heap[index] + 1) * tempo > TS->at(2 * heap[parent_index]) + TS->at(2 * heap[parent_index] + 1) * tempo) {
            troca_interna(index, parent_index);
            index = parent_index;
        } else {
            break;
        }
    }
}

void MaxHeap::extractMax() {
    if (heap.empty()) {
        return;
    }

    heap[0] = heap.back();
    heap.pop_back();
    heapify(0);
}

int MaxHeap::getMax() {
    if (heap.empty()) {
        throw std::runtime_error("Heap is empty.");
    }
    for(int i= 0; i < heap.size(); i++){
        cout << "i = " << i << "      -> " << heap[i];
        cout << endl; 
    }
    return heap[0] + 1;
}

bool MaxHeap::isEmpty() {
    return heap.empty();
}

void MaxHeap::print() {
    cout << "Maxheap print!" << endl;
    recursive_print(0, 0);
    cout << endl;
}

void MaxHeap::print_cru() {
    cout << "----- PRINT CRU" << endl;
    for (int i = 0; i < heap.size(); i++) {
        cout << "[" << i << "] = " << heap[i] << endl;
    }
    cout << "----- PRINT CRU" << endl;
    cout << endl;
}

void MaxHeap::updateKey(int index) {
    if (index < 0 || index >= heap.size()) {
        throw std::out_of_range("Index out of range.");
    }

    int current = heap[index];
    int parent_index = (current - 1) / 2;
    int tempo = *t;

    while (heap[current] >= 0 && TS->at(2 * heap[current]) + TS->at(2 * heap[current] + 1) * tempo > TS->at(2 * heap[parent_index]) + TS->at(2 * heap[parent_index] + 1) * tempo) {
        troca_interna(current, parent_index);
        current = parent_index;
        parent_index = (current - 1) / 2;
    }

    int left_child = 2 * index + 1;
    int right_child = 2 * index + 2;
    int largest = index;

    if (left_child < heap.size() && TS->at(2 * heap[left_child]) + TS->at(2 * heap[left_child] + 1) * tempo > TS->at(2 * heap[largest]) + TS->at(2 * heap[largest] + 1) * tempo) {
        largest = left_child;
    }

    if (right_child < heap.size() && TS->at(2 * heap[right_child]) + TS->at(2 * heap[right_child] + 1) * tempo > TS->at(2 * heap[largest]) + TS->at(2 * heap[largest] + 1) * tempo) {
        largest = right_child;
    }

    if (largest != index) {
        troca_interna(index, largest);
        updateKey(largest);
    }
}

void MaxHeap::change_key(int id, int new_velocity){
    TS->at(id*2) = new_velocity;
    this->updateKey(id);
}

void MaxHeap::add_last_item() {
    insert(heap.size());
}

void MaxHeap::set_min_heap(MinHeap* minh) {
    minheap = minh;
}

void MaxHeap::heapify(int index) {
    int largest = index;
    int left_child = 2 * index + 1;
    int right_child = 2 * index + 2;
    int tempo = *t;

    if (left_child < heap.size() && TS->at(2 * heap[left_child]) + TS->at(2 * heap[left_child] + 1) * tempo > TS->at(2 * heap[largest]) + TS->at(2 * heap[largest] + 1) * tempo) {
        largest = left_child;
    }

    if (right_child < heap.size() && TS->at(2 * heap[right_child]) + TS->at(2 * heap[right_child] + 1) * tempo > TS->at(2 * heap[largest]) + TS->at(2 * heap[largest] + 1) * tempo) {
        largest = right_child;
    }

    if (largest != index) {
        troca_interna(index, largest);
        heapify(largest);
    }
}

void MaxHeap::troca_interna(int index1, int index2) {
    if (index1 < 0 || index1 >= heap.size() || index2 < 0 || index2 >= heap.size()) {
        throw std::out_of_range("Index out of range.");
    }

    int aux = heap[index1];
    heap[index1] = heap[index2];
    heap[index2] = aux;
}

void MaxHeap::recursive_print(int x, int back){
    if(x < 0 || x >= heap.size()){
        return;
    }
    int tempo = *t;
    recursive_print(2 * x + 1, back + 3);
    for(int j = 0; j < back; j++){
        cout << " ";
    }
    cout << TS->at(heap[x] * 2)+ TS->at(heap[x] * 2 + 1) * tempo  << " ";
    cout << "(" << TS->at(heap[x] * 2) << " " << TS->at(heap[x] * 2 + 1) << ")" << endl;
    recursive_print(2 * x + 2, back + 3);
}

int MaxHeap::size(){
    return heap.size();
}

int MaxHeap::sibling(int i){
    if(i == 0){
        return -1;
    }
    if(i % 2 == 0){
        return i - 1;
    }
    return i + 1;
}

