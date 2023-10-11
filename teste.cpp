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
    MaxHeap(){}
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

struct Certificate{
    int position;
    int expiration_date;
};

class MinHeap {
private:
    std::vector<Certificate> heap;
    std::vector<int>* min_hash;
    

    void heapify(int index) {
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

    void troca_interna(int index1, int index2) {
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

public:
    MinHeap(){}
    MinHeap(vector<int>* hash_table) {
        min_hash = hash_table;
    }
    void insert(int position, int date) {
        struct Certificate certificado = {position, date};
        if(min_hash->empty()){
            min_hash->push_back(0);
        }
        else{
            min_hash->push_back(min_hash->size());
        }
        
        heap.push_back(certificado);
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

    void extractMin() {
        if (heap.empty()) {
            return;
        }

        heap[0] = heap.back();
        heap.pop_back();
        heapify(0);
    }

    int getMin() {
        if (heap.empty()) {
            throw std::runtime_error("Heap is empty.");
        }
        return heap[0].expiration_date;
    }

    bool isEmpty() {
        return heap.empty();
    }

    void print(){
        for(int i = 0; i < heap.size(); i++){
            cout << "[" << i << "] = (" << heap[i].position << " " << heap[i].expiration_date << ")" << endl;
        }
        cout << endl;
    }

    void updateKey(int position, int newExpirationDate) {
        // Encontrar o índice do struct com a posição dada
        int index = -1;
        for (int i = 0; i < heap.size(); i++) {
            if (heap[i].position == position) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            // O struct com a posição especificada não foi encontrado
            throw std::runtime_error("Certificate not found.");
        }

        // Atualize o valor do expiration_date
        heap[index].expiration_date = newExpirationDate;

        // Verifique se a atualização violou a propriedade do heap
        int parent_index = (index - 1) / 2;
        if (index > 0 && heap[index].expiration_date < heap[parent_index].expiration_date) {
            // Reorganize o elemento para cima
            while (index > 0 && heap[index].expiration_date < heap[parent_index].expiration_date) {
                std::swap(heap[index], heap[parent_index]);
                index = parent_index;
                parent_index = (index - 1) / 2;
            }
        } else {
            // Reorganize o elemento para baixo
            heapify(index);
        }
    }

    void print_cru(){
        cout << "----- PRINT CRU" << endl;
        for (int i = 0; i < heap.size(); i++) {
            //cout << "[" << i << "] = " << heap[i] << endl;
            cout << "[" << i << "] = (" << heap[i].position << " " << heap[i].expiration_date << ")" << endl;
        }
        cout << "----- PRINT CRU" << endl;
        cout << endl;
    }

    void print_hash(){
        for(int i = 0; i < min_hash->size(); i++){
            cout << "i = " << i << " " << min_hash->at(i) << endl;
        }
    }

};

class MinHeap_original {
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

class KinecticHeap{
    public:
        vector<int> symbol_table;
        vector<int> max_hash_table;
        vector<int> min_hash_table;
        MaxHeap maxHeap;
        MinHeap minheap;
        int time;

    KinecticHeap(){
        time = 0;
        maxHeap = MaxHeap(&symbol_table, &max_hash_table, &time);
        minheap = MinHeap(&min_hash_table);
    }

    void Insert_inicial_certificates(int x, int v){
        symbol_table.push_back(x);
        symbol_table.push_back(v);
        max_hash_table.push_back(max_hash_table.size());
        maxHeap.add_last_item();
        maxHeap.print();
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
        Heap_cinetico.Insert_inicial_certificates(x,v);
    }

    for(int i = 0; i < Heap_cinetico.max_hash_table.size(); i++){
        cout << "i = " << i << "  =  " << Heap_cinetico.max_hash_table[i] << endl;
    }
    Heap_cinetico.maxHeap.print_cru();

    //esboço da função update:
    //caso chamassemos update(0)
    //entrada A -> D -> B -> C
    // A=1,1 B=4,0 C=9,-1 D=2,-1
    cout << "ANTES DA MUDANÇA!" << endl;
    for(int i = 0; i < Heap_cinetico.symbol_table.size(); i = i + 2){
        cout << "[" << i/2 << "] = (" << Heap_cinetico.symbol_table[i] << "," << Heap_cinetico.symbol_table[i+1] << ")" << endl;
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
    for(int i = 0; i < Heap_cinetico.max_hash_table.size(); i++){
        cout << "[" << i << "] = " << Heap_cinetico.max_hash_table[i] << endl;
    }

    for(int i = 0; i < 10; i++){
        cout << endl;
    }

    vector<int> min_hash_table;
    MinHeap minheap = MinHeap(&min_hash_table);
    minheap.insert(1,8);
    minheap.insert(2,2);
    minheap.insert(3,4);
    minheap.insert(4,1);
    cout << "oi" << minheap.getMin() << endl;
    minheap.print_cru();

    cout << "-----" << endl;

    minheap.updateKey(4,12);
    minheap.print_cru();
    

    return 0;
}

// INT_MIN