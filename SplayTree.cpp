#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class Node{
    public:
        int val;
        int priority;

        Node *parent;
        Node *esq;
        Node *dir;

        Node() { 
            parent = nullptr;
            esq = nullptr;
            dir = nullptr;
        }
        Node(int val){
            this->parent = nullptr;
            esq = nullptr;
            dir = nullptr;
            this->val = val;
        }
        Node(int val, Node* dad){
            this->parent = dad;
            esq = nullptr;
            dir = nullptr;
            this->val = val;
        }
        ~Node(){
            /* if(esq != nullptr){
                delete esq;
            }
            if(dir != nullptr){
                delete dir;
            } */
        }
};

class SplayTree {
    private: 
        Node *raiz;

        Node* right_rotation(Node *node){
            Node *new_root = node->esq;
            Node *son = new_root->dir;

            new_root->dir = node;
            node->esq = son;

            return new_root;
        }

        Node* left_rotation(Node *node){
            Node *new_root = node->dir;
            Node *son = new_root->esq;

            new_root->esq = node;
            node->dir = son;

            return new_root;
        }

        void add(Node *node,int val){
            if(node->val > val){ //vai pra esquerda!
                if(node->esq == nullptr){
                    //achou!!
                    Node *new_node = new Node(val,node);
                    node->esq = new_node;
                    splay(node->esq);
                }
                else{
                    add(node->esq,val);
                }
            } 
            else{ //vai pra direita!!
                if(node->dir == nullptr){
                    //achou!!
                    Node *new_node = new Node(val,node);
                    node->dir = new_node;
                    splay(node->dir);
                }
                else{
                    add(node->dir,val);
                }
            }
        }

        Node* remove_rec(Node *node,int val){
            if(node == nullptr){
                return nullptr;
            }
            if(node->val == val){
                //tratamento de deleção;
                if(node->dir == nullptr){
                    return node->esq;
                }
                else if(node->esq == nullptr){
                    return node->dir;
                }
                if(node->dir->priority > node->esq->priority){ // direita sobe
                    Node *new_node = left_rotation(node);
                    new_node->esq = remove_rec(new_node->esq, val);
                    return new_node;
                }
                else{
                    Node *new_node = right_rotation(node);
                    new_node->dir = remove_rec(new_node->dir, val);
                    return new_node;
                }
            }
            else if(node->val > val){ //vá pra esquerda!
                node->esq = remove_rec(node->esq, val);
                return node;
            }
            else{ //vá pra direita!
                node->dir = remove_rec(node->dir, val);
                return node;
            }
        }

        void debug_rec(Node *u, int i){
            if(u->esq != nullptr){
                debug_rec(u->esq, i+3);
            }

            for(int j=0;j<i;j++){
                cout << " ";
            }
            cout << u->val << " ";
            cout << endl;

            if(u->dir != nullptr){
                debug_rec(u->dir, i+3);
            }
        } 

        int min(Node *u){
            if(u->esq == nullptr){
                return u->val;
            }
            return min(u->esq);
        }

        bool search(Node *u, int x){
            if(u == nullptr){
                return false;
            }
            if(u->val == x){
                splay(u);
                return true;
            }
            else if(u->val > x){
                return search(u->esq,x);
            }
            else{
                return search(u->dir,x);
            }
        }

        void splay(Node *u){
            if(u->parent == nullptr){
                return;
            }
            if(u->parent->parent == nullptr){ //filho da raiz!
                //rotação única!
                if(u->parent->esq == u){
                    //roda pra direita
                }
                else{
                    //roda pra esquerda
                }
            }
            if(u == u->parent->esq && u->parent == u->parent->parent->esq){
                //caso / pagina 14.
            }
            if(u == u->parent->esq && u->parent == u->parent->parent->dir){
                //análogo \ / pagina 15.
            }
            if(u == u->parent->dir && u->parent == u->parent->parent->dir){
                //análogo \ pagina 14.
            }
            if(u == u->parent->dir && u->parent == u->parent->parent->esq){
                //caso / \ pagina 15.
            }
            splay(u);
        }

    public:
        SplayTree() {
            raiz = nullptr;
        }
        ~SplayTree() {
            delete raiz;
        }

        void insert(int t){
            if(raiz == nullptr){
                raiz = new Node(t);
            }
            else{
                add(this->raiz, t);
            }   
        }

        void remove(int val){
            this->raiz = remove_rec(this->raiz, val);
        }

        void print(){
            debug_rec(this->raiz,0);
        }

        int print_min(){
            if(raiz == nullptr){
                cout << "Treap vazia!" << endl;
                return -1;
            }
            return min(this->raiz);
        }

        int print_search(int x){
            return (search(this->raiz, x)? 1 : 0);
        }
};

int main(){
    int numero, x;
    SplayTree *ST = new SplayTree(); 

    while(cin >> numero){
        switch (numero)
        {
        case 1:
            cin >> x;
            ST->insert(x);
            break;
        case 2:
            cin >> x;
            //ST->delete(x);
            break;
        case 3:
            cin >> x;
            ST->print_search(x);
            break;
        case 4:
            cout << ST->print_min() << endl;;
            break;
        case 5:
            ST->print();
            break;
        }
    }
}
