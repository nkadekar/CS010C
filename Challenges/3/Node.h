#include <string>

using namespace std;

class Node{
 public:
    string data; //holds data in the node
    int count; //holds number of duplicates
    Node* left;
    Node* right;

    Node(string);
    //constructor(count set to default of 1)
};