#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>

using namespace std;

class Node{       
    public:
        Node *esq;
        Node *dir;

        int num_esq;
        bool esq_aberta;
        int num_dir;
        bool dir_aberta;

        vector<int> segmentos;

        Node() {
            esq = nullptr;
            dir = nullptr;
        };

        Node(int v) { 
            esq = nullptr;
            dir = nullptr;
        };
        
        ~Node() {
            if(esq != nullptr){
                delete esq;
            }
            if(dir != nullptr){
                delete dir;
            }
        }

        void print_segmentos(){
            if(segmentos.size() != 0){
                cout << " ";
            }
            for(int i = 0; i < segmentos.size(); i++){
                cout << segmentos[i] << " ";
            }
        }
};
 
class StaticSegmentedTree {
    private:

        void create_tree(int t){
            int x = 1;
            while(x*2 < t){
                x = x * 2;
            }
            int resto = t - x;
            this->root = create_tree_skeleton(x);
            put_leafs(this->root, resto);
        }

        Node* create_tree_skeleton(int t){
            if (t == 1) { //ISSO É UMA FOLHA!!
                return new Node(1);
            }

            int leftLeaves = (int) t / 2;
            int rightLeaves = t - leftLeaves;

            Node* root = new Node(leftLeaves + 1);
            root->esq = create_tree_skeleton(leftLeaves);
            root->dir = create_tree_skeleton(rightLeaves);

            return root;
        }

        void put_leafs(Node *node, int& t){
            if(t <= 0){
                return;
            }

            if(node->esq != nullptr){
                put_leafs(node->esq,t);
            }
            else{
                node->esq = new Node();
            }

            if(node->dir != nullptr){
                put_leafs(node->dir,t);
            }
            else{
                if(t > 0){
                    node->dir = new Node();
                    t = t - 1;
                }
            }
        }

        void print_debug_segmentos(vector<int> segmentos){
            for (int i = 0; i < segmentos.size(); i++) {
                cout << segmentos[i] << " ";
            }
            cout << endl;
        }

        void debug_rec_filling(Node *u, int i){
            if(u->esq != nullptr){
                debug_rec_filling(u->esq, i+3);
            }

            for(int j=0;j<i;j++){
                cout << " ";
            }
            if(u->esq_aberta){
                cout << "(";
            }
            else{
                cout << "[";
            }
            if(u->num_esq == INT_MIN){
                cout << "-inf";
            }
            else{
                cout << u->num_esq;
            }
            cout << ",";
            if(u->num_dir == INT_MAX){
                cout << "+inf";
            }
            else{
                cout << u->num_dir;
            }
            if(u->dir_aberta){
                cout << ")";
            }
            else{
                cout << "]";
            }
            u->print_segmentos();
            cout << endl;


            if(u->dir != nullptr){
                debug_rec_filling(u->dir, i+3);
            }   
        }

        void numera_preenchendo(Node* node, int &index, vector<int> &segmentos){
            if(node->esq == nullptr && node->dir == nullptr){ //node == leaf
                if(index % 2 == 0){ //caso par
                    node->num_esq = segmentos[index/2];
                    node->num_dir = segmentos[(index/2)+1];
                    node->esq_aberta = true;
                    node->dir_aberta = true;
                }
                else{//caso impar
                    node->num_esq = segmentos[(index/2) + 1];
                    node->num_dir = segmentos[(index/2) + 1];
                    node->esq_aberta = false;
                    node->dir_aberta = false;
                }
                index++;
                return;
            }
            if(node->esq != nullptr){
                numera_preenchendo(node->esq, index, segmentos);
            }
            if(node->dir != nullptr){
                numera_preenchendo(node->dir, index, segmentos);
            }
            node->num_esq = node->esq->num_esq;
            node->num_dir = node->dir->num_dir;
            node->esq_aberta = node->esq->esq_aberta;
            node->dir_aberta = node->dir->dir_aberta;
        }

        void put_segments(){
            for(int i = 0; i < intervalos.size()/2; i++){
                put_segment(this->root, intervalos[i*2], intervalos[(i*2)+1], i+1);
            }
        }

        void put_segment(Node* u, int a, int b, int name){
            if(u == nullptr || a > u->num_dir || b < u->num_esq){
                return;
            }

            if(a <= u->num_esq && b >= u->num_dir){
                u->segmentos.push_back(name);
                return;
            }

            put_segment(u->esq,a,b,name);
            put_segment(u->dir,a,b,name);
        }

        bool included(Node *u, int t){
            if(u == nullptr){
                return false;
            }

            if(u->dir_aberta){
                if(u->num_dir <= t){
                    return false;
                }
            }
            else{
                if(u->num_dir < t){
                    return false;
                }
            }

            if(u->esq_aberta){
                if(u->num_esq >= t){
                    return false;
                }
            }
            else{
                if(u->num_esq > t){
                    return false;
                }
            }
            return true;
        }

    public:
        Node *root;
        vector<int> intervalos;
        

        StaticSegmentedTree(vector<int> segments){
            intervalos = segments;
            vector<int> segmentos = segments;
            segmentos.push_back(INT_MIN);
            segmentos.push_back(INT_MAX);

            sort(segmentos.begin(), segmentos.end());
            segmentos.erase(unique(segmentos.begin(), segmentos.end()), segmentos.end());

            int number_of_different_extremes = 2 * (segmentos.size() - 2) + 1;
            create_tree(number_of_different_extremes);
            int a = 0;
            numera_preenchendo(this->root, a, segmentos);
            put_segments();
        }

        ~StaticSegmentedTree(){
            if(this->root != nullptr){
                delete root;
            }
        }

        void print(){
            debug_rec_filling(this->root,0);
        }

        void find_time(int t){
            vector<int> segments_in_time;
            Node *u = this->root;
            while(u != nullptr && u->num_esq <= t <= u->num_dir){
                if(u->segmentos.size() != 0){
                    for(int i = 0; i < u->segmentos.size(); i++){
                        segments_in_time.push_back(u->segmentos[i]);
                    }
                }
                if(included(u->esq,t)){
                    u = u->esq;
                }
                else{
                    u = u->dir;
                }
            }

            if(segments_in_time.size() == 0){
                cout << "nenhum segmento";
            }
            else{
                sort(segments_in_time.begin(), segments_in_time.end());
                for(int i = 0; i < segments_in_time.size(); i++){
                    cout << segments_in_time[i] << " ";
                }
            }
            cout << endl;
        }
};

int main(){
    int n;
    cin >> n;
    int a,b;
    vector<int> vec;
    for(int i=0; i<n; i++){
        cin >> a;
        cin >> b;
        vec.push_back(a);
        vec.push_back(b);
    }

    StaticSegmentedTree SST = StaticSegmentedTree(vec);
    while(cin >> n){
        switch (n)
        {
        case 1:
            cin >> a;
            SST.find_time(a);
            break;
        case 2:
            SST.print();
            break;
        };
    }
}