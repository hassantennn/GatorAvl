#ifndef AVL_H  // Include guard
#define AVL_H
#include <vector>
#include <queue>
#include <string>
using namespace std;

class Node {
public:
    string name;
    string id;
    int height;
    Node* left;
    Node* right;

    Node(string name, string id);
    int nodeHeight(Node* node);
    int updateNodeHeight(Node* node);
    int getBalanceFactor(Node* node);
};

class AVL {
public:
    Node* root;
    Node* insert(Node* node, string name, string id, bool& flag);  // Changed id type to string
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateLeftRight(Node* node);
    Node* rotateRightLeft(Node* node);
    Node* rebalance(Node* node);   // Changed id type to string
    Node* removeNode(Node* node, string id, bool&flag);
    Node* smallestNode(Node* node);
    void insertHelper(string id, string name);
    void removeHelper(string id);
    void searchIdHelper(string id);
    void searchId(Node* node, string id, bool& flag);
    void searchNameHelper(string name);
    void searchName(Node* node, string name, bool& flag);
    void removeInorderHelper(int n) ;
    void removeInorder(int n, bool&flag);
    void inorderTraversal(Node* node, vector<Node*>& nodes);
    void postorderTraversal(Node* node, vector<Node*>& nodes);
    void preorderTraversal(Node* node, vector<Node*>& nodes);
    void printInOrderHelper();
    void printPreOrderHelper();
    void printPostOrderHelper();
    void printInOrder(Node* node);
    void printPreOrder(Node* node);
    void printPostOrder(Node* node);
    int printLevelCount(Node* node);
    void printLCHelper();
    void printNodesWithCommas(const vector<Node*>& nodes);

 ;  AVL();
};

void processCommand(const string& input, AVL& tree);

#endif  // AVL_H
