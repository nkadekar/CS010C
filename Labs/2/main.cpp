#include "IntList.h"
#include <iostream>

using namespace std;

int main(){
    IntList test;
    cout << "IntList: " << test << endl;
    cout << "empty(should be 1): " << test.empty() << endl;
    cout << "pushfront 10" << endl;
    test.push_front(10);
    cout << "IntList(should be 10): " << test << endl;
    cout << "empty(should be 0): " <<test.empty() << endl;
    cout << "pushfront 9" << endl;
    test.push_front(9);
    cout << "IntList(should be 9 10): " << test << endl;
    cout << "pushback 11" << endl;
    test.push_back(11);
    cout << "IntList(should be 9 10 11): " << test << endl;
    cout << "printReverse(should be 11 10 9): ";
    test.printReverse();
    cout << endl;
    cout << "popfront (9)" << endl;
    test.pop_front();
    cout << "IntList(should be 10 11): " << test << endl;
    cout << "printReverse(should be 11 10): ";
    test.printReverse();
    cout << endl;
    cout << "popback (11)" << endl;
    test.pop_back();
    cout << "IntList(should be 10): " << test << endl;
    cout << "printReverse(should be 10): ";
    test.printReverse();
    cout << endl;
    cout << "popback (10)" << endl;
    test.pop_back();
    cout << "IntList(should be ): " << test << endl;
    cout << "printReverse(should be ): ";
    test.printReverse();
    cout << endl;
    cout << "popback on empty list" << endl;
    test.pop_back();
    cout << "IntList(should be ): " << test << endl;
    cout << "printReverse(should be ): ";
    test.printReverse();
    cout << endl;
    cout << "popfront on empty list" << endl;
    test.pop_front();
    cout << "IntList(should be ): " << test << endl;
    cout << "printReverse(should be ): ";
    test.printReverse();
    cout << endl;
}