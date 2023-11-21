#include <iostream>
#include <vector>
#include <climits>
#include <map>
#include "interface.h"

using namespace std;


void MinHeap::heapifyUp(int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && heap[index].expiration_date < heap[parent].expiration_date) {
        //std::swap(heap[index], heap[parent]);
        troca_interna(index, parent);
        index = parent;
        parent = (index - 1) / 2;
    }
}

void MinHeap::heapifyDown(int index) {
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int smallest = index;

    if (leftChild < heap.size() && heap[leftChild].expiration_date <= heap[smallest].expiration_date) {
        smallest = leftChild;
    }

    if (rightChild < heap.size() && heap[rightChild].expiration_date <= heap[smallest].expiration_date) {
        smallest = rightChild;
    }

    if (smallest != index) {
        //std::swap(heap[index], heap[smallest]);
        troca_interna(index, smallest);
        heapifyDown(smallest);
    }
}

void MinHeap::troca_interna(int index1, int index2) {
    if (index1 < 0 || index1 >= heap.size() || index2 < 0 || index2 >= heap.size()) {
        throw std::out_of_range("Index out of range.");
    }

    swap(heap[index1], heap[index2]);

    int aux = TS2[heap[index1].position];
    TS2[heap[index1].position] = TS2[heap[index2].position];
    TS2[heap[index2].position] = aux;

    //print_hash();
}

int MinHeap::sibling(int index){
    if(index < 0 || index > heap.size() - 1){
        cout << "Erro no sibling" << endl;
        return 0;
    }

    int dad = (index - 1)/2;
    if(dad * 2 + 1 == index){
        return dad*2 + 2;
    }
    return dad*2 + 1;
}

MinHeap::MinHeap(){
    
}

void MinHeap::print_hash(){
    for (const auto& pair : TS2) {
        std::cout << "ID: " << pair.first << " = " << pair.second << std::endl;
    }
}

void MinHeap::updateKey(int index){
    if(index < 0 || index >= heap.size()){
        return;
    }

    if(index > 0){ //checa com pai

        int parent_index = (index - 1) / 2;

        if(heap[parent_index].expiration_date > heap[index].expiration_date){
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
        if(heap[min_child].expiration_date > heap[index_second_child].expiration_date){
            min_child = index_second_child;
        }

        if(heap[index].expiration_date > heap[min_child].expiration_date){
            //std::swap(heap[min_child].expiration_date, heap[index].expiration_date);
            troca_interna(min_child, index);
            updateKey(min_child);
        }
    }
    else if(index_first_child < heap.size()){
        if(heap[index].expiration_date > heap[index_first_child].expiration_date){
            troca_interna(index_first_child, index);
            //std::swap(heap[index_first_child].expiration_date, heap[index].expiration_date);
            updateKey(index_first_child);
        } 
    }
    else if(index_second_child < heap.size()){
        if(heap[index].expiration_date > heap[index_second_child].expiration_date){
            troca_interna(index_second_child, index);
            //std::swap(heap[index_second_child], heap[index]);
            updateKey(index_second_child);
        }
    }
    
}

void MinHeap::changeKey(int index, int newVal){
    if(index < 0 || index >= heap.size()){
        return;
    }
    heap[index].expiration_date = newVal;
}

void MinHeap::insert(double value) {
    int index = heap.size();
    TS2[index] = index;

    Certificate new_cert = {index, value};

    heap.push_back(new_cert);
    heapifyUp(heap.size() - 1);
}

void MinHeap::atualiza_certificados_relacionados(int index){
    update_certificate(index);
    update_certificate(2 * index + 1);
    update_certificate(2 * index + 2);
}

void MinHeap::realiza_troca_certificados(int index){
    update_certificate((index - 1)/2);
    update_certificate(index);
    update_certificate(2 * index + 1);
    update_certificate(2 * index + 2);
    int s = sibling(index);
    update_certificate(s);
}

void MinHeap::realiza_certificados_change(int index){
    update_certificate(index);
    update_certificate(2*index + 1);
    update_certificate(2*index + 2);
}

void MinHeap::update_certificate(int index){
    if(index < 0 || index > heap.size() - 1){
        return;
    }
    int position_on_minheap = TS2[index];

    heap[position_on_minheap].expiration_date = maxheap->calculate_cert_with_dad(heap[position_on_minheap].position);
    updateKey(position_on_minheap);
}

double MinHeap::extractMin() {
    if (heap.empty()) {
        std::cerr << "Heap is empty.\n";
        return -1; // or some sentinel value
    }

    int minValue = heap[0].expiration_date;
    heap[0] = heap.back();
    heap.pop_back();
    heapifyDown(0);

    return minValue;
}

int MinHeap::getMin(){
    return heap[0].position;
}

double MinHeap::Min(){
    if(heap.size() < 1){
        return -1;
    }
    return heap[0].expiration_date;
}

void MinHeap::print() {
    for (Certificate value : heap) {
        std::cout << value.position << " " << value.expiration_date << " ";
    }
    std::cout << "\n";
}

void MinHeap::delete_last_index_certificate(int index){
    int real_index = TS2[index];

    troca_interna(real_index, heap.size() - 1);
    TS2.erase(heap.size() - 1);
    heap.pop_back();
    updateKey(real_index);
}


/*
int main() {
    MinHeap minHeap;

    minHeap.insert(3);
    minHeap.insert(1);
    minHeap.insert(4);
    minHeap.insert(2);
    minHeap.insert(5);
    minHeap.insert(6);
    minHeap.insert(7);
    minHeap.insert(8);
    minHeap.insert(9);


    std::cout << "Min Heap: ";
    //minHeap.print();

    //std::cout << "Extract Min: " << minHeap.extractMin() << "\n";

    std::cout << "Min Heap after extraction: ";
    minHeap.print();

    //minHeap.changeKey(3,-1);
    //minHeap.print();
    //minHeap.updateKey(3);
    //minHeap.print();

    //minHeap.changeKey(0,10);
    //minHeap.print();
    //minHeap.updateKey(0);
    //minHeap.print();

    minHeap.print_hash();

    int agora = minHeap.TS2[3];
    cout << "agora = " << agora << endl;

    return 0;
}
*/
