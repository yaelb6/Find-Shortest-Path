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
    vector<State<T>> search(Searchable<T> matrix);
};

template<typename T>
vector<State<T>> BFS<T>::search(Searchable<T> matrix) {
    vector<State<T>> path;
    int size = 0;
    State<T> initial, node, goal;
    auto *mtx = dynamic_cast<Matrix<T> *>(matrix);
    if (mtx) {
        size = mtx->getSize();
        initial = mtx->getInitialState();
    }
    bool *visited = new bool[size*size];
    //initialize all the vertices as not visited
    for (int i = 0; i < size*size; i++) {
        visited[i] = false;
    }
    //define queue and its iterator
    list<State<T>> queue;
    typename list<State<T>>::iterator it;

    //mark the first as visited
    visited[initial.getIndex()] = true;
    queue.push_back(initial);
    while (!queue.empty()){
        //remove the current node from dequqe
        node = queue.front();
        path.push_back(node);
        queue.pop_front();
        //if the current node is the goal
        if(matrix.isGoalState(node)){
            return path;
        }
        else {
            list<State<T>> adj = matrix.getAllPossibleStates(node);
            for (it=adj.begin(); it!=adj.end(); it++){
                if (!visited[it->getIndex()]){
                    visited[it->getIndex()] = true;
                    queue.push_back(it);
                }
            }
        }
    }
}

#endif //EX4_BFS_H
