//Worked with Edward Zhu and Royce Moses
#include <iostream>

using namespace std;

#ifndef LLIST_H
#define LLIST_H

struct IntNode {
    string data;
    IntNode *next;
    IntNode(string data) : data(data), next(0) {}
};

class LList {
 private:
    IntNode* head;
    IntNode* tail;
 public:
    LList();
    ~LList();
    void pop_front();
    bool empty() const;
    void push_back(string);
    void removeAfter(IntNode*);
    void Survivor(int, int);
};

#endif