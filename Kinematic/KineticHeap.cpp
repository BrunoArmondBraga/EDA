#include <iostream>
#include <vector>
#include <climits>
#include "teste.h"

using namespace std;

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