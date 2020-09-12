#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

const int MAX_SIZE = 20;

template<typename T>
class stack {
 private:
    T data[MAX_SIZE];
    int size;
 public:
    stack(); //constructs an empty stack.
    void push(T); //inserts a new element (val) of type T (T could be integer or string) into the data. If the data array is full, this function should throw an overflow_error exception with error message "Called push on full stack.".
    void pop(); //removes the last element from data. If the data array is empty, this function should throw an outofrange exception with error message "Called pop on empty stack.".
    T top(); //returns the top element of stack (last inserted element). If stack is empty, this function should throw an underflow_error exception with error message "Called top on empty stack.".
    bool empty(); //returns true if the stack is empty otherwise it returns false.
};

//IMPLEMENTATIONS
template<typename T>
stack<T>::stack(){
   size = 0;
}

template<typename T>
void stack<T>::push(T val){
   if (size >= MAX_SIZE){
      throw overflow_error("Called push on full stack.");
   }
   else {
      data[size] = val;
      size++; 
   }
}

template<typename T>
void stack<T>::pop(){
   if (size == 0) {
      throw out_of_range("Called pop on empty stack.");
   }
   else {
      size--;
   }
}

template<typename T>
T stack<T>::top(){
   if (size == 0){
      throw underflow_error("Called top on empty stack.");
   }
   return data[size - 1];
}

template<typename T>
bool stack<T>::empty(){
   if (size == 0) {
      return true;
   }
   else {
      return false;
   }
}