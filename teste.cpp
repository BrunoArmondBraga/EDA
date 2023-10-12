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

class KinecticHeap{
    private:
    
    void event(Certificate certificado){
        int i = certificado.position;
        int i_sobre_dois = i / 2;
    
        if (i < 0 || i_sobre_dois >= maxHeap.size() || i_sobre_dois < 0 || i_sobre_dois >= maxHeap.size()) {
            throw std::out_of_range("Index out of range.");
        }

        int aux = maxHeap.heap[i];
        maxHeap.heap[i] = maxHeap.heap[i_sobre_dois];
        maxHeap.heap[i_sobre_dois] = aux;
    
        minheap.extractMin();
        
        if(i > 1){
            minheap.update(i_sobre_dois);
        }
        minheap.update(i);
        if(2 * i <= maxHeap.size()){
            minheap.update(2 * i);
        }
        if(2 * i + 1 <= maxHeap.size()){
            minheap.update(2 * i + 1);
        }
        int s = maxHeap.sibling(i);
        if(s > 0){
            minheap.update(s);
        }
    }

    public:
        vector<int> symbol_table;
        vector<int> max_hash_table;
        vector<int> min_hash_table;
        vector<int> id_hash_table;
        MaxHeap maxHeap;
        MinHeap minheap;
        int time;

    KinecticHeap(){
        time = 0;
        maxHeap = MaxHeap(&symbol_table, &max_hash_table, &time);
        minheap = MinHeap(&min_hash_table);
    }

    void insert_inicial_elements(int x, int v){
        symbol_table.push_back(x);
        symbol_table.push_back(v);
        max_hash_table.push_back(max_hash_table.size());
        maxHeap.add_last_item();
        maxHeap.print();
    }

    void advance(int t){
        if(time < t){
            cout << "O heap cinético não retrocede em tempo!" << endl;
            return;
        }
        while(minheap.getMin().expiration_date <= t){
            time = minheap.getMin().expiration_date;
            event(minheap.getMin());
        }
        time = t;
    }

    void change(int id, int v){

    }

    void insert(int id, int xnow, int v){
        if(time != 0){
            //fazer tratamento de xnow
        }
        else{
            insert_inicial_elements(xnow, v);
        }
    }

    int max(){
        if(maxHeap.size() == 0){
            return -1;
        }
        return maxHeap.getMax();
    }

    void delete_max(){

    }

    void delete_id(int id){

    }

    void print(){

    }
};


int main() {
    KinecticHeap Heap_cinetico = KinecticHeap();
    int n, x, v;
    cout << "Escolha o número de elementos a adicionar:";
    cin >> n;
    
    for(int i = 0; i < n; i++){
        cin >> x;
        cin >> v;
        Heap_cinetico.insert_inicial_elements(x,v);
    }

    cout << "Escolha:" << endl;
    cout << "1 <t>             significa Advance(t)" << endl;
    cout << "2 <id> <v>        significa Change(id, v)" << endl;
    cout << "3 <id> <xnow> <v> significa Insert(id, xnow, v)" << endl;
    cout << "4                 significa Max()" << endl;
    cout << "5                 significa DeleteMax()" << endl;
    cout << "6 <id>            significa Delete(id)" << endl;
    cout << "7                 significa Print()" << endl;

    while(cin >> n){
        switch (n)
        {
        case 1:
            cin >> x;
            Heap_cinetico.advance(x);
            break;
        case 2:
            cin >> x;
            cin >> v;
            Heap_cinetico.change(x,v);
            break;
        case 3:
            cin >> x;
            cin >> v;
            int j;
            cin >> j;
            Heap_cinetico.insert(x,v,j);
            break;
        case 4:
            cout << Heap_cinetico.max() << endl;
            break;
        case 5:
            Heap_cinetico.delete_max();
            break;
        case 6:
            cin >> x;
            Heap_cinetico.delete_id(x);
        case 7:
            Heap_cinetico.print();
        };
    }

    return 0;
}

// INT_MIN