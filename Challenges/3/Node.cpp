#include "Node.h"
#include <string>

using namespace std;

Node::Node(string d){
    data = d;
    count = 1;
    left = nullptr;
    right = nullptr;
}