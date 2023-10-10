#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class MaxHeap {
private:
    std::vector<int> heap;
    std::vector<int>* TS;
    std::vector<int>* hash;
    int* t;

    void heapify(int index) {
        int largest = index;
        int left_child = 2 * index + 1;
        int right_child = 2 * index + 2;
        int tempo = *t;

        if (left_child < heap.size() && TS->at(2 * heap[left_child]) + TS->at(2 * heap[left_child] + 1) * tempo > TS->at(2 * heap[largest]) + TS->at(2 * heap[largest] + 1) * tempo ) {
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

    void troca_interna(int index1, int index2) {
        cout << "index 1 e 2 = " << index1 << index2 << endl;

        int valor_um = heap[index1];
        int valor_dois = heap[index2];

        swap(heap[index1], heap[index2]);
        //valor tem q ser trocado na hash table!
        /* int aux = hash->at(index1);
        hash->at(index1) = hash->at(index2);
        hash->at(index2) = aux; */

        int aux = hash->at(valor_um);
        hash->at(valor_um) = hash->at(valor_dois);
        hash->at(valor_dois) = aux;
    }

    void recursive_print(int x, int back){
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

public:
    MaxHeap(vector<int>* symbol_table, vector<int>* hash_table, int* time) {
        TS = symbol_table;
        hash = hash_table;
        t = time; // Correção para atribuir o valor de 'time' a 't'
    }

    void insert(int item) {
        cout << "item = " << item << endl;
        heap.push_back(item);
        int index = heap.size() - 1;
        int tempo = *t;

        while (index > 0) {
            int parent_index = (index - 1) / 2;
            //if (heap[index] > heap[parent_index]) {
            cout << "primeiro = " << TS->at(2 * index) + TS->at(2 * index + 1) * tempo << endl;
            cout << "segundo = " << TS->at(2 * parent_index) + TS->at(2 * parent_index + 1) * tempo << endl;
            if(TS->at(2 * heap[index]) + TS->at(2 * heap[index] + 1) * tempo > TS->at(2 * heap[parent_index]) + TS->at(2 * heap[parent_index] + 1) * tempo){
                troca_interna(index,parent_index);
                index = parent_index;
            } else {
                break;
            }
        }
    }

    void extractMax() {
        if (heap.empty()) {
            return;
        }

        heap[0] = heap.back();
        heap.pop_back();
        heapify(0);
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
        recursive_print(0,0);
        /* for (int i = 0; i < heap.size(); i++) {
            cout << "[" << i << "] = " << TS->at(heap[i] * 2) << endl;
        }
        cout << endl; */
    }

    void print_cru(){
        cout << "----- PRINT CRU" << endl;
        for (int i = 0; i < heap.size(); i++) {
            //cout << "[" << i << "] = " << heap[i] << endl;
            cout << "[" << i << "] = " << heap[i] << endl;
        }
        cout << "----- PRINT CRU" << endl;
        cout << endl;
    }

    /* void updateKey(int index) {
        if (index < 0 || index >= heap.size()) {
            throw std::out_of_range("Index out of range.");
        }

        //heap[index] = newKey;
        int tempo = *t;
        while (index > 0) {
            int parent_index = (index - 1) / 2;
            if(TS->at(2 * heap[index]) + TS->at(2 * heap[index] + 1) * tempo > TS->at(2 * heap[parent_index]) + TS->at(2 * heap[parent_index] + 1) * tempo){
                troca_interna(index,parent_index);
                index = parent_index;
            }
            else {
                break;
            }
        }
        // Após atualizar a chave, pode ser necessário ajustar descendentes
        heapify(index);
    } */

    void updateKey(int index) {
        if (index < 0 || index >= heap.size()) {
            throw std::out_of_range("Index out of range.");
        }

        int current = heap[index];
        int parent_index = (current - 1) / 2;
        int tempo = *t;

        //cout << "valor do index = " << index << " = " << TS->at(2 * heap[current]) + TS->at(2 * heap[current] + 1) * tempo << endl;
        //cout << "valor do index = " << parent_index << " = " << TS->at(2 * heap[parent_index]) + TS->at(2 * heap[parent_index] + 1) * tempo << endl;



        // Verifica se o nó atual deve subir
        while (heap[current] >= 0 && TS->at(2 * heap[current]) + TS->at(2 * heap[current] + 1) * tempo > TS->at(2 * heap[parent_index]) + TS->at(2 * heap[parent_index] + 1) * tempo) {
            troca_interna(current, parent_index);
            current = parent_index;
            parent_index = (current - 1) / 2;
        }

        // Verifica se o nó atual deve descer
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
            // Recursivamente verifique se é necessário descer mais
            updateKey(largest);
        }
    }


    void add_last_item(){
        insert(heap.size());
    }
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
};

int main() {
    vector<int> symbol_table;
    vector<int> max_hash_table;
    int time = 0;
    MaxHeap maxHeap(&symbol_table, &max_hash_table, &time);

    int n, x, v;
    cout << "Escolha o número de elementos a adicionar:";
    cin >> n;
    
    for(int i = 0; i < n; i++){
        cin >> x;
        cin >> v;

        symbol_table.push_back(x);
        symbol_table.push_back(v);
        max_hash_table.push_back(max_hash_table.size());
        maxHeap.add_last_item();
        maxHeap.print();
    }

    for(int i = 0; i < max_hash_table.size(); i++){
        cout << "i = " << i << "  =  " << max_hash_table[i] << endl;
    }
    maxHeap.print_cru();

    //esboço da função update:
    //caso chamassemos update(0)
    //entrada A -> D -> B -> C
    // A=1,1 B=4,0 C=9,-1 D=2,-1
    cout << "ANTES DA MUDANÇA!" << endl;
    for(int i = 0; i < symbol_table.size(); i = i + 2){
        cout << "[" << i/2 << "] = (" << symbol_table[i] << "," << symbol_table[i+1] << ")" << endl;
    }
    /* cout << "me fala qual item deseja mudar: ";
    int id;
    cin >> id;
    cout << endl;

    cout <<  "nova posicao_inicial: ";
    int new_velocity;
    cin >> new_velocity;
    cout << endl;

    symbol_table[id*2] = new_velocity;
    maxHeap.updateKey(id);

    for(int i = 0; i < symbol_table.size(); i = i + 2){
        cout << "[" << i/2 << "] = (" << symbol_table[i] << "," << symbol_table[i+1] << ")" << endl;
    }

    maxHeap.print_cru(); */

    cout << "teste tabela de hash!" << endl;
    for(int i = 0; i < max_hash_table.size(); i++){
        cout << "[" << i << "] = " << max_hash_table[i] << endl;
    }

    return 0;
}

// INT_MIN