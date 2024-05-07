#include<bits/stdc++.h>
using namespace std;

class node{

    public:
    int data;
    node *left,*right;

    node(){
        data = -1;
        left = right = NULL;
    }

    node(int val){
        data = val;
        left = right = NULL;
    }

};

void insertintobst(node * &root,int key){
    if(root == NULL){
        node * temp = new node(key);
        root = temp;
        return;
    }

    if(key > root->data){
        insertintobst(root->right,key);
    }else if(key < root->data){
        insertintobst(root->left,key);
    }else{
        cout << "duplicate" << endl;
        return;
    }
}

void insertintobstiterative(node* &root, int key){
    node * temp = new node(key);
    if(root == NULL){
        root = temp;
        return;
    }

    node * curr = root;
    node * parent = NULL;
    while(curr != NULL){
        parent = curr;
        if(key > curr->data){
            curr = curr->right;
        }else{
            curr = curr->left;
        }
    }

    if(parent->data > key){
        parent->left = temp;
    }else{
        parent->right = temp;
    }
}

void inorder_recursive(node* root){
    if(root == NULL){
        return ;
    }

    inorder_recursive(root->left);
    cout << root->data << " ";
    inorder_recursive(root->right);
}

void preorder_recursive(node* root){
    if(root == NULL){
        return ;
    }

    cout << (root->data) << " ";
    preorder_recursive(root->left);
    preorder_recursive(root->right);
}

void postorder_recursive(node* root){
    if(root == NULL){
        return ;
    }

    postorder_recursive(root->left);
    postorder_recursive(root->right);
    cout << (root->data) << " ";
}

void inorder_iterative(node* root){
    stack<node *> st;
    node* r = root;
    while(r != NULL || st.size()!=0){
        while(r!=NULL){
            st.push(r);
            r = r->left;
        }
        r = st.top();
        st.pop();

        cout << r->data << " ";
        r=r->right;
    }

}

void preorder_iterative(node* root){
    stack<node *> st;
    node* r = root;
    while(r != NULL || st.size()!=0){
        while(r!=NULL){
            cout << r->data << " ";
            st.push(r);
            r = r->left;
        }

        r = st.top();
        st.pop();

        r=r->right;
    }
}

void postorder_iterative(node* root){
    stack<node *> s1,s2;
    node * temp = NULL;
    s1.push(root);

    while(s1.size()!=0){
        temp = s1.top();
        s1.pop();

        s2.push(temp);
        if(temp->left) s1.push(temp->left);
        if(temp->right) s1.push(temp->right);
    }

    while(s2.size()!=0){
        temp = s2.top();
        s2.pop();

        cout << temp->data << " ";
    }

}

node * helperfunction(vector<int> &inorder,vector<int> &preorder,int inS, int inE, int preS, int preE ){
    if(preS > preE || inS > inE){
        return NULL;
    }

    node * root = new node(preorder[preS]);
    int inI = 0;
    for(int i=inS;i<=inE;i++){
        if(inorder[i] == preorder[preS]){
            inI = i;
        }
    }

    int leftsubtreesize = inI-inS;
    root->left = helperfunction(inorder,preorder,inS,inI-1,preS+1,preS+inI);
    root->right = helperfunction(inorder,preorder,inI+1,inE,preS+inI+1,preE);

    return root;
}

node * treefrominorderpreorder(vector<int> inorder,vector<int> preorder){
    node * root = helperfunction(inorder,preorder,0,inorder.size()-1,0,preorder.size()-1);
    return root;
}

int main(){

    node * root = NULL;
    insertintobst(root,4);
    insertintobst(root,7);
    insertintobst(root,5);
    insertintobstiterative(root,1);
    inorder_recursive(root);
    cout << endl;
    preorder_recursive(root);
    cout << endl;
    postorder_recursive(root);
    cout << endl;
    inorder_iterative(root);
    cout << endl;
    preorder_iterative(root);
    cout << endl;
    postorder_iterative(root);
    cout << endl;

    vector<int> inorder={4,2,7,5,1,8,6,3};
    vector<int> preorder={1,2,4,5,7,3,6,8};

    node * tree = treefrominorderpreorder(inorder,preorder);
    inorder_recursive(tree);

}