//Worked with Edward Zhu and Royce Moses
//Also worked with Jordan Sam a little bit
#include "LList.h"
#include <iostream>
#include <fstream>

using namespace std;

//MAIN
int main(){
    LList circle;
    int n = -1;
    int startPos = -1;
    int skips = -1;
    string fileName;
    string nameInput;
    cout << "How many people are in the circle?" << endl;
    cin >> n;
    cout << "What is name of the file?" << endl;
    cin >> fileName;
    ifstream fin(fileName);
    //fin.open(fileName);
    if (!fin.is_open()){
        cout << "ERROR OPENING FILE" << endl;
        return 1;
    }
    for (int i = 0; i < n; ++i){
        getline(fin, nameInput);
        circle.push_back(nameInput);
    }
    // while (getline(fin, nameInput)){
    //     circle.push_back(nameInput);
    // }
    fin.close();
    cout << "Which position should we start from?" << endl;
    cin >> startPos;
    while (startPos < 1){
        cout << "Which position should we start from?" << endl;
        cin >> startPos;
    }
    cout << "How many people should be skipped?" << endl;
    cin >> skips;
    while (skips < 1){
        cout << "How many people should be skipped?" << endl;
        cin >> skips;
    }
    circle.Survivor(startPos, skips);
}