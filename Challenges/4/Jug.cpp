#include "Jug.h"
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>

using namespace std;

//CONSTRUCTOR
Jug::Jug(int Ca, int Cb, int N ,int cfA, int cfB,int ceA, int ceB, int cpAB, int cpBA){
    this->Ca = Ca;
    this->Cb = Cb;
    this->N = N;
    this->cfA = cfA;
    this->cfB = cfB;
    this->ceA = ceA;
    this->ceB = ceB;
    this->cpAB = cpAB;
    this->cpBA = cpBA;
}

Jug::~Jug(){}

int Jug::solve(string &solution) {

   //CHECK FOR VALID INPUT
   if (Ca > Cb || Cb < 1 || Cb > 1000 || Ca < 1  || N < 0 || N > Cb || cfA < 0 || cfB < 0 || ceA < 0 || ceB < 0 || cpAB < 0 || cpBA < 0) {
      solution = "";
      return -1;
   }

   //ALL RESOURCES
   queue<Vertex> q;
   Vertex initial;
   vector<Vertex> visitedVertices; //tracks vertices already visited by BFS
   vector<Vertex> solPaths; //vector holds all solutions of traversing graph
   Vertex pathA = fillA(initial);
   Vertex pathB = fillB(initial);

   initial.neighbors.push_back(pathA); //mainly used neighbors for debugging. shows which vertices are neighbors of curr vertex
   initial.neighbors.push_back(pathB);

   bool found = false; //used to check if solution 

   visitedVertices.push_back(initial);

   q.push(pathA);
   q.push(pathB);

   while (!q.empty()) {
      Vertex temp = q.front();
      q.pop();

      //CHECK FOR EXISTANCE IN VISITED VERTICES
      if (!search(visitedVertices, temp)) {
         visitedVertices.push_back(temp);
         
         //CHECK IF FINAL
         if (temp.x == 0 && temp.y == N) {
            solPaths.push_back(temp);
            visitedVertices.pop_back();
            found = true;
            continue;
         }
         //OTHERWISE PUSH THE REST INTO THE QUEUE BUT CHECK BEFORE THAT
         Vertex tempfA = fillA(temp);
         if (!search(visitedVertices, tempfA)){
            visitedVertices.at(visitedVertices.size()-1).neighbors.push_back(tempfA);
            q.push(tempfA);
         }

         Vertex tempfB = fillB(temp);
         if (!search(visitedVertices, tempfB)) {
            visitedVertices.at(visitedVertices.size()-1).neighbors.push_back(tempfB);
            q.push(tempfB);
         }

         Vertex tempeA = emptyA(temp);
         if (!search(visitedVertices, tempeA)) {
            visitedVertices.at(visitedVertices.size()-1).neighbors.push_back(tempeA);
            q.push(tempeA);
         }

         Vertex tempeB = emptyB(temp);
         if (!search(visitedVertices, tempeB)) {
            visitedVertices.at(visitedVertices.size()-1).neighbors.push_back(tempeB);
            q.push(tempeB);
         }
         
         Vertex tempAtoB = pourAToB(temp);
         if (!search(visitedVertices, tempAtoB)) {
            visitedVertices.at(visitedVertices.size()-1).neighbors.push_back(tempAtoB);
            q.push(tempAtoB);
         }

         Vertex tempBtoA = pourBToA(temp);
         if (!search(visitedVertices, tempBtoA)) {
            visitedVertices.at(visitedVertices.size()-1).neighbors.push_back(tempBtoA);
            q.push(tempBtoA);
         }
      }
   }
   
   //IF TRUE -> PICK MIN -> fill solution and return 1
   //IF FALSE -> return 0
   if (found) {
      Vertex min = solPaths.at(0);
      if (solPaths.at(0).cost > solPaths.at(1).cost) {
         min = solPaths.at(1);
      }
      for (unsigned i = 0; i < min.path.size(); i++) {
         solution = solution + min.path.at(i) + "\n";
      }
      solution = solution + "success " + to_string(min.cost);
      return 1;
   }
   return 0;
}

bool Jug::search(vector<Vertex> visitedVertices, Vertex v) {
   for (unsigned int i = 0; i < visitedVertices.size(); i++) {
      if (v.x == visitedVertices.at(i).x && v.y == visitedVertices.at(i).y) {
            return true;
      }
   }
   return false;
}

Vertex Jug::fillA(Vertex bef){
    Vertex temp;
    temp.x = Ca;
    temp.y = bef.y;
    temp.cost = bef.cost + cfA;
    temp.path = bef.path;
    temp.path.push_back("fill A");
    return temp;
}

Vertex Jug::fillB(Vertex bef){
    Vertex temp;
    temp.x = bef.x;
    temp.y = Cb;
    temp.cost = bef.cost + cfB;
    temp.path = bef.path;
    temp.path.push_back("fill B");
    return temp;
}

Vertex Jug::pourAToB(Vertex bef){
    Vertex temp;
    int capLeft = Cb - bef.y;
    if (bef.x > capLeft){
        int leftOver = bef.x - capLeft;
        temp.y = Cb;
        temp.x = leftOver;
    }
    else {
        temp.y = bef.x + bef.y;
        temp.x = 0;
    }
    temp.cost = bef.cost + cpAB;
    temp.path = bef.path;
    temp.path.push_back("pour A B");
    return temp;
}

Vertex Jug::pourBToA(Vertex bef){
    Vertex temp;
    int capLeft = Ca - bef.x;
    if (bef.y > capLeft){
        int leftOver = bef.y - capLeft;
        temp.x = Ca;
        temp.y = leftOver;
    }
    else {
        temp.x = bef.y + bef.x;
        temp.y = 0;
    }
    temp.cost = bef.cost + cpBA;
    temp.path = bef.path;
    temp.path.push_back("pour B A");
    return temp;
}

Vertex Jug::emptyA(Vertex bef){
    Vertex temp;
    temp.x = 0;
    temp.y = bef.y;
    temp.cost = bef.cost + ceA;
    temp.path = bef.path;
    temp.path.push_back("empty A");
    return temp;
}

Vertex Jug::emptyB(Vertex bef){
    Vertex temp;
    temp.x = bef.x;
    temp.y = 0;
    temp.cost = bef.cost + ceB;
    temp.path = bef.path;
    temp.path.push_back("empty B");
    return temp;
}