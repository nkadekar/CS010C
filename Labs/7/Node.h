#include <string>

using namespace std;

class Node{
 public:
    string data; //holds data in the node
    int count;
    Node* left;
    Node* right;
    Node* parent;
    Node(string);
    //constructor(count set to default of 1)
};