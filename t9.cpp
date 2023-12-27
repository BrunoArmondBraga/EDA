#include <vector>
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <stack>

using namespace std;

class Node{
public:
    int n;
    int counter = 1;
    int number_of_children = 0;
    int suffix_index = -1;
    int start = -1;
    int end = -1;

    int number_of_descendants = 0;
    vector<int> descendants;

    Node* children[128];
    string letters = "";

    Node(int t){
        n = t;
        if(t == -1){
            number_of_descendants = 1;
        }
    }

    void add_children(Node* child){
        children[number_of_children] = child;
        number_of_children++;
    }
};

bool compare_suffix(int a, int b, string s){ //a é menor que b?
    int index1 = a;
    int index2 = b;

    int i = 0;
    
    while(true){
        if(s[index1 + i] == '$'){
            return true;
        }
        if(s[index2 + i] == '$'){
            return false;
        }
        if(s[index1 + i] < s[index2 + i]){
            return true;
        }
        if(s[index2 + i] < s[index1 + i]){
            return false;
        }
        i++;
    }
}

void merge(std::vector<int>& arr, int left, int middle, int right, string word) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    std::vector<int> leftSubarray(n1);
    std::vector<int> rightSubarray(n2);

    for (int i = 0; i < n1; i++) {
        leftSubarray[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightSubarray[j] = arr[middle + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left; 

    while (i < n1 && j < n2) {
        if (compare_suffix(leftSubarray[i],rightSubarray[j], word)) {
            arr[k] = leftSubarray[i];
            i++;
        } else {
            arr[k] = rightSubarray[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftSubarray[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightSubarray[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int>& arr, int left, int right, string word) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        mergeSort(arr, left, middle, word);
        mergeSort(arr, middle + 1, right, word);

        merge(arr, left, middle, right, word);
    }
}

int compare_two_strings(int a, vector<int> suffix_vector, string s){
    int i = 0;
    int length = 0;
    while(true){
        if(s[suffix_vector[a] + i] != s[suffix_vector[a + 1] + i])
            break;
        length++;
        i++;
    }
    return length;
}

vector<int> create_lcp_vector(vector<int> suffix_vector, string s){
    int n = suffix_vector.size();
    vector<int> lcp;

    for(int i = 0; i < n - 1; i++){
        lcp.push_back(compare_two_strings(i, suffix_vector, s));
    }
    return lcp;
}

void compare(int& L, int& R, int& l, int& r, int M, int init, vector<int> lcp, string p, string text, bool is_suc){
    int index = init;
    int first_letter_suffix = lcp[M];

    while(true){        
        if(index == p.size()){
            if(is_suc){
                L = M;
                l = index;
                break;
            }
            else{
                R = M;
                r = index;
                break;
            }
        }
        
        if(p[index] == text[first_letter_suffix + index]){
            index++;
        }
        else if(p[index] > text[first_letter_suffix + index]){
            L = M;
            l = index;
            break;
        }
        else{
            R = M;
            r = index;
            break;
        }
    }
    return;
}

void put_edges_rec(vector<int> VS, Node* root, int& i, int depth_index){
    if(root == nullptr) return;
    
    int index = depth_index + root->n;

    int size = root->counter + 1;
    //int current = i - VS.size() + 1;
    for(int j = size - 1; j >= 0; j--){
        if(root->children[j] == nullptr){
            root->children[j] = new Node(-1);
            root->children[j]->suffix_index = VS[i];
            root->children[j]->start = VS[i] + root->n;
            root->children[j]->end = VS.size() - 2;
            i--;
        }
        else{
            put_edges_rec(VS, root->children[j], i, depth_index + root->n);
        }
        root->number_of_descendants += root->children[j]->number_of_descendants;
    }

    root->end = root->children[1]->start - 1; //isso está errado para pais com mais de 2 filhos!
    root->start = root->end - (root->n - depth_index) + 1;

}

char get_first_letter(int VS, int start, string text){
    if(start == -1){
        return text[0];
    }
    return text[VS + start];
}

string get_interval_letters(const string& str, int start, int end){
    if (start < 0 || start >= str.length() || end + 1 <= start || end > str.length()) {
        return "";
    }
    return str.substr(start, end + 1 - start);
}

void fix_vectors_rec(vector<int> VS, Node* root, string text, int& i){
    int size = root->counter + 1;

    for(int j = size - 1; j >= 0; j--){
        char first_letter = get_first_letter(VS[i], root->n, text);
        root->children[first_letter] = root->children[j];
        root->children[j] = nullptr;

        root->descendants.push_back(first_letter);

        //string interval = get_interval_letters(text, root->children[first_letter]->start + 1, root->children[first_letter]->end);
        //root->children[first_letter]->letters = interval;
        //root->children[first_letter]->letters = get_interval_letters(text, root->children[first_letter]->start + 1, root->children[first_letter]->end);
        
        if(root->children[first_letter]->n != -1){
            fix_vectors_rec(VS, root->children[first_letter], text, i);
        }
        else{
            i--;
        }

    }
}

Node* make_tree(vector<int> VS, vector<int> LCP, string text){
    stack<Node*> minhaPilha;
    minhaPilha.push(new Node(LCP[1]));
    minhaPilha.top()->add_children(nullptr);

    for(int i = 2; i < LCP.size(); i++){
        int current = LCP[i];
        Node* new_node = new Node(current);
        Node* aux = nullptr;

        if(!minhaPilha.empty() && minhaPilha.top()->n > new_node->n){
            aux = minhaPilha.top();
            minhaPilha.pop();
        }

        while(!minhaPilha.empty()){
            if(minhaPilha.top()->n == new_node->n){
                minhaPilha.top()->add_children(aux);
                minhaPilha.top()->counter++;
                aux = nullptr;
                delete new_node;
                break;
            }
            else if(minhaPilha.top()->n < new_node->n){
                new_node->add_children(aux);
                aux = nullptr;
                minhaPilha.push(new_node);
                break;
            }
            else{
                minhaPilha.top()->add_children(aux);
                aux = minhaPilha.top();
                minhaPilha.pop();
            }
        }

        if(aux != nullptr){
            cout << "algo deu problema!" << endl;
        }
    }

    
    while(minhaPilha.size() > 1){
        Node* aux = minhaPilha.top();
        minhaPilha.pop();
        minhaPilha.top()->add_children(aux);
    }

    int recursive_stack = VS.size() - 1;
    put_edges_rec(VS, minhaPilha.top(),recursive_stack, 0);

    recursive_stack = VS.size() - 1;
    fix_vectors_rec(VS, minhaPilha.top(), text, recursive_stack);


    return minhaPilha.top();
}

void print_descendants(Node* root){
    for(int i = 0; i < root->descendants.size(); i++){
        if(root->children[root->descendants[i]]->n == -1){
            cout << root->children[root->descendants[i]]->suffix_index << " ";
        }
        else{
            print_descendants(root->children[root->descendants[i]]);
        }
    }
}


int number_of_occurences(Node* tree, string searched_word, bool is_printing, string text){
    //tem problema para casos de occurences sem prefixo intermediário

    Node* current_node = tree;
    int current_letter = 0;

    while(true){
        if(current_node->children[searched_word[current_letter]] == nullptr){
            return 0;
        }
        else{
            current_node = current_node->children[searched_word[current_letter]];
            current_letter++;

            int index_to_compare = current_node->letters.size();

            for(int i = 0; i < index_to_compare; i++){
                if(current_letter == searched_word.size()){
                    if(is_printing){
                        print_descendants(current_node);
                        cout << endl;
                    }
                    return current_node->number_of_descendants;
                }

                if(current_node->letters[i] != searched_word[current_letter]){
                    return 0;
                }
                else{
                    current_letter++;
                }
            }
            if(current_letter == searched_word.size()){
                if(is_printing){
                    print_descendants(current_node);
                    cout << endl;
                }
                return current_node->number_of_descendants;
            }
        }
    }
}

void put_VS_rec(Node* root, vector<int>& VS){
    for(int i = root->descendants.size() - 1; i >= 0; i--){
        int current_index = root->descendants[i];
        if(root->children[current_index]->n == -1){
            VS.push_back(root->children[current_index]->suffix_index);
        }
        else{
            put_VS_rec(root->children[current_index], VS);
        }
    }
}

vector<int> make_VS(Node* tree){
    vector<int> VS;
    VS.push_back(-1);

    put_VS_rec(tree, VS);
    return VS;
}



vector<int> make_LCP(Node* tree){
    vector<int> LCP;

    //put_LCP_rec();

    return LCP;
}

int main(){
    int numero, x;
    int fim, começo;
    string texto, palavra, nome_arq;
    vector<int> VS;
    vector<int> LCP;
    ifstream arquivo;
    char caractere;
    Node* current_tree = nullptr;

    while(cin >> numero){
        switch (numero)
        {
        case 1:
        {
            VS.clear();
            LCP.clear();

            cin >> texto;
            texto = texto + '$';
            VS.push_back(-1);
            for(int i = 0; i < texto.size(); i++){
                VS.push_back(i);
            }

            mergeSort(VS, 1, VS.size() - 1, texto);

            LCP = create_lcp_vector(VS, texto);


            current_tree = make_tree(VS, LCP, texto);
            break;
        }
        case 2:
            VS.clear();
            LCP.clear();

            cin >> nome_arq;
            texto = "";

            arquivo.open(nome_arq);
            if(arquivo.is_open()){
                while(arquivo.get(caractere)){
                    texto += caractere;
                }
                arquivo.close();
            }

            texto = texto + '$';
            VS.push_back(-1);
            for(int i = 0; i < texto.size(); i++){
                VS.push_back(i);
            }

            mergeSort(VS, 1, VS.size() - 1, texto);

            LCP = create_lcp_vector(VS, texto);
            current_tree = make_tree(VS, LCP, texto);

            break;

        case 3:
            cin >> palavra;
            if(number_of_occurences(current_tree, palavra, false, texto) > 0){
                cout << "True" << endl;
            }
            else{
                cout << "False" << endl;
            }
            break;
            
        case 4:
            cin >> palavra;
            number_of_occurences(current_tree, palavra, true, texto);
            break;
        case 5:
            cin >> palavra;
            cout << number_of_occurences(current_tree, palavra, false, texto) << endl;
            break;
        case 6:
            cout << "VS:  ";
            for(int i = 1; i < VS.size(); i++){
                cout << VS[i] << " ";
            }
            cout << endl;

            cout << "LCP:  ";
            for(int i = 1; i < LCP.size(); i++){
                cout << LCP[i] << " ";
            }
            cout << endl;
            break;
        case 7:
        {
            vector<int> VS = make_VS(current_tree);
            for(int i = 0; i < VS.size(); i++){
                cout << VS[i] << " ";
            }
            cout << endl;

            vector<int> LCP = make_LCP(current_tree);
            for(int i = 0; i < LCP.size(); i++){
                cout << LCP[i] << " ";
            }
            cout << endl;
        }
        }
    }
}
