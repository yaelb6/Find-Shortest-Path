//
// Created by yael6 on 20/01/2020.
//

#ifndef EX4_SEARCHER_H
#define EX4_SEARCHER_H

#include <deque>
#include <string>
#include "Searcher.h"
#include "Point.h"
#include "Searchable.h"

using namespace std;
template<typename T>
class Searcher {
public:
    virtual string search(Searchable<T> matrix) = 0;
    virtual int getNumberOfNodesEvaluated() = 0;
    string traceBack(State<T>* current, State<T> *intial);
};

template<typename T>
string Searcher<T>::traceBack(State<T> *current, State<T> *initial) {
    deque<State<T>*> path;
    string pathCost = "";
    //insert goal state to deque
    path.push_front(current);
    //while loop that insert all the path states to the deque
    while (!current->Equals(initial)) {
        path.push_front(current->getCameFrom());
        current = current ->getCameFrom();
    }
    //for loop that goes over the deque and make the string of path and costs that need to be printed to a file
    for (unsigned int i = 0; i < path.size() -1; i++) {
        int currX, currY, nextX, nextY;
        State<T>* curr = path[i];
        State<T>* next = path[i+1];
        currX = curr->getState()->getX();
        currY = curr->getState()->getY();
        nextX = next->getState()->getX();
        nextY = next->getState()->getY();
        //if step is Up
        if (currX == nextX + 1) {
            pathCost += "Up (" + next->getCost() + ")";
        }
        //if step is Down
        else if (currX == nextX - 1) {
            pathCost += "Down (" + next->getCost() + ")";
        }
        //if step is Right
        else if (currY == nextY - 1) {
            pathCost += "Right (" + next->getCost() + ")";
        }
        //if step is Left
        else {
            pathCost += "Left (" + next->getCost() + ")";
        }
        //add comma after every step, except if it's the last step
        if (i != path.size() - 2) {
            pathCost += " ,";
        }
    }
    pathCost+="\n"
    return pathCost;
}


#endif //EX4_SEARCHER_H
