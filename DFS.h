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
private:
    int numOfNodes;
    bool finishRecur;
public:
    string search(Searchable<T>* matrix);
    void DFSRecursive(State<T>* v, bool visited[], Searchable<T>* matrix);
    int getNumberOfNodesEvaluated();

    virtual ~DFS();

    DFS();
};

template<typename T>
string DFS<T>::search(Searchable<T>* matrix) {
    int size;
    auto *isMatrix = dynamic_cast<Matrix<T>*>(matrix);
    if(isMatrix) {
        size = isMatrix->getSize();
        size = size * size;
    }
    //initialize not visited to all states
    bool *visited = new bool[size];
    for (int i = 0; i < size; i++) {
        visited[i] = false;
    }
    //calling recursive function of dfs with the initialState
    DFSRecursive(matrix->getInitialState(), visited, matrix);
    return Searcher<T>::traceBack(matrix->getGoalState(), matrix->getInitialState());
}

template<typename T>
void DFS<T>::DFSRecursive(State<T>* v, bool *visited, Searchable<T>* matrix) {
    //update the state was visited and insert to vector path
    int index = v->getIndex();
    visited[index] = true;
    if (matrix->isGoalState(v)) {
        this->finishRecur = true;
        return;
    } else if (!this->finishRecur){
        list<State<T> *> adj = matrix->getAllPossibleStates(v);
        typename list<State<T> *>::iterator iter;
        for (iter = adj.begin(); iter != adj.end(); iter++) {
            int adjIndex = (*iter)->getIndex();
            if (!visited[adjIndex]) {
                this->numOfNodes++;
                (*iter)->setCameFrom(v);
                (*iter)->setCost(v->getCost() + (*iter)->getCost());
                DFSRecursive(*iter, visited, matrix);
            }
        }
    }
}

template<typename T>
int DFS<T>::getNumberOfNodesEvaluated() {
    return this->numOfNodes;
}

template<typename T>
DFS<T>::DFS() {
    this->numOfNodes = 0;
    this->finishRecur = false;
}

template<typename T>
DFS<T>::~DFS() {

}

#endif //EX4_DFS_H
