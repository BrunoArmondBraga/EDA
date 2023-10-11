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
    return heap[0];
}

bool MaxHeap::isEmpty() {
    return heap.empty();
}

void MaxHeap::print() {
    recursive_print(0, 0);
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

void MaxHeap::recursive_print(int x, int back) {
    int tempo = *t;
    if (x < 0 || x >= heap.size()) {
        return;
    }

    cout << "Index: " << x << " Position: " << TS->at(2 * heap[x]) << " Date: " << TS->at(2 * heap[x] + 1) * tempo << " Back: " << back << " Parent: " << TS->at(2 * heap[(x - 1) / 2]) << endl;

    if (2 * x + 1 < heap.size()) {
        recursive_print(2 * x + 1, x);
    }
    if (2 * x + 2 < heap.size()) {
        recursive_print(2 * x + 2, x);
    }
}

MinHeap::MinHeap() {
}

MinHeap::MinHeap(vector<int>* hash_table) {
    min_hash = hash_table;
}

void MinHeap::insert(int position, int date) {
    Certificate cert;
    cert.position = position;
    cert.expiration_date = date;
    heap.push_back(cert);
    int index = heap.size() - 1;

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

int MinHeap::getMin() {
    if (heap.empty()) {
        throw std::runtime_error("Heap is empty.");
    }
    return heap[0].position;
}

bool MinHeap::isEmpty() {
    return heap.empty();
}

void MinHeap::print() {
    recursive_print(0, 0);
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

KinecticHeap::KinecticHeap() {
    time = 0;
    maxHeap = MaxHeap(&symbol_table, &max_hash_table, &time);
    minheap = MinHeap(&min_hash_table);
    maxHeap.set_min_heap(&minheap);
    minheap.set_max_heap(&maxHeap);
}

void KinecticHeap::Insert_inicial_certificates(int x, int v) {
    symbol_table.push_back(x);
    symbol_table.push_back(v);
    max_hash_table.push_back(max_hash_table.size());
    maxHeap.add_last_item();
}

void KinecticHeap::deletar_depois() {
    minheap.insert(1, 8);
    minheap.insert(2, 2);
    minheap.insert(3, 4);
    minheap.insert(4, 1);

    cout << "MinHeap Min: " << minheap.getMin() << endl;

    cout << "-----" << endl;

    minheap.updateKey(4, 12);

    cout << "MinHeap Updated Min: " << minheap.getMin() << endl;
}

int main() {
    KinecticHeap Heap_cinetico = KinecticHeap();
    int n, x, v;
    cout << "Escolha o número de elementos a adicionar:";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> x;
        cin >> v;
        Heap_cinetico.Insert_inicial_certificates(x, v);
    }

    for (int i = 0; i < Heap_cinetico.max_hash_table.size(); i++) {
        cout << "i = " << i << "  =  " << Heap_cinetico.max_hash_table[i] << endl;
    }

    Heap_cinetico.deletar_depois();

    cout << "TESTE TESTE TESTE" << endl;
    Heap_cinetico.minheap.print_max_do_min();

    return 0;
}
