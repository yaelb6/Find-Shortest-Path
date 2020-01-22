//
// Created by jenny on 21/01/2020.
//

#ifndef EX4_BESTFIRSTSEARCH_H
#define EX4_BESTFIRSTSEARCH_H


#include <string>
#include "Searcher.h"
#include "Matrix.h"

template<typename T>
class BestFirstSearch : public Searcher<T> {
private:
    int numOfNodes;
public:
    BestFirstSearch();

    virtual ~BestFirstSearch();

    string search(Searchable<T> matrix);
    int getNumberOfNodesEvaluated();
};

template<typename T>
string BestFirstSearch<T>::search(Searchable<T> matrix) {
    int size = 0;
    State<T> *initial;
    State<T> *node;
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
    list<State<T> *> priorityQueue;
    typename list<State<T> *>::iterator it;

    //mark the first as visited
    visited[initial->getIndex()] = true;
    this->numOfNodes++;
    priorityQueue.push_back(initial);
    while (!priorityQueue.empty()) {
        //remove the current node from queue
        node = priorityQueue.front();
        priorityQueue.pop_front();
        //if the current node is the goal
        if (matrix.isGoalState(node)) {
            return traceBack(node);
        } else {
            list<State<T> *> adj = matrix.getAllPossibleStates(node);
            for (it = adj.begin(); it != adj.end(); it++) {
                if (it->getCost() == -1) {
                    continue;
                }
//                it->setCameFrom(node);
//                it->setCost(node->getCost() + it->getCost());
                if ((!visited[it->getIndex()]) && (!contains(priorityQueue, node))) {
                    node = it;
                    priorityQueue.push_back(it);
                    this->numOfNodes++;
                }
                    //if the state is not in visited but in open,
                    //check is the min cost is already the cost
                else if (!visited[it->getIndex()]) {
                    visited[it->getIndex()] = true;
                    this->numOfNodes++;
                    saveMinVal(priorityQueue, node);
                }
            }
        }
    }
}

template<typename T>
BestFirstSearch<T>::BestFirstSearch() {
    this->numOfNodes = 0;
}

template<typename T>
BestFirstSearch<T>::~BestFirstSearch() {

}

template<typename T>
int BestFirstSearch<T>::getNumberOfNodesEvaluated() {
    return this->numOfNodes;
}

template<typename T>
bool contains(list<State<T> *> queue, State<T> currentState) {
    for (auto it = queue.begin(); it != queue.end(); it++) {
        State<T> *s = *it;
        if (s->Equals(currentState))
            return true;
    }
    return false;
}

template<typename T>
void saveMinVal(list<State<T> *> queue, State<T> node) {
    for (auto it = queue.begin(); it != queue.end(); it++) {
        State<T> *s = *it;
        if (s->Equals(node)) {
            if (node.getCost() < s->getCost()) {
                queue.erase(it);
                queue.insert(node);
            }
            return;
        }
    }
    queue.insert(node);
    return;
}


#endif //EX4_BESTFIRSTSEARCH_H
