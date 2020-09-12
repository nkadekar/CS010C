#include <string>
#include <list>
#include <stack>

#ifndef WORDLADDER_H
#define WORDLADDER_H

using namespace std;

class WordLadder {

  private:
    list<string> dict;

  public:
    WordLadder(const string &);
    void outputLadder(const string &start, const string &end, const string &outputFile);
    
  private:
    bool offByOne(string, string);
    bool ifExists(string, string);
    void print(stack<string>, ofstream &, string);
};

#endif