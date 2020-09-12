#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <ctime>

using namespace std;

//FUNC DECLARATIONS
template<typename T>
unsigned min_index(const vector<T> &, unsigned);

template<typename T>
void selection_sort(vector<T> &);

template<typename T>
T getElement(vector<T> &, unsigned);

vector<char> createVector();


//MAIN
int main(){

    //Part A
    vector<int>v1 = {2,3,6,1,5};
    cout << "Before: ";
    for (unsigned i = 0; i < v1.size(); ++i){
        cout << v1.at(i) << " ";
    }
    cout << endl;
    selection_sort(v1);
    cout << "After: ";
    for (unsigned i = 0; i < v1.size(); ++i){
        cout << v1.at(i) << " ";
    }
    cout << endl << endl;
    vector<char>v2 = {'v','c','p','g','a'};
    cout << "Before: ";
    for (unsigned i = 0; i < v2.size(); ++i){
        cout << v2.at(i) << " ";
    }
    cout << endl;
    selection_sort(v2);
    cout << "After: ";
    for (unsigned i = 0; i < v2.size(); ++i){
        cout << v2.at(i) << " ";
    }
    cout << endl << endl;
    vector<double>v3 = {0.6,9.3,57.0,2.4,100.5};
    cout << "Before: ";
    for (unsigned i = 0; i < v3.size(); ++i){
        cout << v3.at(i) << " ";
    }
    cout << endl;
    selection_sort(v3);
    cout << "After: ";
    for (unsigned i = 0; i < v3.size(); ++i){
        cout << v3.at(i) << " ";
    }
    cout << endl << endl;

    //Part B
    try{
        srand(time(0));
        vector<char> vals = createVector();
        char curChar;
        int index;
        int numOfRuns = 10;
        while(--numOfRuns >= 0){
            cout << "Enter a number: " << endl;
            cin >> index;
            curChar = getElement(vals,index);
            cout << "Element located at " << index << ": is " << curChar << endl;
        }
    }
    catch (out_of_range &excpt) {
        cout << excpt.what() << endl;
        cout << "Unable to access index." << endl;
    }

    return 0;
}


//IMPLEMENTATIONS
template<typename T>
unsigned min_index(const vector<T> &vals, unsigned index){
    if (index > vals.size() - 1 || index < 0){
        throw out_of_range("Out of range");
    }
    unsigned min = index;
    for (unsigned i = index; i < vals.size(); i++){
        if (vals.at(min) > vals.at(i)){
            min = i;
        }
    }
    return min;
}

template<typename T>
void selection_sort(vector<T> &vals) {
    for (unsigned i = 0; i < vals.size(); ++i) {
        swap(vals.at(i), vals.at(min_index(vals, i)));
    }
    // int minIndex;
    // for (unsigned i = 0; i < vals.size(); i++) {
    //     minIndex = min_index(vals, i);
    //     T temp;
    //     temp = vals.at(i);
    //     vals.at(i) = vals.at(minIndex);
    //     vals.at(minIndex) = temp;
    // }
}

template<typename T>
T getElement(vector<T> &vals, unsigned index) {
  if (index > vals.size() - 1 || index < 0){
        throw out_of_range("Out of range");
  }
  else {
    return vals.at(index);
  }
}

vector<char> createVector(){
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}