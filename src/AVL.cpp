#include "AVL.h"
#include <iostream>
#include <vector>
#include <regex>
using namespace std;

// Constructor definition for Node class
Node::Node(string name, string id)
    : name(name), id(id), height(1), left(nullptr), right(nullptr) {}  // Initialize node with name, id, height, and no children

// AVL constructor to initialize the root of the tree
AVL::AVL() {
    root = nullptr;  // Start with an empty tree
}
// Get the balance factor of a node, which is the difference in height between the left and right children
int Node::getBalanceFactor(Node* node) {
    if (node == nullptr) {
        return 0;  // Null nodes have a balance factor of 0
    }
    return nodeHeight(node->left) - nodeHeight(node->right);  // Difference between left and right subtree heights
}
// Get the height of a node
int Node::nodeHeight(Node* node) {
    if (node == nullptr) {
        return 0;  // Null nodes have height 0
    }
    return node->height;  // Return the node's stored height
}
// Update the height of a node after insertion, deletion, or rotation
int Node::updateNodeHeight(Node* node) {
    if (node == nullptr) {
        return 0;  // Null nodes have height 0
    }
    // Height is 1 plus the maximum height of the left and right children
    node->height = 1 + std::max(nodeHeight(node->left), nodeHeight(node->right));
    return node->height;
}
// Perform a left rotation around the given node
Node* AVL::rotateLeft(Node* node) {
    Node* newParent = node->right;  // New parent becomes the right child
    Node* grandChild = newParent->left;  // Save left child of the new parent
    newParent->left = node;  // Perform rotation
    node->right = grandChild;  // Reattach grandchild
    // Update heights after rotation
    node->updateNodeHeight(node);
    newParent->updateNodeHeight(newParent);

    return newParent;  // Return new root of this subtree
}
// Perform a right rotation around the given node
Node* AVL::rotateRight(Node* node) {
    Node* newParent = node->left;  // New parent becomes the left child
    Node* grandChild = newParent->right;  // Save right child of the new parent
    newParent->right = node;  // Perform rotation
    node->left = grandChild;  // Reattach grandchild
    // Update heights after rotation
    node->updateNodeHeight(node);
    newParent->updateNodeHeight(newParent);

    return newParent;  // Return new root of this subtree
}
// Perform a left-right rotation (double rotation)
Node* AVL::rotateLeftRight(Node* node) {
    node->left = rotateLeft(node->left);  // First perform left rotation on left child
    return rotateRight(node);  // Then perform right rotation
}
// Perform a right-left rotation (double rotation)
Node* AVL::rotateRightLeft(Node* node) {
    node->right = rotateRight(node->right);  // First perform right rotation on right child
    return rotateLeft(node);  // Then perform left rotation
}
// Helper function to insert a node into the AVL tree
void AVL::insertHelper(string id, string name) {
    bool flag = false;
    // Validate the name (only alphabetic characters and spaces are allowed)
    for (const char c : name) {
        if (!isalpha(c) && c != ' ') {
            cout << "unsuccessful" << endl;
            return;
        }
    }
    // Check if ID length is exactly 8 characters
    if (id.length() != 8) {
        cout << "unsuccessful" << endl;
        return;
    }
    // Insert the node, and handle duplicate IDs
    this->root = insert(this->root, name, id, flag);
    if (flag) {
        cout << "unsuccessful" << endl;  // Duplicate ID case
    } else {
        cout << "successful" << endl;  // Successful insertion
    }
}
// Rebalance a node if it becomes unbalanced
Node* AVL::rebalance(Node* node) {
    int balance = node->getBalanceFactor(node);
    // Left-heavy (balance > 1)
    if (balance > 1) {
        // Left-left case
        if (node->left != nullptr && node->left->getBalanceFactor(node->left) >= 0) {
            return rotateRight(node);
        }
        // Left-right case
        else {
            return rotateLeftRight(node);
        }
    }
    // Right-heavy (balance < -1)
    if (balance < -1) {
        // Right-right case
        if (node->right != nullptr && node->right->getBalanceFactor(node->right) <= 0) {
            return rotateLeft(node);
        }
        // Right-left case
        else {
            return rotateRightLeft(node);
        }
    }

    // Update height before returning the node
    node->updateNodeHeight(node);
    return node;  // No rotation needed
}
// Insert a new node with the given name and ID, and flag duplicates
Node* AVL::insert(Node* node, string name, string id, bool& flag) {
    if (node == nullptr) {
        flag = false;  // Insertion successful
        return new Node(name, id);  // Create and return new node
    }
    // Recursively insert into left or right subtree based on the lexicographical order of ID
    if (id > node->id) {
        node->right = insert(node->right, name, id, flag);
    } else if (id < node->id) {
        node->left = insert(node->left, name, id, flag);
    } else {
        flag = true;  // Duplicate ID found
        return node;  // No insertion for duplicates
    }
    // Update node height after insertion
    node->updateNodeHeight(node);
    // Rebalance the node if necessary
    return rebalance(node);
}
// Helper function to search for a node by ID
void AVL::searchIdHelper(string id) {
    bool flag = false;
    // Validate ID (it must have exactly 8 digits)
    if (id.length() != 8) {
        cout << "unsuccessful" << endl;
        return;
    }
    for (char c : id) {
        if (!isdigit(c)) {
            cout << "unsuccessful" << endl;
            return;
        }
    }
    // Start searching from the root
    searchId(root, id, flag);
    if (!flag) {
        cout << "unsuccessful" << endl;  // ID not found
    }
}
// Search for a node by ID in the AVL tree
void AVL::searchId(Node* node, string id, bool& flag) {
    if (node == nullptr) {
        return;  // Base case: stop if node is null
    }
    if (id == node->id) {
        cout << node->name << endl;  // Print the name if ID matches
        flag = true;  // Set flag to true (ID found)
        return;
    }
    // Recursively search in left or right subtree
    if (id < node->id) {
        searchId(node->left, id, flag);
    } else {
        searchId(node->right, id, flag);
    }
}
// Helper function to search for a node by name
void AVL::searchNameHelper(string name) {
    bool flag = false;
    searchName(root, name, flag);
    if (!flag) {
        cout << "unsuccessful" << endl;  // Name not found
    }
}
// Search for a node by name in the AVL tree
void AVL::searchName(Node* node, string name, bool& flag) {
    if (node == nullptr) {
        return;  // Stop if node is null
    }
    // If the name matches, print the ID and stop recursion
    if (name == node->name) {
        cout << node->id << endl;
        flag = true;
        return;
    }
    // Continue searching both left and right subtrees
    searchName(node->left, name, flag);
    searchName(node->right, name, flag);
}
// Helper function to remove a node by ID
void AVL::removeHelper(string id) {
    bool flag = false;
    // Validate the ID (it must be exactly 8 digits)
    if (id.length() != 8) {
        cout << "unsuccessful" << endl;
        return;
    }
    // Attempt to remove the node
    this->root = removeNode(this->root, id, flag);
    if (!flag) {
        cout << "unsuccessful" << endl;
    } else {
        cout << "successful" << endl;
    }
}
// Find the node with the smallest ID in a subtree
Node* AVL::smallestNode(Node* node) {
    Node* temp = node;
    while (temp->left != nullptr) {
        temp = temp->left;  // Keep moving left to find the smallest node
    }
    return temp;
}
// Remove a node from the AVL tree
Node* AVL::removeNode(Node* node, string id, bool& flag) {
    if (node == nullptr) {
        return node;  // Node not found
    }
    if (id > node->id) {
        node->right = removeNode(node->right, id, flag);  // Recur into the right subtree
    } else if (id < node->id) {
        node->left = removeNode(node->left, id, flag);  // Recur into the left subtree
    } else {
        flag = true;  // Node found
        // Case 1: Node with no children (leaf)
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        }
        // Case 2: Node with one child (right child)
        else if (node->left == nullptr) {
            Node* temp = node;
            node = node->right;
            delete temp;
        }
        // Case 2: Node with one child (left child)
        else if (node->right == nullptr) {
            Node* temp = node;
            node = node->left;
            delete temp;
        }
        // Case 3: Node with two children
        else {
            Node* temp = smallestNode(node->right);  // Find inorder successor
            node->id = temp->id;  // Replace node's ID with successor's ID
            node->name = temp->name;  // Replace node's name with successor's name
            node->right = removeNode(node->right, temp->id, flag);  // Remove the successor
        }
    }

    node->updateNodeHeight(node);  // Update height after deletion
    return rebalance(node);  // Rebalance the tree
}
// Helper function to remove a node at a given inorder position
void AVL::removeInorderHelper(int n) {
    bool flag = false;

    removeInorder(n, flag);
    if (!flag) {
        cout << "unsuccessful" << endl;
    } else {
        cout << "successful" << endl;
    }
}
// Remove a node based on its inorder position
void AVL::removeInorder(int n, bool& flag) {
    vector<Node*> inorderNodes;
    inorderTraversal(root, inorderNodes);  // Get the nodes in inorder sequence

    if (n < 0 || n >= inorderNodes.size()) {
        flag = false;
        return;
    }

    Node* targetNode = inorderNodes[n];  // Get the nth node
    root = removeNode(root, targetNode->id, flag);  // Remove the node by its ID
}
// Helper function to print nodes with commas
void AVL::printNodesWithCommas(const vector<Node*>& nodes) {
    for (size_t i = 0; i < nodes.size(); i++) {
        cout << nodes[i]->name;  // Print each node's name
        if (i != nodes.size() - 1) {
            cout << ", ";  // Print comma between nodes, but not after the last one
        }
    }
    cout << endl;  // Newline after printing all nodes
}
// Print the nodes in inorder sequence
void AVL::printInOrderHelper() {
    vector<Node*> inorderNodes;
    inorderTraversal(root, inorderNodes);  // Get the inorder sequence
    printNodesWithCommas(inorderNodes);  // Print nodes
}
// Print the nodes in preorder sequence
void AVL::printPreOrderHelper() {
    vector<Node*> preorderNodes;
    preorderTraversal(root, preorderNodes);  // Get the preorder sequence
    printNodesWithCommas(preorderNodes);  // Print nodes
}
// Print the nodes in postorder sequence
void AVL::printPostOrderHelper() {
    vector<Node*> postorderNodes;
    postorderTraversal(root, postorderNodes);  // Get the postorder sequence
    printNodesWithCommas(postorderNodes);  // Print nodes
}
// Inorder traversal to collect nodes
void AVL::inorderTraversal(Node* node, vector<Node*>& nodes) {
    if (node == nullptr) return;
    inorderTraversal(node->left, nodes);  // Traverse left subtree
    nodes.push_back(node);  // Visit the current node
    inorderTraversal(node->right, nodes);  // Traverse right subtree
}
// Preorder traversal to collect nodes
void AVL::preorderTraversal(Node* node, vector<Node*>& nodes) {
    if (node == nullptr) return;
    nodes.push_back(node);  // Visit the current node
    preorderTraversal(node->left, nodes);  // Traverse left subtree
    preorderTraversal(node->right, nodes);  // Traverse right subtree
}
// Postorder traversal to collect nodes
void AVL::postorderTraversal(Node* node, vector<Node*>& nodes) {
    if (node == nullptr) return;
    postorderTraversal(node->left, nodes);  // Traverse left subtree
    postorderTraversal(node->right, nodes);  // Traverse right subtree
    nodes.push_back(node);  // Visit the current node
}
// Count the levels in the tree using level-order traversal
int AVL::printLevelCount(Node* node) {
    if (node == nullptr) {
        return 0;  // Empty tree has 0 levels
    }

    // Queue for level-order traversal
    std::queue<Node*> q;
    q.push(node);  // Start with the root

    int levelCount = 0;

    // Traverse each level of the tree
    while (!q.empty()) {
        int levelSize = q.size();  // Number of nodes in the current level
        levelCount++;  // Increment level count

        // Process all nodes in the current level
        for (int i = 0; i < levelSize; i++) {
            Node* currentNode = q.front();
            q.pop();

            // Add left and right children to the queue
            if (currentNode->left != nullptr) {
                q.push(currentNode->left);
            }
            if (currentNode->right != nullptr) {
                q.push(currentNode->right);
            }
        }
    }

    return levelCount;  // Return the total number of levels
}
// Helper function to print the number of levels in the tree
void AVL::printLCHelper() {
    cout << printLevelCount(root) << endl;  // Print the level count
}
void processCommand(const string& input, AVL& tree) {

    regex commandRegex("(\\w+)(?:\\s+\"([^\"]+)\")?(?:\\s+(\\d+))?");
    smatch commandMatch;

    if (regex_search(input, commandMatch, commandRegex)) {
        string command = commandMatch[1];
        string name = commandMatch[2];
        string id_or_n = commandMatch[3];

        if (command == "insert" && !name.empty() && !id_or_n.empty()) {

            tree.insertHelper(id_or_n, name);
        }
        else if (command == "remove" && !id_or_n.empty()) {

            tree.removeHelper(id_or_n);
        }
        else if (command == "search" && !id_or_n.empty()) {

            tree.searchIdHelper(id_or_n);
        }
        else if (command == "search" && !name.empty()) {

            tree.searchNameHelper(name);
        }
        else if (command == "printInorder") {

            tree.printInOrderHelper();
        }
        else if (command == "printPreorder") {

            tree.printPreOrderHelper();
        }
        else if (command == "printPostorder") {

            tree.printPostOrderHelper();
        }
        else if (command == "printLevelCount") {

            tree.printLCHelper();
        }
        else if (command == "removeInorder" && !id_or_n.empty()) {

            int n = stoi(id_or_n);
            tree.removeInorderHelper(n);
        }

    } else {
        cout << "unsuccessful" << endl;
    }
}
