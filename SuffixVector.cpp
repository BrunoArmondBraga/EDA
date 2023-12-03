#include <vector>
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class VS{
    public:
        VS(){
            
        }

        bool search(){
            return true;
        }

        void occurences(){

        }

        int n_occurences(){
            return 0;
        }

        void print(){

        }
    private:

};

int min(int a, int b){
    if(a < b){
        return a;
    }
    return b;
}

bool comparare_suffix(int a, int b, string s){ //a é menor que b?
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
    //cout << "merge:  l= " << left << "  m= " << middle << "  r= " << right << endl; 
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Criar sublistas temporárias
    std::vector<int> leftSubarray(n1);
    std::vector<int> rightSubarray(n2);

    // Copiar dados para as sublistas temporárias
    for (int i = 0; i < n1; i++) {
        leftSubarray[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightSubarray[j] = arr[middle + 1 + j];
    }

    // Mesclar as sublistas temporárias de volta na lista original
    int i = 0; // Índice inicial da primeira sublista
    int j = 0; // Índice inicial da segunda sublista
    int k = left; // Índice inicial da lista mesclada

    while (i < n1 && j < n2) {
        if (comparare_suffix(leftSubarray[i],rightSubarray[j], word)) {
            arr[k] = leftSubarray[i];
            i++;
        } else {
            arr[k] = rightSubarray[j];
            j++;
        }
        k++;
    }

    // Copiar os elementos restantes da sublista esquerda, se houver
    while (i < n1) {
        arr[k] = leftSubarray[i];
        i++;
        k++;
    }

    // Copiar os elementos restantes da sublista direita, se houver
    while (j < n2) {
        arr[k] = rightSubarray[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int>& arr, int left, int right, string word) {
    //cout << "mergeSort:  l= " << left << "  r= " << right << endl;
    if (left < right) {
        // Encontrar o ponto médio da lista
        int middle = left + (right - left) / 2;

        // Chamar mergeSort recursivamente para as sublistas esquerda e direita
        mergeSort(arr, left, middle, word);
        mergeSort(arr, middle + 1, right, word);

        // Mesclar as sublistas ordenadas
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

void create_lrlcp(int i, int j, bool side_right, vector<int>& lcp, vector<int>& llcp, vector<int>& rlcp){
    int value;
    int m;
    if(i == j - 1){
        value = lcp[j];
    }
    else{
        m = (i + j) / 2;
        create_lrlcp(i, m, false, lcp, llcp, rlcp);
        create_lrlcp(m, j, true, lcp, llcp, rlcp);
        value = min(llcp[m], rlcp[m]);
    }
    if(side_right){
        rlcp[i] = value;
    }
    else{
        llcp[j] = value;
    }
}

void compare_suc(int& L, int& R, int& l, int& r, int M, int init, vector<int> lcp, string p, string text){
    cout << "L = (" << L << " , " << l << ")   ,   R = (" << R << " , " << r << ")   ,   M =  " << M << endl;

    int index = init;
    int first_letter_suffix = lcp[M];

    while(true){
        cout << "comparando " << p[index] << "  com  " << text[first_letter_suffix + index] << endl;
        /* if(index == p.size()){
            //acabou a palavra!!

            if(p[index] > text[first_letter_suffix + index]){}

            L = M;
            l = index;
            return;
        } */
        /* if(first_letter_suffix + index > text.size() - 1){
            //deu merda!
            return;
        } */

        if(index == p.size()){
            L = M;
            l = index;
            break;
            if(text[first_letter_suffix + index] == '$'){
                //R = M + 1;
                //L = R - 1;
            }
            else{
                //R = M;
                //r = index;
            }
            break;
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
    cout << "fui!" << endl;
    return;
}

int sucessor(string P, vector<int> lcp, vector<int> llcp, vector<int> rlcp, string T){

    int s = lcp[T.size()];
    int r = 0;

    while(r < P.size() && P[r] == T[s + r]){
        r++;
    }

    if(r == P.size() || P[r] > T[s + r]){
        return T.size() + 1;
    }

    /* if(r == P.size() && s + r + 1 == T.size()){
        return T.size() + 1;
    }
    if(r != P.size() && P[r] > T[s + r]){
        return T.size() + 1;
    } */
    


    int l = 0;
    int L = 1;
    int R = T.size();
    while(L < R - 1){

        int M = (L + R) / 2;

         if(l == r){
            //compara p e M a partir de l
            compare_suc(L,R, l, r, M, l, lcp, P, T);
        }


        else if(l > r){

            if(l < llcp[M - 1]){
                L = M ;
            }
            else if(llcp[M - 1] < l){
                R = M;
                r = llcp[M - 1];
            }
            else{
                //começa a comparar P e M de l
                compare_suc(L, R, l, r, M, l, lcp, P, T);
            }
        }

        else{

            if(r < rlcp[M-1]){
                R = M;
            }
            else if(rlcp[M-1] < r){
                L = M;
                l = rlcp[M-1];
            }
            else{
                //começa a comparar P e M de l
                compare_suc(L, R, l, r, M, r, lcp, P, T);
            }
        }
    }
    return R;
}

void compare_pred(int& L, int& R, int& l, int& r, int M, int init, vector<int> lcp, string p, string text){
    cout << "L = (" << L << " , " << l << ")   ,   R = (" << R << " , " << r << ")   ,   M =  " << M << endl;

    int index = init;
    int first_letter_suffix = lcp[M];

    while(true){
        cout << "comparando " << p[index] << "  com  " << text[first_letter_suffix + index] << endl;

        if(index == p.size()){
            R = M;
            r = index;
            break;
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
    cout << "fui!" << endl;
    return;
}

int predecessor(string P, vector<int> lcp, vector<int> llcp, vector<int> rlcp, string T){

    int s = lcp[2];
    int l = 0;

    while(l < P.size() && P[l] == T[s + l]){
        l++;
    }

    if(l == P.size() || P[l] < T[s + l]){
        return 1;
    }

    l = 0;
    int r = 0;
    int L = 1;
    int R = T.size();
    while(L < R - 1){

        int M = (L + R) / 2;

         if(l == r){
            //compara p e M a partir de l
            compare_pred(L,R, l, r, M, l, lcp, P, T);
        }


        else if(l > r){

            if(l < llcp[M - 1]){
                L = M ;
            }
            else if(llcp[M - 1] < l){
                R = M;
                r = llcp[M - 1];
            }
            else{
                //começa a comparar P e M de l
                compare_pred(L, R, l, r, M, l, lcp, P, T);
            }
        }

        else{

            if(r < rlcp[M-1]){
                R = M;
            }
            else if(rlcp[M-1] < r){
                L = M;
                l = rlcp[M-1];
            }
            else{
                //começa a comparar P e M de l
                compare_pred(L, R, l, r, M, r, lcp, P, T);
            }
        }
    }
    return L;
}

int main() {

    //string palavra = "abracadabra$";
    string palavra = "aaacctttgcgacc$";
    vector<int> inteiros;
    inteiros.push_back(-1);
    for(int i = 0; i < palavra.size(); i++){
        inteiros.push_back(i);
    }

    mergeSort(inteiros, 1, inteiros.size() - 1, palavra);


    for(int i = 0; i < inteiros.size(); i++){
        cout << inteiros[i] << " ";
    }
    cout << endl;
    

    vector<int> LCP = create_lcp_vector(inteiros, palavra);

    for(int i = 0; i < LCP.size(); i++){
        cout << LCP[i] << " ";
    }
    cout << endl;

    vector<int> llcp(LCP.size() - 1, 0);
    vector<int> rlcp(LCP.size() - 1, 0);

    cout << "lcp_size = " << LCP.size() << endl;

    create_lrlcp(0, LCP.size() - 1, true, LCP, llcp, rlcp);


    cout << "LLCP!" << endl;
    for(int i = 0; i < llcp.size(); i++){
        cout << llcp[i] << " ";
    }
    cout << endl;


    cout << "RLCP!" << endl;
    for(int i = 0; i < rlcp.size(); i++){
        cout << rlcp[i] << " ";
    }
    cout << endl;

    string teste;
    while(true){
        cin >> teste;
        int fim = sucessor(teste, inteiros, llcp, rlcp, palavra);
        cout << "sucessor = " << fim << endl;
        int pred = predecessor(teste, inteiros, llcp, rlcp, palavra);
        cout << "predecessor = " << pred << endl;
        cout << endl;
    }

    return 0;
}
