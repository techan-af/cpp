#include<bits/stdc++.h>
using namespace std;

class node{
    public:
    int data;
    int height;
    node *left,*right;

    public:
    node(int d){
        data = d;
        left = right = NULL;
        height = 1;
    }
};

int height(node * root){
    if(root == NULL){
        return 0;
    }

    return root->height;
}

int getbalance(node * root){
    if(root == NULL){
        return 0;
    }

    return height(root->left) - height(root->right);
}

node * rightrotate(node * x){
    node * y = x->left;
    node * t2 = y->right;

    // rotation
    y->right = x;
    x->left = t2;

    y->height = 1 + max(height(y->left),height(y->right));
    x->height = 1 + max(height(x->left),height(x->left));

    return y;
}

node * leftrotate(node * x){
    node * y = x->right;
    node * t2 = y->left;

    // rotatation
    y->left = x;
    x->right = t2;

    y->height = 1 + max(height(y->left),height(y->right));
    x->height = 1 + max(height(x->left),height(x->left));

    return y;

}

node * insert(node * root,int data){

    if(root == NULL){
        return new node(data);
    }

    if(data < root->data){
        root->left = insert(root->left,data);
    }else if(data > root->data){
        root->right = insert(root->right,data);
    }else{
        root->data = data;
        return root;
    }

    root->height = 1 + max(height(root->left),height(root->right));
    int balance = getbalance(root);

    //ll
    if(balance > 1 && data < root->left->data){
        return rightrotate(root);
    }

    //rr
    if(balance < -1 && data > root->right->data){
        return leftrotate(root);
    } 

    //lr
    if(balance > 1 && data > root->left->data){
        root->left = leftrotate(root->left);
        return rightrotate(root);
    }

    //rl
    if(balance < -1 && data < root->right->data){
        root->right = rightrotate(root->right);
        return leftrotate(root);
    }

    return root;
}

void levelorder(node * root){
    if(root == NULL){
        return;
    }

    cout << "level" << endl;
    queue<node*> q;
    q.push(root);

    while(!q.empty()){
        node * temp = q.front();
        q.pop();

        cout << temp->data << " ";
        if(temp->left) q.push(temp->left);
        if(temp->right) q.push(temp->right);
    }

    cout << endl;
}

void preorder(node* root){
    if(root == NULL){
        return ;
    }

    cout << (root->data) << " ";
    preorder(root->left);
    preorder(root->right);
}

int main(){

    node * root = NULL;
    root = insert(root, 10);  
    root = insert(root, 20);  
    root = insert(root, 30);  
    root = insert(root, 40);  
    root = insert(root, 50);  
    root = insert(root, 25);  

    cout << "height is " << height(root) << endl;

    cout <<"=========" << endl;
    levelorder(root);
    cout << "=========" << endl;
    preorder(root);
}