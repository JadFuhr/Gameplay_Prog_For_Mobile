#pragma once
#include <iostream>
#include <queue>  // For level order traversal

using namespace std;

// TreeNode structure
struct TreeNode {
    int data;            // Value of the node
    TreeNode* left;      // Pointer to the left child
    TreeNode* right;     // Pointer to the right child

    // Constructor to create a new node
    TreeNode(int value) {
        data = value;
        left = right = nullptr;
    }
};

// BinaryTree class
class BinaryTree {
private:
    TreeNode* root;  // Pointer to the root node

public:
    // Constructor
    BinaryTree() {
        root = nullptr;
    }

    // Get the root (used for internal algorithms)
    TreeNode* getRoot() {
        return root;
    }

    // Insert a node (wrapper function for recursion)
    void insert(int value) {
        root = insertRec(root, value);
    }

    // Search for a value in the tree
    bool search(int value) {
        return searchRec(root, value);
    }

    // Delete a node from the tree
    void deleteNode(int value) {
        root = deleteRec(root, value);
    }

    // Get the height of the tree
    int height() {
        return heightRec(root);
    }

    // Traversal functions
    void inorder() {
        inorderRec(root);
        cout << endl;
    }

    void preorder() {
        preorderRec(root);
        cout << endl;
    }

    void postorder() {
        postorderRec(root);
        cout << endl;
    }

    void levelOrder();

private:
    // Recursive function to insert a node
    TreeNode* insertRec(TreeNode* node, int value);

    // Recursive function to search for a value
    bool searchRec(TreeNode* node, int value);

    // Recursive function to delete a node
    TreeNode* deleteRec(TreeNode* node, int value);

    // Recursive function to get the height of the tree
    int heightRec(TreeNode* node);

    // Traversal helper functions
    void inorderRec(TreeNode* node);
    void preorderRec(TreeNode* node);
    void postorderRec(TreeNode* node);
};

void BinaryTree::inorderRec(TreeNode* node) {
    if (node == nullptr)
        return;
    inorderRec(node->left);       // Visit left subtree
    cout << node->data << " ";    // Visit root node
    inorderRec(node->right);      // Visit right subtree
}


void BinaryTree::preorderRec(TreeNode* node) {
    if (node == nullptr)
        return;
    cout << node->data << " ";    // Visit root node
    preorderRec(node->left);      // Visit left subtree
    preorderRec(node->right);     // Visit right subtree
}


void BinaryTree::postorderRec(TreeNode* node) {
    if (node == nullptr)
        return;
    postorderRec(node->left);     // Visit left subtree
    postorderRec(node->right);    // Visit right subtree
    cout << node->data << " ";    // Visit root node
}

void BinaryTree::levelOrder() {
    if (root == nullptr) return;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        cout << current->data << " ";

        // Enqueue left and right children
        if (current->left != nullptr)
            q.push(current->left);
        if (current->right != nullptr)
            q.push(current->right);
    }
    cout << endl;
}


TreeNode* BinaryTree::insertRec(TreeNode* node, int value) {
    if (node == nullptr) {
        return new TreeNode(value);
    }

    // If value is less, go left; otherwise, go right
    if (value < node->data) {
        node->left = insertRec(node->left, value);
    }
    else {
        node->right = insertRec(node->right, value);
    }

    return node;
}


bool BinaryTree::searchRec(TreeNode* node, int value) {
    if (node == nullptr) {
        return false;
    }

    if (node->data == value) {
        return true;
    }

    if (value < node->data) {
        return searchRec(node->left, value);  // Search left
    }
    else {
        return searchRec(node->right, value); // Search right
    }
}


TreeNode* BinaryTree::deleteRec(TreeNode* node, int value) {
    if (node == nullptr) return node;

    // Traverse the tree to find the node to delete
    if (value < node->data) {
        node->left = deleteRec(node->left, value);
    }
    else if (value > node->data) {
        node->right = deleteRec(node->right, value);
    }
    else {
        // Node found, handle the deletion cases
        if (node->left == nullptr) {
            TreeNode* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            TreeNode* temp = node->left;
            delete node;
            return temp;
        }

        // Node with two children, find the inorder successor
        TreeNode* temp = node->right;
        while (temp && temp->left != nullptr) {
            temp = temp->left;
        }

        // Copy inorder successor's data to this node
        node->data = temp->data;

        // Delete the inorder successor
        node->right = deleteRec(node->right, temp->data);
    }

    return node;
}


int BinaryTree::heightRec(TreeNode* node) {
    if (node == nullptr)
        return 0;
    int leftHeight = heightRec(node->left);
    int rightHeight = heightRec(node->right);
    return 1 + max(leftHeight, rightHeight);
}


