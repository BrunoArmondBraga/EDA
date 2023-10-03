#include <iostream>
#include <vector>

using namespace std;

struct element {
    int id;
    int x;
    int v;
    int maxheap_position;
    int certificate_position;
};

class MinHeap {
private:
    std::vector<int> heap;

    void heapify(int index) {
        int smallest = index;
        int left_child = 2 * index + 1;
        int right_child = 2 * index + 2;

        if (left_child < heap.size() && heap[left_child] < heap[smallest]) {
            smallest = left_child;
        }

        if (right_child < heap.size() && heap[right_child] < heap[smallest]) {
            smallest = right_child;
        }

        if (smallest != index) {
            std::swap(heap[index], heap[smallest]);
            heapify(smallest);
        }
    }

public:
    void insert(int item) {
        heap.push_back(item);
        int index = heap.size() - 1;

        while (index > 0) {
            int parent_index = (index - 1) / 2;
            if (heap[index] < heap[parent_index]) {
                std::swap(heap[index], heap[parent_index]);
                index = parent_index;
            } else {
                break;
            }
        }
    }

    void extractMin() {
        if (heap.empty()) {
            return;
        }

        heap[0] = heap.back();
        //print();
        heap.pop_back();
        //print();
        heapify(0);
    }

    void troca(int i, int j){
        swap(heap[i], heap[j]);
    }

    int getMin() {
        if (heap.empty()) {
            throw std::runtime_error("Heap is empty.");
        }
        return heap[0];
    }

    bool isEmpty() {
        return heap.empty();
    }

    void print(){
        for(int i = 0; i < heap.size(); i++){
            cout << "[" << i << "] = " << heap[i] << endl;
        }
        cout << endl;
    }

    void update(int i){
        return;
    }

    int size(){
        return heap.size();
    }
};

class MaxHeap {
private:
    std::vector<int> heap;

    void heapify(int index) {
        int largest = index;
        int left_child = 2 * index + 1;
        int right_child = 2 * index + 2;

        if (left_child < heap.size() && heap[left_child] > heap[largest]) {
            largest = left_child;
        }

        if (right_child < heap.size() && heap[right_child] > heap[largest]) {
            largest = right_child;
        }

        if (largest != index) {
            std::swap(heap[index], heap[largest]);
            heapify(largest);
        }
    }

public:
    int insert(int item) {
        heap.push_back(item);
        int index = heap.size() - 1;

        while (index > 0) {
            int parent_index = (index - 1) / 2;
            if (heap[index] > heap[parent_index]) {
                std::swap(heap[index], heap[parent_index]);
                index = parent_index;
            } else {
                break;
            }
        }
        return index;
    }

    void extractMax() {
        if (heap.empty()) {
            return;
        }

        heap[0] = heap.back();
        heap.pop_back();
        heapify(0);
    }

    void troca(int i, int j){
        swap(heap[i], heap[j]);
    }

    int getMax() {
        if (heap.empty()) {
            throw std::runtime_error("Heap is empty.");
        }
        return heap[0];
    }

    bool isEmpty() {
        return heap.empty();
    }

    void print() {
        for (int i = 0; i < heap.size(); i++) {
            cout << "[" << i << "] = " << heap[i] << endl;
        }
        cout << endl;
    }

    int size(){
        return heap.size();
    }
};

class KineticHeap {
public:
    MinHeap Q;
    MaxHeap H;
    int now;

    vector<element> elements;

    KineticHeap(){

    }

    ~KineticHeap(){

    }

    void advance(int t){
        while(Q.getMin() <= t){
            now = Q.getMin();
            //Event(now);
        }
        now = t;
    }

    void event(int i, int t){
        H.troca(i,i/2);
        if(i > 1){
            Q.update(i/2);
        }
        Q.update(i);
        if(2 * i <= Q.size()){
            Q.update(2*i);
        }
        if(2 * i + 1 <= Q.size()){
            Q.update(2*i);
        }
        /* int s = sibling(i);
        if(s > 0){
            Q.update(s);
        } */
    } 

    void change(int i, int v){

    }

    void insert(int id, int x, int v){
        element i = {id, x, v};
        elements.push_back(i);
        int max_heap_position = H.insert();
    }

    void print_elements(){
        for(int i=0; i < elements.size(); i++){
            cout << "elemento [" << i << "] = " << elements[i].id << " " << elements[i].x << " " << elements[i].v << endl;
        }
    }

    void delete_with_id(int id){ //precisa deletar os certificados tbb!!
        for(int i=0; i < elements.size(); i++){
            if(elements[i].id == id){
                elements.erase(elements.begin() + i);
                return;
            }
        }
    }

private:
};

int main() {
    /* MinHeap minHeap;
    
    minHeap.insert(4);
    minHeap.insert(-2);
    minHeap.insert(3);
    minHeap.insert(7);
    minHeap.insert(1);
    minHeap.insert(9);
    minHeap.insert(12);
    minHeap.insert(-1);
    minHeap.insert(2);
    minHeap.print();
    
    for(int i = 0; i < 6; i++){
        std::cout << "Minimum element: " << minHeap.getMin() << std::endl;
        //minHeap.print();

        minHeap.extractMin();
        
        std::cout << "Minimum element after extraction: " << minHeap.getMin() << std::endl;
    }
    minHeap.print(); */

    KineticHeap KH = KineticHeap();
    KH.insert(100000001, 1, 2);
    KH.print_elements();

    return 0;
}
/* 
Heap cinético:

KinHeap(id, x0, speed, n): cria um maxheap cinético com n elementos,
  com identificador, valor inicial e velocidade nos vetores id, x0 e speed. 
Advance(t): avança o tempo para o instante t
Change(id, v): altera a velocidade do elemento id para v
Insert(id, xnow, v): insere o elemento id na posição xnow com velocidade v
Max(): identificador do elemento com o maior valor no instante atual
DeleteMax(): remove o elemento com o maior valor
Delete(id): remove o elemento id
Print(): imprime o heap no instante atual
 */