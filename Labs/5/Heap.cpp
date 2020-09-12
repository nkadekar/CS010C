#include <iostream>
#include "Heap.h"

using namespace std;

Heap::Heap(){
    numItems = 0;
}

void Heap::enqueue(PrintJob* insert){
    if (numItems < MAX_HEAP_SIZE){
        arr[numItems] = insert;
        numItems++;
        PercolateUp(numItems - 1);
    }
}

void Heap::dequeue(){
    if (numItems > 1){
        swap(arr[0], arr[numItems - 1]);
        numItems--;
        trickleDown(0);
    }
    else if (numItems == 1){
        numItems--;
    }
}

PrintJob* Heap::highest(){
    if (numItems > 0){
        return arr[0];
    }
    return nullptr;
}

void Heap::print(){
    if (highest() == nullptr){
        cout << "No items in priority queue." << endl;
    }
    else{
        cout << "Priority: " << highest() -> getPriority() << ", Job Number: " << highest() -> getJobNumber() << ", Number of Pages: " << highest() -> getPages() << endl;
    }
}


void Heap::trickleDown(int index){

    int child = 2 * index + 1;
    int value = arr[index] -> getPriority();

    while (child < numItems) {
        int maxValue = value;
        int maxIndex;
        for (int i = 0; i < 2 && i + child < numItems; i++) {
            if (arr[i + child] -> getPriority() > maxValue) {
                maxValue = arr[i + child] -> getPriority();
                maxIndex = i + child;
            }
        }
        if (maxValue == value) {
            return;
        }
        else {
            swap(arr[index], arr[maxIndex]);
            index = maxIndex;
            child = 2 * index + 1;
        }
    }
}

void Heap::PercolateUp(int index) {
    int parentIndex = 0;
    while (index > 0) {
        parentIndex = (index - 1) / 2;
        if (arr[index] -> getPriority() <= arr[parentIndex] -> getPriority()){
            return;
        }
        else{
            swap(arr[index],arr[parentIndex]);
            index = parentIndex;
        }
    }
}