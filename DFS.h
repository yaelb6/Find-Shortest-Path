//
// Created by jenny on 21/01/2020.
//

#ifndef EX4_DFS_H
#define EX4_DFS_H

#include "Searcher.h"
#include "Matrix.h"
using namespace std;

template<typename T>
class DFS : public Searcher<T>{
    vector<State<T>> search(Searchable<T> matrix);
    void DFSRecursive(State<T> v, bool visited[], vector<State<T>> vector[], Searchable<T> matrix);
};

template<typename T>
vector<State<T>> DFS<T>::search(Searchable<T> matrix) {
    vector <State<T>> vectorStates;
    int size;
    auto *isMatrix = dynamic_cast<Matrix<T>*>(matrix);
    if(isMatrix) {
        size = isMatrix->getSize();
        size = size * size;
    }
    //initialize not visited to all states
    bool *visited = new bool[size];
    for (int i = 0; i < size; i++) {
        visited[size] = false;
    }
    //calling recursive function of dfs with the initialState
    DFSRecursive(matrix->getInitialState(), visited, &vectorStates);
    return vectorStates;
}

template<typename T>
void DFS<T>::DFSRecursive(State<T> v, bool *visited, vector <State<T>> *vector, Searchable<T> matrix) {
    //update the state was visited and insert to vector path
    int index = v.getIndex();
    visited[index] = true;
    vector->push_back(v);
    if (matrix.isGoalState(v)) {
        return;
    }
    list<State<T>> adj = matrix.getAllPossibleStates(v);
    typename list<State<T>>::iterator iter;
    for(iter = adj.begin(); iter != adj.end(); ++iter){
        //if it's a block adj
        if(iter->getCost() == -1) {
            continue;
        }
        int adjIndex = iter->getIndex();
        if (!visited[adjIndex]) {
            DFSRecursive(iter, visited, vector, matrix);
        }
    }
}

#endif //EX4_DFS_H
