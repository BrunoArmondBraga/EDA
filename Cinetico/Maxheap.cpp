#include <iostream>
#include <vector>
#include <climits>
#include <map>
#include "interface.h"

using namespace std;

void MaxHeap::heapifyUp(int index){
    int parent = (index - 1) / 2;
    while (index > 0 && heap[index].x0 + heap[index].v * time > heap[parent].x0 + heap[parent].v * time) {
        //std::swap(heap[index], heap[parent]);
        troca_interna(index, parent);
        index = parent;
        parent = (index - 1) / 2;
    }
}

void MaxHeap::heapifyDown(int index) {
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int greatest = index;

    if (leftChild > heap.size() && heap[leftChild].x0 + heap[leftChild].v * time < heap[greatest].x0 + heap[greatest].v * time) {
        greatest = leftChild;
    }

    if (rightChild > heap.size() && heap[rightChild].x0 + heap[rightChild].v * time < heap[greatest].x0 + heap[greatest].v * time) {
        greatest = rightChild;
    }

    if (greatest != index) {
        //std::swap(heap[index], heap[greatest]);
        troca_interna(index, greatest);
        heapifyDown(greatest);
    }
}

void MaxHeap::troca_interna(int index1, int index2) {
    if (index1 < 0 || index1 >= heap.size() || index2 < 0 || index2 >= heap.size()) {
        throw std::out_of_range("Index out of range.");
    }

    swap(heap[index1], heap[index2]);

    int first_id = heap[index1].id;
    int second_id = heap[index2].id;

    int aux = TS1[first_id];
    TS1[first_id] = TS1[second_id];
    TS1[second_id] = aux;

    int max = index1;
    if(index2 > index1){
        max = index2;
    }
    //minheap->realiza_troca_certificados(index1);
    minheap->realiza_troca_certificados(max);
}

void MaxHeap::change_velocity(int id, int new_v){
    int heap_position = TS1[id];

    int x_now = heap[heap_position].v * time;
    int k = x_now - new_v * time;


    heap[heap_position].x0 = heap[heap_position].x0 + k; 
    heap[heap_position].v = new_v;
    minheap->realiza_certificados_change(heap_position);
}

void MaxHeap::delete_elem(int index){
    if(heap.size() < 1 || index > heap.size() || index < 0){
        return;
    }

    int id = heap[index].id;

    troca_interna(index,heap.size()-1);
    minheap->delete_last_index_certificate(index);
    minheap->atualiza_certificados_relacionados(index);
    heap.pop_back();
    TS1.erase(id);
    updateKey(index);
}

int MaxHeap::find_pos_with_id(int id){
    return TS1[id];
}

MaxHeap::MaxHeap(){
    time = 0;
}

void MaxHeap::change_time(double t){
    time = t;
}

double MaxHeap::calculate_cert_with_dad(int index){
    if(index < 0 || index > heap.size() - 1){
        cout << "Não é possivel calcular o certificado do elemento " << index << endl; 
        return -1;
    }

    if(index == 0){
        return INT_MAX;
    }

    int index_dad = (index - 1)/2;

    Element son = heap[index];
    Element dad = heap[index_dad];

    double v_dad = dad.v; 
    double x_dad = dad.x0;
    double v_son = son.v;
    double x_son = son.x0;

    if(v_dad == v_son){
        return INT_MAX;
    }

    double result = (x_son - x_dad) / (v_dad - v_son);
    
    if(result <= time){
        return INT_MAX;
    }
    return result;
}

void MaxHeap::print_hash(){
    for (const auto& pair : TS1) {
        std::cout << "ID: " << pair.first << " = " << pair.second << std::endl;
    }
}


void MaxHeap::updateKey(int index){
    if(index < 0 || index >= heap.size()){
        return;
    }

    if(index > 0){ //checa com pai

        int parent_index = (index - 1) / 2;

        if(heap[parent_index].x0 + heap[parent_index].v * time < heap[index].x0 + heap[index].v * time){
            //std::swap(heap[parent_index], heap[index]);
            troca_interna(parent_index,index);
            updateKey(parent_index);
            return;
        }
        //0 -> 1,2
        //1 -> 3,4
        //2 -> 5,6
    }


    int index_first_child = 2 * index + 1;
    int index_second_child = 2 * index + 2;

    if(index_first_child < heap.size() && index_second_child < heap.size()){
        int min_child = index_first_child;
        if(heap[min_child].x0 + heap[min_child].v * time < heap[index_second_child].x0 + heap[index_second_child].v * time){
            min_child = index_second_child;
        }

        if(heap[index].x0 + heap[index].v * time < heap[min_child].x0 + heap[min_child].v * time){
            //std::swap(heap[min_child], heap[index]);
            troca_interna(min_child, index);
            updateKey(min_child);
        }
    }
    else if(index_first_child < heap.size()){
        if(heap[index].x0 + heap[index].v * time < heap[index_first_child].x0 + heap[index_first_child].v * time){
            troca_interna(index_first_child, index);
            //std::swap(heap[index_first_child], heap[index]);
            updateKey(index_first_child);
        } 
    }
    else if(index_second_child < heap.size()){
        if(heap[index].x0 + heap[index].v * time < heap[index_second_child].x0 + heap[index_second_child].v * time){
            troca_interna(index_second_child, index);
            //std::swap(heap[index_second_child], heap[index]);
            updateKey(index_second_child);
        }
    }
    
}

void MaxHeap::changeKey(int index, int newVal){
    if(index < 0 || index >= heap.size()){
        return;
    }
    heap[index].x0 = newVal;
    updateKey(index);
}

void MaxHeap::insert(int id, int x, int v) {
    int index = heap.size();
    TS1[id] = index;

    int first_position = x;
    if(time > 0){
        first_position = x - v * time;
    }

    Element new_elem = {id, first_position, v};

    heap.push_back(new_elem);

    minheap->insert(calculate_cert_with_dad(index));

    heapifyUp(heap.size() - 1);
}

int MaxHeap::extractMax() {
    if (heap.empty()) {
        std::cerr << "Heap is empty.\n";
        return -1; // or some sentinel value
    }

    /* Element maxValue = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    heapifyDown(0); */

    return heap[0].id;
}

void MaxHeap::print() {
    if(heap.size() < 1){
        cout << "nenhum elemento" << endl;
        return;
    }
    debug_rec(0,0);
}

void MaxHeap::debug_rec(int index, int i){
    int first_son = 2*index + 1;
    int second_son = 2*index + 2;
    if(first_son < heap.size()){
        debug_rec(first_son, i + 3);
    }
    for(int j=0;j<i;j++){
        cout << " ";
    }

    Element myself = heap[index];

    cout << myself.v * time + myself.x0 << " (" << myself.x0 << " " << myself.v << ")"; 
    cout << endl;

    if(second_son < heap.size()){
        debug_rec(second_son, i + 3);
    }
}

void MaxHeap::debug_print(){
    cout << endl;
    cout << "elemento (id, x, v0)" << endl;
    for(int i = 0; i < heap.size(); i++){
        cout << "elemento[" << i << "]  " << heap[i].v*time + heap[i].x0 <<"   (" << heap[i].id << ", " << heap[i].x0 << ", " << heap[i].v << ")" << endl;  
    }
    cout << endl;
}

/*
int main() {
    MaxHeap maxHeap;
    maxHeap.time = 15;

    
    maxHeap.insert(10,3,1);
    maxHeap.insert(20,1,1);
    maxHeap.insert(30,4,1);
    maxHeap.insert(40,2,1);
    maxHeap.insert(50,5,1);
    maxHeap.insert(60,6,1);
    maxHeap.insert(70,7,1);
    maxHeap.insert(80,8,1);
    maxHeap.insert(90,9,1);

    std::cout << "Min Heap after extraction: ";
    maxHeap.print();

    //MaxHeap.changeKey(3,-1);
    //MaxHeap.print();
    //MaxHeap.updateKey(3);
    //MaxHeap.print();

    //MaxHeap.changeKey(0,10);
    //MaxHeap.print();
    //MaxHeap.updateKey(0);
    //MaxHeap.print();

    maxHeap.print_hash();
    maxHeap.debug_print();

    maxHeap.changeKey(0,-1);
    //maxHeap.updateKey(0);
    maxHeap.debug_print();

    return 0;
}
*/
