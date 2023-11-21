#include <iostream>
#include <vector>
#include <climits>
#include <map>
#include "interface.h"

using namespace std;

class KinecticHeap{
    MaxHeap *maxheap;
    MinHeap *minheap;
    public:
        KinecticHeap(){
            maxheap = new MaxHeap();
            minheap = new MinHeap();
            maxheap->minheap = minheap;
            minheap->maxheap = maxheap;
        }


        void advance(double t){
            while(minheap->Min() <= t){
                double new_t = minheap->Min();
                maxheap->change_time(new_t);
                event();
            }
            maxheap->time = t;
        }

        void change(int id, int v){
            maxheap->change_velocity(id,v);
        }

        void insert(int id, int xnow, int v){
            maxheap->insert(id, xnow,v);
        }

        int max(){
            return maxheap->extractMax();
        }

        void delete_max(){
            maxheap->delete_elem(0);
        }

        void delete_id(int id){
            maxheap->delete_elem(maxheap->find_pos_with_id(id));
        }

        void print(){
            maxheap->print();
        }
        void debug(){
            cout << "max heap!!!!" << endl;
            cout << "time atual = " << maxheap->time << endl;
            maxheap->print();
            maxheap->print_hash();

            cout << "min heap!!!!" << endl;
            minheap->print();
            minheap->print_hash();

            
        }
    private:
        void event(){
            int expirated_position = minheap->getMin();
            maxheap->troca_interna(expirated_position, (expirated_position -1)/2);
        }

};

int main() {
    KinecticHeap Heap_cinetico = KinecticHeap();
    int n,x, v;
    double new_t;
    cout << "Escolha o número de elementos a adicionar:";
    cin >> n;
    
    for(int i = 1; i <= n; i++){
        cin >> x;
        cin >> v;
        Heap_cinetico.insert(i, x, v);
    }

    cout << "Escolha:" << endl;
    cout << "1 <t>             significa Advance(t)" << endl;
    cout << "2 <id> <v>        significa Change(id, v)" << endl;
    cout << "3 <id> <xnow> <v> significa Insert(id, xnow, v)" << endl;
    cout << "4                 significa Max()" << endl;
    cout << "5                 significa DeleteMax()" << endl;
    cout << "6 <id>            significa Delete(id)" << endl;
    cout << "7                 significa Print()" << endl;
    cout << "8                 significa DEBUG()" << endl;

    while(cin >> n){
        switch (n)
        {
        case 1:
            cin >> new_t;
            Heap_cinetico.advance(new_t);
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
            cout << "terminei o 5" << endl;
            break;
        case 6:
            cin >> x;
            Heap_cinetico.delete_id(x);
            break;
        case 7:
            Heap_cinetico.print();
            break;
        case 8:
            Heap_cinetico.debug();
            break;
        };
    }

    return 0;
}
