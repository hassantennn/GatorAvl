#include "AVL.h"
#include <iostream>
#include <string>
using namespace std;


int main() {
    AVL tree;
    // Example input
    string input;

    // Simulate user input
    while (getline(cin, input)) {
        processCommand(input, tree);
    }

    return 0;
}
