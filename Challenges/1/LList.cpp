//Worked with Edward Zhu and Royce Moses
#include "LList.h"
#include <iostream>

using namespace std;

LList::LList(){
    head = nullptr;
    tail = nullptr;
}

LList::~LList(){
    while(!empty()){
        pop_front();
    }
}

void LList::pop_front(){
    if (!empty()){
        if (head == tail){
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else{
            IntNode *temp = head->next;
            delete head;
            head = temp;
            tail->next = head;
        }
    }
}

bool LList::empty() const{
    if (head == 0 && tail == 0){
        return true;
    }
    else{
        return false;
    }
}

void LList::push_back(string name){
    if (tail == 0){
        tail = new IntNode(name);
        tail->next = head;
        head = tail;
    }
    else{
        IntNode *temp = new IntNode(name);
        tail->next = temp;
        tail = temp;
        tail->next = head;
    }
}

void LList::removeAfter(IntNode* prev){
    if (!empty()){
        if (prev->next == head){
            pop_front();
        }
        else if (prev->next == tail){
            delete tail;
            tail = prev;
            tail->next = head;
        }
        else{
            IntNode* temp = prev->next;
            prev->next = temp->next;
            delete temp;
        }
    }
}

void LList::Survivor(int startPos, int skips){
    IntNode* curr = head;
    //find start pos
    for(int i = 1; i < startPos; ++i){
        curr = curr->next;
    }
    while(head != tail){
        //get curr to position before executed person
        for (int k = 0; k < skips - 2; ++k){
            curr = curr->next;
        }
        cout << "Eliminated: " << curr->next->data << endl;
        removeAfter(curr);
        curr = curr->next;
    }
    cout << "Survivor: " << head->data << endl;
}