#include "Header.h"

int main() {
    BinaryTree tree;

    // Insert nodes
    tree.insert(50);
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(70);
    tree.insert(60);
    tree.insert(80);

    // Traversals
    cout << "Inorder Traversal: ";
    tree.inorder();  // Expected: 20 30 40 50 60 70 80

    cout << "Preorder Traversal: ";
    tree.preorder();  // Expected: 50 30 20 40 70 60 80

    cout << "Postorder Traversal: ";
    tree.postorder();  // Expected: 20 40 30 60 80 70 50

    cout << "Level Order Traversal: ";
    tree.levelOrder();  // Expected: 50 30 70 20 40 60 80

    // Search for a value
    int key = 40;
    if (tree.search(key))
        cout << key << " found in the tree." << endl;
    else
        cout << key << " not found in the tree." << endl;

    // Delete a node
    tree.deleteNode(30);
    cout << "Inorder Traversal after deleting 30: ";
    tree.inorder();  // Expected: 20 40 50 60 70 80

    // Height of tree
    cout << "Height of tree: " << tree.height() << endl;

    return 0;
}
