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

void inorder(node* root){
    if(root == NULL){
        return ;
    }

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(node* root){
    if(root == NULL){
        return ;
    }

    cout << (root->data) << " ";
    inorder(root->left);
    inorder(root->right);
}

void postorder(node* root){
    if(root == NULL){
        return ;
    }

    inorder(root->left);
    inorder(root->right);
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

int mini(node* root){
    if(root->left == NULL ){
        return root->data;
    }

    mini(root->left);
}

int maxi(node* root){
    if(root->right == NULL ){
        return root->data;
    }

    maxi(root->right);
}

node* deletenode(node* root,int key){
    if(root == NULL){
        return root;
    }

    if(root->data == key){
        // 0 child 
        if(root->left == NULL and root->right == NULL){
            delete root;
            return NULL;
        }
        // 1 child

        if(root->left !=NULL and root->right == NULL){
            node* temp = root->left;
            delete root;
            return temp;
        }

        if(root->left == NULL and root->right != NULL){
            node * temp = root->right;
            delete root;
            return temp;
        }

        // 2 child
        if(root->left and root->right){
            int min_val = mini(root->right);
            root->data = min_val;
            root->right = deletenode(root->right,min_val);

            return root;
        }

    }else if(root->data > key){
        // left 
        root->left = deletenode(root->left,key);
        return root;
    }else{
        // right
        root->right = deletenode(root->right,key);
        return root;
    }
}


int main(){

    node * root = NULL;
    insertintobst(root,4);
    insertintobst(root,7);
    insertintobst(root,5);
    insertintobstiterative(root,1);
    inorder(root);
    cout << endl;
    preorder(root);
    cout << endl;
    postorder(root);
    cout << endl;
    inorder_iterative(root);
    cout << endl;
    preorder_iterative(root);
    cout << endl;
    postorder_iterative(root);
    cout << endl;

}