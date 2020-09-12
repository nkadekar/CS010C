#include "WordLadder.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <vector>

using namespace std;

WordLadder::WordLadder(const string &filename) {
    ifstream inFS;
    inFS.open(filename);
    if (!inFS.is_open()){
        cout << "Error opening file." << endl;
        return;
    }
    string word;
    //input words into list(dict) and make sure words are exactly 5 letters
    while (inFS >> word) {
        if (word.size() != 5) {
            cout << word << " in file does not have 5 chars" << endl;
            return;
        }
        else {
            dict.push_back(word);
        }
    }
}

void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile) {
    string word; //this string is used within the while loop
    stack<string>s1; //initial stack
    s1.push(start);
    queue<stack<string>>qofstacks;
    qofstacks.push(s1); //initial stack enqueued
    ofstream outFS;
    outFS.open(outputFile);
    if (!outFS.is_open()){
        cout << "Error opening Output file." << endl;
    }
    //checks if start and end exist in the dictionary
    if (!ifExists(start, end)) {
        cout << "Start word or End word does not exist in dictionary." << endl;
        return;
    }
    //if start and end are the same word, the word ladder is complete already
    if (start == end){
        outFS << start << endl;
        return;
    }
    else {
        //Deletes the start word from dictionary
        for (list<string>::iterator it = dict.begin(); it != dict.end(); ++it) {
            if (*it == start) {
                it = dict.erase(it);
            }
        }
        while(!qofstacks.empty()){
            word = qofstacks.front().top();
            for (list<string>::iterator it = dict.begin(); it != dict.end(); ++it) {
                //checks if each word is an "off by one" word
                if (offByOne(*it, word)) {
                    //create a copy of the front stack in the queue and push the new word onto new stack
                    stack<string>s2 = qofstacks.front();
                    s2.push(*it);
                    //if word found is the end word, print the stack
                    if (*it == end) {
                        print(qofstacks.front(), outFS, end);
                        return;
                    }
                    //else enqueue the new stack and erase the word from the dictionary
                    else {
                        qofstacks.push(s2);
                        it = dict.erase(it);
                        //decrement iterator to make up for the word being deleted from dictionary
                        it--;
                    }
                }
            }
            qofstacks.pop();
        }
        outFS << "No Word Ladder Found." << endl;
    }
}

bool WordLadder::offByOne(string word, string key){
        unsigned counter = 0;
        for (unsigned i = 0; i < word.size(); ++i){
            if (word.at(i) == key.at(i)){
                counter++;
            }
        }
        if (counter == 4){
            return true;
        }
        else {
            return false;
        }
    }

bool WordLadder::ifExists(string start, string end) {
    int c1 = 0;
    for (list<string>::iterator it = dict.begin(); it != dict.end(); ++it) {
        if (*it == start) {
            c1++;
        }
        if (*it == end) {
            c1++;
        }
    }
    if (c1 == 2) {
        return true;
    }
    else {
        return false;
    }
}

//pops the stack one at a item and stores word into vector
//then reads vector backwards to ofstream
void WordLadder::print(stack<string> answer, ofstream &outFS, string end) {
    vector<string> temp;
    while (!answer.empty()) {
        temp.push_back(answer.top());
        answer.pop();
    }
    for (unsigned i = temp.size() - 1; i != 0; i--) {
        outFS << temp.at(i) << " ";
    }
    outFS << temp.at(0) << " ";
    outFS << end << endl;
}