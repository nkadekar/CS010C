#include "AVLTree.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int test = 0;

AVLTree::AVLTree(){
    root = nullptr;
    treecount = 0;
}

void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    test = 0;
    makekey(outFS, root);
    test = 0;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<<n->data <<" -> " <<n->left->data<<";"<<endl;    
        }
        else {
            outFS << "\t" << n -> data << " -> " << test << endl;
            test++;
        }

        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<<n->data <<" -> " <<n->right->data<<";"<<endl;    
        }
        else {
            outFS << "\t" << n -> data << " -> " << test << endl;
            test++;
        }
    }
}

void AVLTree::makekey(ofstream &outfile, Node *node) {
    if (node == nullptr) {
        return;
    }
    if (node != root) {
        outfile << "\t" << node->data << "[color = lightblue, peripheries=2, style = filled, label=\"" << node->data << ", " << balanceFactor(node) << ", par:" << node -> parent -> data <<  "\"]" << endl;
    }
    else {
        outfile << "\t" << node->data << "[color = lightblue, peripheries=2, style = filled, label=\"" << node->data << ", " << balanceFactor(node) << ", no par" <<  "\"]" << endl;
    }
    makekey(outfile, node -> left);
    if (node -> left == nullptr) {
        outfile << "\t" << test << "[color = red, peripheries=2, style = filled, label=\"" << test << "\"]" << endl;
        ++test;
    }
    makekey(outfile, node -> right);
    if (node -> right == nullptr) {
        outfile << "\t" << test << "[color = red, peripheries=2, style = filled, label=\"" << test << "\"]" << endl;
        ++test;
    }
}

void AVLTree::insert(const string & dat) {
    if (root == nullptr){
        root = new Node(dat);
        treecount++;
    }
    else {
        Node* curr = root;
        Node* prev = nullptr;
        while (curr != nullptr) {
            if (curr -> data == dat) {
                curr -> count++;
                return;
            }
            else if (curr -> data > dat) {
                prev = curr;
                curr = curr -> left;
            }
            else {
                prev = curr;
                curr = curr -> right;
            }
        }
        if (dat < prev -> data) {
            prev -> left = new Node(dat);
            prev -> left -> parent = prev;
            treecount++;
            rotate(findUnbalancedNode(prev -> left));
        }
        else {
            prev -> right = new Node(dat);
            prev -> right -> parent = prev;
            treecount++;
            rotate(findUnbalancedNode(prev -> right));
        }
    }
}

int AVLTree::balanceFactor(Node* curr) {
    if (curr == nullptr) {
        return -1;
    }
    return treeHeight(curr -> left) - treeHeight(curr -> right);
}

int AVLTree::treeHeight(Node* curr) const {
    if (curr == nullptr){
        return -1;
    }
    else {
        int leftHeight = treeHeight(curr -> left);
        int rightHeight = treeHeight(curr -> right);
        return 1 + std::max(leftHeight, rightHeight);
    }
}

void AVLTree::printBalanceFactors() {
    printBalanceFactors(root);
}

void AVLTree::printBalanceFactors(Node *curr) {
    if (curr != nullptr) {
        printBalanceFactors(curr -> left);
        cout << curr -> data << "(" << balanceFactor(curr) << "), ";
        printBalanceFactors(curr -> right);
    }

}

Node* AVLTree::findUnbalancedNode(Node* curr) {
    while (curr != nullptr) {
        if (balanceFactor(curr) < -1 || balanceFactor(curr) > 1){
            return curr; 
        }
        curr = curr -> parent;
    }
    return nullptr;
}

void AVLTree::rotate(Node* curr) {
    if (curr == nullptr) {
        return;
    }
    else if (balanceFactor(curr) == 2) { //unbalanced on left side
        if (balanceFactor(curr -> left) == -1) { //zigzag case
            rotateLeft(curr -> left);
        }
        rotateRight(curr);
    }
    else if (balanceFactor(curr) == -2) { //unbalanced on right side
        if (balanceFactor(curr -> right) == 1) { //zigzag case
            rotateRight(curr -> right);
        }
        rotateLeft(curr);
    }
}

void AVLTree::rotateLeft(Node* curr) {
    Node* rightLeftChild = curr->right->left;
    if (curr->parent != nullptr){ //Sets the correct child node from the parent of the node getting called rotate in
        AVLTreeReplaceChild(curr->parent, curr, curr->right);
    }
    else { // node is root
        root = curr->right;
        root -> parent = nullptr;
    }
    AVLTreeSetChild(curr->right, "left", curr);
    //Re-Sets what curr right should be
    AVLTreeSetChild(curr, "right", rightLeftChild);
}

void AVLTree::rotateRight(Node* curr) {
    Node* leftRightChild = curr->left->right;
    if (curr->parent != nullptr){ //Sets the correct child node from the parent of the node getting called rotate in
        AVLTreeReplaceChild(curr->parent, curr, curr->left);
    }
    else { // node is root
        root = curr->left;
        root -> parent = nullptr;
    }
    AVLTreeSetChild(curr->left, "right", curr);
    //Re-Sets what curr left should be
    AVLTreeSetChild(curr, "left", leftRightChild);
}

bool AVLTree::AVLTreeSetChild(Node* parent, string whichChild, Node* child) {
    if (whichChild != "left" && whichChild != "right"){
        return false;
    }
    if (whichChild == "left"){
        parent->left = child;
    }
    else {
        parent->right = child;
    }
    if (child != nullptr) {
        child->parent = parent;
    }
    //AVLTreeUpdateHeight(parent);
    return true;
}

bool AVLTree::AVLTreeReplaceChild(Node* parent, Node* currentChild, Node* newChild) {
    if (parent->left == currentChild){
      return AVLTreeSetChild(parent, "left", newChild);
    }
    else if (parent->right == currentChild) {
        return AVLTreeSetChild(parent, "right", newChild);
    }
    return false;
}