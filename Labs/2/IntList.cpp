#include "IntList.h"
#include <iostream>

using namespace std;

IntList::IntList(){
    dummyHead = new IntNode(0);
    dummyTail = new IntNode(0);
    dummyHead->next = dummyTail;
    dummyTail->prev = dummyHead;
}

IntList::~IntList(){
    while(!empty()){
        pop_front();
    }
    delete dummyHead;
    delete dummyTail;
    dummyHead = dummyTail = 0;
}

void IntList::push_front(int value){
    IntNode* temp = new IntNode(value);
    temp->next = dummyHead->next;
    temp->prev = dummyHead;
    dummyHead->next = temp;
    temp->next->prev = temp;
}

void IntList::push_back(int value){
    IntNode* temp = new IntNode(value);
    temp->prev = dummyTail->prev;
    temp->next = dummyTail;
    dummyTail->prev->next = temp;
    dummyTail->prev = temp;
}

void IntList::pop_front(){
    if (!empty()){
        IntNode* temp = dummyHead->next;
        dummyHead->next = temp->next;
        temp->next->prev = dummyHead;
        temp->next = temp->prev = nullptr;
        delete temp;
    }
}

void IntList::pop_back(){
    if (!empty()){
        IntNode* temp = dummyTail->prev;
        temp->prev->next = dummyTail;
        dummyTail->prev = temp->prev;
        temp->next = temp->prev = nullptr;
    }
}

bool IntList::empty() const{
    if (dummyHead->next == dummyTail){
        return true;
    }
    else {
        return false;
    }
}

ostream & operator<<(ostream &out, const IntList &rhs){
    if (!rhs.empty()){
        out << rhs.dummyHead->next->data;
        IntNode *curr = rhs.dummyHead->next->next;
        if (curr != rhs.dummyTail){
            out << " ";
        }
        while (curr != rhs.dummyTail){
            out << curr->data;
            if (curr->next != rhs.dummyTail){
                out << " ";
            }
            curr = curr->next;
        }
    }
    return out;
}

void IntList::printReverse() const{
    if (!empty()){
        cout << dummyTail->prev->data;
        IntNode *curr = dummyTail->prev->prev;
        if (curr != dummyHead){
            cout << " ";
        }
        while (curr != dummyHead){
            cout << curr->data;
            if (curr->prev != dummyHead){
                cout << " ";
            }
            curr = curr->prev;
        }
    }
}