#include "BSTree.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int test = 0;

BSTree::BSTree() {
    root = nullptr;
    treecount = 0;
}

void BSTree::insert(const string & dat) {
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
            treecount++;
        }
        else {
            prev -> right = new Node(dat);
            treecount++;
        }
    }
}

bool BSTree::search(const string & dat) const {
    if (search(root, dat) == nullptr){
        return false;
    }
    else {
        return true;
    }
}

Node* BSTree::search(Node* curr, const string & dat) const {
    if(curr == nullptr){
        return nullptr;
    }
    else if (curr -> data == dat) {
        return curr;
    }
    else if (curr -> data > dat) {
        return search(curr -> left, dat);
    }
    else {
        return search(curr -> right, dat);
    }
}

Node* BSTree::searchParent(Node* child) const {
    Node* curr = root;
    if (child == nullptr){
        return nullptr;
    }
    else if (child == root){
        return nullptr;
    }
    else {
        while (curr != nullptr){
            if (curr->left == child || curr->right == child) {
                return curr;
            }
            else if (child->data > curr->data){
                curr = curr->right;
            }
            else {
                curr = curr->left;
            }
        }
    }
    return nullptr;
}

string BSTree::largest() const {
    if (root == nullptr) {
        return "";
    }
    if (treecount == 1){
        return root->data;
    }
    else{
        Node* curr = root;
        while(curr->right != nullptr){
            curr = curr->right;
        }
        return curr->data;
    }
}

string BSTree::smallest() const {
    if (root == nullptr) {
        return "";
    }
    if (treecount == 1){
        return root->data;
    }
    else{
        Node* curr = root;
        while(curr->left != nullptr){
            curr = curr->left;
        }
        return curr->data;
    }
}

int BSTree::height(const string & dat) const {
    Node *curr = search(root, dat);
    int height = treeHeight(curr);
    if (curr == nullptr) {
        return -1;
    }
    else {
        return height - 1;
    }
}

//Nikhil
int BSTree::treeHeight(Node* curr) const {
    if (curr == nullptr){
        return 0;
    }
    else {
        int leftHeight = treeHeight(curr -> left);
        int rightHeight = treeHeight(curr -> right);
        return 1 + std::max(leftHeight, rightHeight);
    }
}

void BSTree::remove(const string &dat) {
    if (root != nullptr) {
        Node* removalNode = search(root, dat);
        if (removalNode != nullptr) {
            if (removalNode->count > 1) {
                removalNode->count--;
                return;
            }
            else {
                Node* parent = searchParent(removalNode);
                remove(removalNode, parent);
            }
        }
   }
}

void BSTree::remove(Node* removalNode, Node* parent) {
    Node* curr = removalNode;
    if (curr->left == nullptr && curr->right == nullptr){
        if (curr == root) {
            root = nullptr;
        }
        else if (parent->left == curr){
            parent->left = nullptr;
        }
        else {
            parent->right = nullptr;
        }
        delete curr;
        treecount--;
    }
    //As long as there is a right children its going to look for inorder successor
    else if (curr -> left != nullptr) {
        parent = curr;
        curr = curr->left;
        while (curr->right != nullptr){
            parent = curr;
            curr = curr->right;
        }
        //Recursively removes the swap
        swap(removalNode, curr);
        remove(curr, parent);
    }
    //Else looks left -> all the way right
    else {
        parent = curr;
        curr = curr->right;
        while (curr->left != nullptr){
            parent = curr;
            curr = curr->left;
        }
        swap(removalNode, curr);
        remove(curr, parent);
        //Recursively remotes the swap
    }
}

//swapping a and b
void BSTree::swap(Node* a, Node* b){
    string bData = b->data;
    int bCount = b->count;
    b->data = a->data;
    b->count = a->count;
    a->data = bData;
    a->count = bCount;
}

void BSTree::preOrder() {
    preOrder(root);
}

void BSTree::preOrder(Node* curr) {
    if (curr != nullptr) {
        cout << curr -> data << "(" << curr -> count << "), ";
        preOrder(curr -> left);
        preOrder(curr -> right);
    }
}

void BSTree::inOrder() {
    inOrder(root);
}

void BSTree::inOrder(Node* curr) {
    if (curr != nullptr) {
        inOrder(curr -> left);
        cout << curr -> data << "(" << curr -> count << "), ";
        inOrder(curr -> right);
    }
}

void BSTree::postOrder() {
    postOrder(root);
}

void BSTree::postOrder(Node* curr) {
    if (curr != nullptr) {
        postOrder(curr -> left);
        postOrder(curr -> right);
        cout << curr -> data << "(" << curr -> count << "), ";
    }
}

void BSTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    test = 0;
    makekey(outFS,root);
    test = 0;
    outFS << endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void BSTree::visualizeTree(ofstream &outfile, Node *node) {
    if (node == nullptr) {
        return;
    }
    if (node -> left != nullptr) {
        outfile << "\t" << node -> data << " -> " << node -> left -> data << endl;
    }
    else {
        outfile << "\t" << node -> data << " -> " << test << endl;
        test++;
    }
    if (node -> right != nullptr) {
        outfile << "\t" << node -> data << " -> " << node -> right -> data << endl;
    }
    else {
        outfile << "\t" << node -> data << " -> " << test << endl;
        test++;
    }
    visualizeTree(outfile, node -> left);
    visualizeTree(outfile, node -> right);
}

void BSTree::makekey(ofstream &outfile, Node *node) {
    if (node == nullptr) {
        return;
    }
    outfile << "\t" << node->data << "[color = lightblue, peripheries=2, style = filled, label=\"" << node->data << " " << node -> count << "\"]" << endl;
    
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