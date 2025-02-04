//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Michael Puckett
// Version     : 1.0
// Copyright   : Copyright © 2023 SNHU COCE
// Description : Lab 5-2 Binary Search Tree
//============================================================================

#include <iostream>
#include <time.h>
#include <algorithm>
#include <functional> // Required for std::function

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}


// Internal structure for tree node
struct Node {
    Bid bid;
    Node *left;
    Node *right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Bid aBid) :
            Node() {
        bid = aBid;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;
    static std::function<void(Node*)> deletePostOrder; // Declaring lambda in the private section

    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);
    Node* removeNode(Node* node, string bidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
};

std::function<void(Node*)> BinarySearchTree::deletePostOrder = [](Node* node) {
  if (node) {
    BinarySearchTree::deletePostOrder(node->left);
    BinarySearchTree::deletePostOrder(node->right);
    delete node;
  }
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // Initialize root to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
    deletePostOrder(root);
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // call inOrder function and pass root
    inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // postOrder root
    postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // preOrder root
    preOrder(root);
}



/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    // if root is null, create a new node
    // otherwise, add the node using recursive helper
    if (root == nullptr){
        root = new Node(bid);
    } else {
        addNode(root, bid);
    }
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
    // remove node root bidID
    root = removeNode(root, bidId);
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    // set current node equal to root
    Node* current = root;
    
    // keep looping downwards until bottom reached or matching bidId found
    while (current != nullptr){
        // if match found, return current bid
        if (current->bid.bidId == bidId){
            return current->bid;
        }
        // if bid is smaller than current node then traverse left
        if (bidId < current->bid.bidId){
            current = current->left;
        }
        // else larger so traverse right
        else {
            current = current->right;
        }
    }

    Bid bid;
    return bid;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    // if bid id is less then the current node's id then add to left
    if(bid.bidId < node->bid.bidId){
        // if no left node, create a new left node
        if(node->left == nullptr){
            node->left = new Node(bid);
        }
        // otherwise, recursively add the new node to the left child
        else{
            addNode(node->left, bid);
        }
    }
     // otherwise, add to the right side
    else{
        // if no right node, create a new right node
        if (node->right == nullptr){
            node->right = new Node(bid);
        }
        // otherwise recursively add the new node to the right child
        else{
            addNode(node->right, bid);
        }
    }
}

/**
 * Traverses the tree in order
 */
void BinarySearchTree::inOrder(Node* node) {
      //if node is not equal to null ptr
    if(node != nullptr){
        //InOrder not left
        inOrder(node->left);
        //output bidID, title, amount, fund
        ::displayBid(node->bid);
        //InOder right
        inOrder(node->right);
    }
}

/**
 * Traverses the tree in post-order
 */
void BinarySearchTree::postOrder(Node* node) {
      //if node is not equal to null ptr
    if(node != nullptr){
        //postOrder left
        postOrder(node->left);
        //postOrder right
        postOrder(node->right);
        //output bidID, title, amount, fund
        ::displayBid(node->bid);
    }

}

/**
 * Traverses the tree in pre-order
 */
void BinarySearchTree::preOrder(Node* node) {
      //if node is not equal to null ptr
    if(node != nullptr){
        //output bidID, title, amount, fund
        ::displayBid(node->bid);
        //postOrder left
        preOrder(node->left);
        //postOrder right
        preOrder(node->right);
    }
}

/**
 * Remove a bid from some node (recursive)
 */
Node* BinarySearchTree::removeNode(Node* node, string bidId) {
    // if node is null, return node
    if (node == nullptr){
        return node;
    }
    
    // if the bidId is less than the current node's bidId, recurse down the left subtree
    if (bidId < node->bid.bidId){
        node->left = removeNode(node->left, bidId);
    }
    // otherwise if the bidId is greater than the current node's bidId, recurse down the right subtree
    else if(bidId > node->bid.bidId){
        node->right = removeNode(node->right, bidId);
    }
    //otherwise, this is the node that needs to be removed
    else{
        // if the node is a leaf, simply delete the node and return nullptr
        if(node->left == nullptr && node->right == nullptr){
            delete node;
            return nullptr;
        }
         // if the node has only one child on the left, replace the node with the left child
        else if(node->left != nullptr && node->right == nullptr){
            Node* temp = node->left;
            delete node;
            return temp;
        }
         // if the node has only one child on the right, replace the node with the right child
        else if (node->left == nullptr && node->right != nullptr){
            Node* temp = node->right;
            delete node;
            return temp;
        }
        //otherwise the node has two children
        else {
            // find the minimum node in the right subtree
            Node* temp = node->right;
            while(temp->left != nullptr){
                temp = temp->left;
            }
            // replace the current node's data with the minimum node's data
            node->bid = temp->bid;
            // recursively remove the node with the minimum data from the right subtree
            node->right = removeNode(node->right, temp->bid.bidId);
        }
    }
    // return the updated node
    return node;
}



//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bst->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(std::remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98223";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales.csv";
        bidKey = "98223";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            //cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
                cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}