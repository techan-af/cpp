#include<bits/stdc++.h>
using namespace std;
#define MAX 50

class Node{
    public:
    int data;
    Node *left,*right;

    Node(int d){
        data = d;
        left = right = NULL;
    }
};

Node * construct(int r[][MAX],int i,int j){
    if(!r[i][j]){
        return NULL;
    }

    Node * root = new Node(r[i][j]);
    root->left = construct(r,i,r[i][j]-1);
    root->right = construct(r,r[i][j]+1,j);

    return root;
}

Node * obst(vector<int> p,vector<int> q,int n){
    int w[MAX][MAX], c[MAX][MAX], r[MAX][MAX];

    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            w[i][j] = c[i][j] = r[i][j] = 0;
        }
    }

    for(int i=1;i<=n;i++){
        w[i][i] = q[i-1] + p[i] + q[i];
        c[i][i] = w[i][i];
        r[i][i] = i;
    }

    for(int size = 2;size<=n;size++){
        for(int i=1;i+size-1 <=n ;i++){
            int j = i+size -1;
            w[i][j] = w[i][j-1] + p[j] + q[j];
            c[i][j] = INT_MAX;
            for(int k=i;k<=j;k++){
                int cost = w[i][j] + c[i][k-1] + c[k+1][j];
                if(c[i][j] > cost){
                    c[i][j] = cost;
                    r[i][j] = k;
                }
            }
        }
    }

    cout << "COST IS : " << c[1][n] << endl;

    cout << "Weight " << endl;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            cout << w[i][j] << " ";
        }
        cout << endl;
    }

    cout << "cost " << endl;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            cout << c[i][j] << " ";
        }
        cout << endl;
    }

    cout << "root " << endl;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            cout << r[i][j] << " ";
        }
        cout << endl;
    }

    return construct(r,1,n);
}

void inorder(Node * root, vector<string> words){
    if(root == NULL){
        return ;
    }

    cout << words[root->data] << " ";
    inorder(root->left,words);
    inorder(root->right,words);
}


int main(){

    int n; cin>>n;
    vector<string> words(n+1);
    for(int i=1;i<=n;i++) cin>>words[i];

    vector<int> p(n+1);
    for(int i=1;i<=n;i++) cin>>p[i];

    vector<int> q(n+1);
    for(int i=0;i<=n;i++) cin>>q[i];

    Node * root = obst(p,q,n);

    inorder(root,words);
}