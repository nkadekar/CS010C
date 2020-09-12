#include "arithmeticExpression.h"
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <stack>
#include <fstream>

int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

void arithmeticExpression::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    makekey(outFS,root);
    outFS << endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void arithmeticExpression::visualizeTree(ofstream &outfile, TreeNode *node){
    if (node -> left != nullptr) {
        outfile << "\t" << node -> key << " -> " << node -> left -> key << endl;
        outfile << "\t" << node -> key << " -> " << node -> right -> key << endl;
        visualizeTree(outfile, node -> left);
        visualizeTree(outfile, node -> right);
    }
}

void arithmeticExpression::makekey(ofstream &outfile, TreeNode *node) {
    if (node != nullptr) {
        outfile << "\t" << node->key << "[color = lightblue, peripheries=2, style = filled, label=\"" << node->data << "\"]" << endl;
        makekey(outfile, node -> left);
        makekey(outfile, node -> right);
    }
}

arithmeticExpression::arithmeticExpression(const string &input){
    infixExpression = input;
    root = nullptr;
}

void arithmeticExpression::buildTree() {
    string postString = infix_to_postfix();
    stack<TreeNode*> s;
    char c;
    TreeNode *temp;
    TreeNode *t1;
    TreeNode *t2;
    char startKey = 'a';
    for(unsigned i = 0; i < postString.size(); ++i){
        c = postString.at(i);
        if(c == '+' || c == '-' || c == '*' || c == '/'){ //c is an operator
            //pull last two from stack
            t1 = s.top();
            s.pop();
            t2 = s.top();
            s.pop();

            //Make a tree of root c and last two items from stack
            temp = new TreeNode(c, startKey);
            startKey ++;
            temp -> left = t2;
            temp -> right = t1;
            s.push(temp);

        }
        else{ //c is an operand
            //Make single tree of c and push to stack
            temp = new TreeNode(c, startKey);
            startKey++;
            s.push(temp);
        }
    }
    root = s.top();
    return;
}

void arithmeticExpression::infix() {
    this -> infix(root);
}

void arithmeticExpression::infix(TreeNode *subNode) {
    if (subNode != nullptr) {
        if(subNode -> data == '+' || subNode -> data == '-' || subNode -> data == '*' || subNode -> data == '/'){
            cout << "(";
        }
        infix(subNode -> left);
        cout << subNode -> data;
        infix(subNode -> right);
        if(subNode -> data == '+' || subNode -> data == '-' || subNode -> data == '*' || subNode -> data == '/'){
            cout << ")";
        }
    }
}

void arithmeticExpression::prefix() {
    this -> prefix(root);
}

void arithmeticExpression::prefix(TreeNode *subNode) {
    if (subNode != nullptr) {
        cout << subNode -> data;
        prefix(subNode -> left);
        prefix(subNode -> right);
    }
}

void arithmeticExpression::postfix() {
    this -> postfix(root);
}

void arithmeticExpression::postfix(TreeNode *subNode) {
    if (subNode != nullptr) {
        postfix(subNode -> left);
        postfix(subNode -> right);
        cout << subNode -> data;
    }
}