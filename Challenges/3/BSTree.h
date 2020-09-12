#include "Node.h"
#include <string>
#include <fstream>

using namespace std;

class BSTree {
 private:
    Node* root; //pointer to root node
    int treecount; //number of NODES in tree

 public:
    BSTree();
    //Constructor

    void insert(const string &);
    //Insert an item into the binary search tree. Be sure to keep the binary search tree properties.
    //When an item is first inserted into the tree the count should be set to 1. 
    //When adding a duplicate string (case sensitive), rather than adding another node, 
        //the count variable should just be incremented.

    bool search(const string &) const;
    //Search for a string in the binary search tree. 
    //It should return true if the string is in the tree, and false otherwise.

    string largest() const;
    //Find and return the largest value in the tree. Return an empty string if the tree is empty.

    string smallest() const;
    //Find and return the smallest value in the tree. Return an empty string if the tree is empty.

    int height(const string &) const;
    //Compute and return the height of a particular string in the tree. 
    //The height of a leaf node is 0 (count the number of edges on the longest path). 
    //Return -1 if the string does not exist.

    void remove(const string &);
    //Remove a specified string from the tree. Be sure to maintain all binary search tree properties. 
    //If removing a node with a count greater than 1, just decrement the count, 
        //otherwise, if the count is simply 1, remove the node. 
    //You MUST follow the remove algorithm shown in the slides and discussed in class or else your 
        //program will not pass the test functions. When removing, if removing a leaf node, simply remove the leaf. 
    //Otherwise, if the node to remove has a left child, replace the node to remove with the 
        //largest string value that is smaller than the current string to remove 
        //(i.e. find the largest value in the left subtree of the node to remove). 
    //If the node has no left child, replace the node to remove with the smallest value larger than 
        //the current string to remove (i.e. find the smallest value in the right subtree of the node to remove).

    void preOrder();
    //Traverse and print the tree in preorder notation following the printing guidelines specified above.

    void inOrder();
    //Traverse and print the tree in inorder notation following the printing guidelines specified above.

    void postOrder();
    //Traverse and print the tree in postorder notation following the printing guidelines specified above.

//VISUALIZING TREE (GRAPHVIZ)
    void visualizeTree(const string &outputFilename);

 private:
    void preOrder(Node*);
    //Traverse and print the tree in preorder notation following the printing guidelines specified above.

    void inOrder(Node*);
    //Traverse and print the tree in inorder notation following the printing guidelines specified above.

    void postOrder(Node*);
    //Traverse and print the tree in postorder notation following the printing guidelines specified above.

    Node* search(Node*, const string &) const;
    //returns pointer to node containing string

    int treeHeight(Node*) const;
    //returns height of passed in node

    void remove(Node*, Node*);
    //removes node given pointers to node and parent

    Node* searchParent(Node*) const;
    //returns pointer to parent of node passed in

    void swap(Node*, Node*);
    //swaps data and count in nodes passed in

//VISUALIZING TREE(GRAPHVIZ)
    void visualizeTree(ofstream &outfile, Node *node);
    void makekey(ofstream &outfile, Node *node);
};