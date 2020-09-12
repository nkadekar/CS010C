#include <string>
#include <vector>
#include <queue>
#include <iostream>

#ifndef JUG_H
#define JUG_H

using namespace std;

class Vertex {
 public:
    int x;
    int y;
    int cost;
    vector<string> path;
    vector<Vertex> neighbors;
    Vertex():x(0),y(0),cost(0){}
};

class Jug {
    private:
        int Ca;
        int Cb;
        int N;
        int cfA;
        int cfB;
        int ceA;
        int ceB;
        int cpAB;
        int cpBA;
    public:
        Jug(int, int, int, int, int, int, int, int, int);
        ~Jug();
        int solve(string &);
            //solve is used to check input and find the solution if one exists
            //returns -1 if invalid inputs. solution set to empty string.
            //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
            //returns 1 if solution is found and stores solution steps in solution string.
    private:
        Vertex fillA(Vertex);
        Vertex fillB(Vertex);
        Vertex pourAToB(Vertex);
        Vertex pourBToA(Vertex);
        Vertex emptyA(Vertex);
        Vertex emptyB(Vertex);
        bool search(vector<Vertex>, Vertex);
        Vertex BFS(Vertex);
};

#endif