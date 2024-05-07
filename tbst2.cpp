#include <bits/stdc++.h>
using namespace std;

/* Structure of a node in double-threaded binary tree */
struct Node {
    int key;
    Node* left;
    Node* right;

    // Flags to indicate whether the left and right pointers are threads
    bool isLeftThreaded;
    bool isRightThreaded;

    Node(int key) : key(key), left(nullptr), right(nullptr), isLeftThreaded(false), isRightThreaded(false) {}
};

/* Utility function to create a new node */
Node* newNode(int key) {
    return new Node(key);
}

/* Function to create double-threaded binary tree */
void createDoubleThreaded(Node* root) {
    // Base cases
    if (root == nullptr)
        return;

    // Convert the left subtree
    if (root->left) {
        createDoubleThreaded(root->left);

        // Find predecessor (rightmost child in left subtree)
        Node* pred = root->left;
        while (pred->right && !pred->isRightThreaded) {
            pred = pred->right;
        }

        // Create left thread from root to predecessor
        pred->right = root;
        pred->isRightThreaded = true;

        // Create right thread from root to predecessor
        root->left = pred;
        root->isLeftThreaded = true;
    }

    // Convert the right subtree
    if (root->right) {
        createDoubleThreaded(root->right);

        // Find successor (leftmost child in right subtree)
        Node* succ = root->right;
        while (succ->left && !succ->isLeftThreaded) {
            succ = succ->left;
        }

        // Create right thread from root to successor
        root->right = succ;
        root->isRightThreaded = true;

        // Create left thread from root to successor
        succ->left = root;
        succ->isLeftThreaded = true;
    }
}

/* Utility function to find the leftmost node */
Node* leftMost(Node* root) {
    while (root != nullptr && root->left && !root->isLeftThreaded) {
        root = root->left;
    }
    return root;
}

/* Function to perform inorder traversal of a double-threaded binary tree */
void inOrder(Node* root) {
    if (root == nullptr) return;

    // Find the leftmost node in the tree
    Node* current = leftMost(root);

    while (current != nullptr) {
        // Print the current node
        cout << current->key << " ";

        // If the right pointer is a thread, go to the inorder successor
        if (current->isRightThreaded) {
            current = current->right;
        } else {
            // Otherwise, go to the leftmost child in the right subtree
            current = leftMost(current->right);
        }
    }
}

/* Main function */
int main() {
    // Create a sample binary tree
    /*        1
           /   \
         2       3
        / \     / \
       4   5   6   7 */
    Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);

    // Convert the tree into a double-threaded binary tree
    createDoubleThreaded(root);

    // Perform inorder traversal of the double-threaded tree
    cout << "Inorder traversal of double-threaded tree:\n";
    inOrder(root);
    cout << endl;

    return 0;
}
