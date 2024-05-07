#include<bits/stdc++.h>
using namespace std;

class Minheap{
    public:
    char data;
    int freq;
    Minheap *left,*right;

    public:
    Minheap(char data, int freq){
        this->data = data;
        this->freq = freq;

        left = right = NULL;
    }
};

struct compare{
    bool operator()(Minheap *l, Minheap *r){
        return (l->freq) > (r->freq);
    }
};

void printcodes(Minheap * node, string str){
    if(node == NULL){
        return;
    }

    if(node->data != '$'){
        cout << "Word : Code " << node->data << " " << str << endl;
    }

    printcodes(node->left,str+"0");
    printcodes(node->right,str+"1");
}

void huffmann(vector<pair<char,int>> codes){

    priority_queue<Minheap*,vector<Minheap*>,compare> pq;

    for(int i=0;i<codes.size();i++){
        Minheap * element = new Minheap(codes[i].first,codes[i].second);
        pq.push(element);
    }

    while(pq.size()!=1){
        Minheap * left = pq.top();
        pq.pop();

        Minheap * right = pq.top();
        pq.pop();

        int totalfreq = left->freq + right->freq;
        Minheap * temp = new Minheap('$',totalfreq);

        temp->left = left;
        temp->right = right;

        pq.push(temp);
    }

    printcodes(pq.top(),"");
}

int main(){
    int n; cin>>n;
    vector<pair<char,int>> codes;

    for(int i=0;i<n;i++){
        char c; int freq;
        cout << "Char : Freq ";
        cin>>c>>freq;
        codes.push_back({c,freq});
    }

    huffmann(codes);

}