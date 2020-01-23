//
// Created by jenny on 21/01/2020.
//

#ifndef EX4_BFS_H
#define EX4_BFS_H

#include "Searcher.h"
#include "State.h"
#include "Matrix.h"
#include<iostream>
#include <list>

using namespace std;

template<typename T>
class BFS : public Searcher<T> {
private:
    int numOfNodes;
public:
    string search(Searchable<T>* matrix);

    BFS();

    virtual ~BFS();

    int getNumberOfNodesEvaluated();
};

template<typename T>
string BFS<T>::search(Searchable<T>* matrix) {
    int size = 0;
    State<T> *initial, *node;
    auto *mtx = dynamic_cast<Matrix<T> *>(matrix);
    if (mtx) {
        size = mtx->getSize();
        initial = mtx->getInitialState();
    }
    bool *visited = new bool[size * size];
    //initialize all the vertices as not visited
    for (int i = 0; i < size * size; i++) {
        visited[i] = false;
    }
    //define queue and its iterator
    list<State<T> *> queue;
    typename list<State<T> *>::iterator it;

    //mark the first as visited
    visited[initial->getIndex()] = true;
    this->numOfNodes++;
    queue.push_back(initial);
    while (!queue.empty()) {
        //remove the current node from queue
        node = queue.front();
        queue.pop_front();
        //if the current node is the goal
        if (matrix->isGoalState(node)) {
            return Searcher<T>::traceBack(matrix->getGoalState(), matrix->getInitialState());
        } else {
            list<State<T> *> adj = matrix->getAllPossibleStates(node);
            for (it = adj.begin(); it != adj.end(); it++) {
                if (!visited[(*it)->getIndex()]) {
                    (*it)->setCameFrom(node);
                    (*it)->setCost(node->getCost() + (*it)->getCost());
                    visited[(*it)->getIndex()] = true;
                    this->numOfNodes++;
                    queue.push_back(*it);
                }
            }
        }
    }
}

template<typename T>
int BFS<T>::getNumberOfNodesEvaluated() {
    return this->numOfNodes;
}

template<typename T>
BFS<T>::BFS() {
    this->numOfNodes = 0;
}

template<typename T>
BFS<T>::~BFS() {

}

#endif //EX4_BFS_H
