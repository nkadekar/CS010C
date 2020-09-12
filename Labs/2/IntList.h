#include <iostream>

using namespace std;

#ifndef INTLIST_H
#define INTLIST_H

struct IntNode {
    int data;
    IntNode *prev;
    IntNode *next;
    IntNode(int data) : data(data), prev(0), next(0) {}
};

class IntList {
 private:
    IntNode* dummyHead;
    IntNode* dummyTail;
 public:
    IntList();
    ~IntList();
    void push_front(int); //This must be an O(1) operation.
    void pop_front(); //This must be an O(1) operation.
    void push_back(int); //This must be an O(1) operation.
    void pop_back(); //This must be an O(1) operation.
    bool empty() const;
    friend ostream & operator<<(ostream &, const IntList &);
    void printReverse() const;
};

#endif