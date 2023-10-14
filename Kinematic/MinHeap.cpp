#include <iostream>
#include <vector>
#include <climits>
#include "teste.h"

using namespace std;

MinHeap::MinHeap() {
}

MinHeap::MinHeap(vector<int>* hash_table) {
    min_hash = hash_table;
}

void MinHeap::troca_interna(int index1, int index2) {
    cout << "TROCA DO MIN HEAP!!" << endl;
    for(int i = 0; i < min_hash->size(); i++){
        cout << "i = " << i << " " << min_hash->at(i) << endl;
    }
    cout << "index 1 e 2 = " << index1 << index2 << endl;

    swap(heap[index1], heap[index2]);

    int aux = min_hash->at(index1);
    min_hash->at(index1) = min_hash->at(index2);
    min_hash->at(index2) = aux;
    print_hash();
}

void MinHeap::insert(int position, int date) {
    Certificate cert;
    cert.position = position;
    cert.expiration_date = date;
    heap.push_back(cert);
    int index = heap.size() - 1;
    min_hash->push_back(min_hash->size());

    while (index > 0) {
        int parent_index = (index - 1) / 2;
        if (heap[index].expiration_date < heap[parent_index].expiration_date) {
            troca_interna(index, parent_index);
            index = parent_index;
        } else {
            break;
        }
    }
}

void MinHeap::extractMin() {
    if (heap.empty()) {
        return;
    }

    heap[0] = heap.back();
    heap.pop_back();
    heapify(0);
}

Certificate MinHeap::getMin() {
    if (heap.empty()) {
        throw std::runtime_error("Heap is empty.");
    }
    return heap[0];
}

bool MinHeap::isEmpty() {
    return heap.empty();
}

void MinHeap::create_certificate(int i){
    if(this->isEmpty()){
        this->insert(0, INT_MAX);
    }
    else{

    }
}

void MinHeap::update(int i) {

}

void MinHeap::updateKey(int position, int newExpirationDate) {
    int index = -1;

    for (int i = 0; i < heap.size(); i++) {
        if (heap[i].position == position) {
            index = i;
            break;
        }
    }

    if (index < 0) {
        throw std::runtime_error("Position not found.");
    }

    int tempo = 1; // tempo não está declarado em qualquer lugar aqui
    heap[index].expiration_date = newExpirationDate;
    int current = index;

    while (current > 0 && heap[current].expiration_date < heap[(current - 1) / 2].expiration_date) {
        troca_interna(current, (current - 1) / 2);
        current = (current - 1) / 2;
    }

    
}

void MinHeap::print_cru() {
    cout << "----- PRINT CRU" << endl;
    for (int i = 0; i < heap.size(); i++) {
        cout << "[" << i << "] = " << heap[i].position << " " << heap[i].expiration_date << endl;
    }
    cout << "----- PRINT CRU" << endl;
    cout << endl;
}

void MinHeap::print_hash() {
    cout << "----- PRINT HASH" << endl;
    for (int i = 0; i < min_hash->size(); i++) {
        cout << "[" << i << "] = " << min_hash->at(i) << endl;
    }
    cout << "----- PRINT HASH" << endl;
    cout << endl;
}

void MinHeap::set_max_heap(MaxHeap* maxh) {
    maxheap = maxh;
}

void MinHeap::print_max_do_min() {
    maxheap->print();
}

void MinHeap::heapify(int index) {
    int smallest = index;
    int left_child = 2 * index + 1;
    int right_child = 2 * index + 2;

    if (left_child < heap.size() && heap[left_child].expiration_date < heap[smallest].expiration_date) {
        smallest = left_child;
    }

    if (right_child < heap.size() && heap[right_child].expiration_date < heap[smallest].expiration_date) {
        smallest = right_child;
    }

    if (smallest != index) {
        troca_interna(index, smallest);
        heapify(smallest);
    }
}
