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

    string search(Searchable<T> *matrix);

    int getNumberOfNodesEvaluated();

    bool contains(list<State<T> *> queue, State<T> *currentState);

    void saveMinVal(list<State<T> *> queue, State<T> *node);
};

template<typename T>
string BestFirstSearch<T>::search(Searchable<T> *matrix) {
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


    this->numOfNodes++;
    priorityQueue.push_back(initial);
    while (!priorityQueue.empty()) {
        //remove the current node from queue
        node = priorityQueue.front();
        this->numOfNodes++;
        priorityQueue.pop_front();
        visited[node->getIndex()] = true;
        //if the current node is the goal
        if (matrix->isGoalState(node)) {
            return Searcher<T>::traceBack(matrix->getGoalState(), matrix->getInitialState());
        } else {
            list<State<T> *> adj = matrix->getAllPossibleStates(node);
            for (it = adj.begin(); it != adj.end(); it++) {
                if ((!visited[(*it)->getIndex()]) && (!contains(priorityQueue, (*it)))) {
                    (*it)->setCameFrom(node);
                    (*it)->setCost(node->getCost() + (*it)->getCost());
                    priorityQueue.push_back(*it);
                }
                    //if the state is not in visited but in open,
                    //check is the min cost is already the cost
                else if (!visited[(*it)->getIndex()]) {
                    State<T> *temp = *it;
                    temp->setCost(temp->getCost() - temp->getCameFrom()->getCost() + node->getCost());
                    temp->setCameFrom(node);
                    saveMinVal(priorityQueue, temp);
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
bool BestFirstSearch<T>::contains(list<State<T> *> queue, State<T> *currentState) {
    for (auto it = queue.begin(); it != queue.end(); it++) {
        State<T> *s = *it;
        if (s->Equals(currentState))
            return true;
    }
    return false;
}

template<typename T>
void BestFirstSearch<T>::saveMinVal(list<State<T> *> queue, State<T> *temp) {
    for (auto it = queue.begin(); it != queue.end(); it++) {
        State<T> *s = *it;
        if (s->Equals(temp)) {
            if (temp->getCost() < s->getCost()) {
                queue.erase(it);
                queue.push_back(temp);
            }
            return;
        }
    }
//    queue.push_back(temp);
//    return;
}


#endif //EX4_BESTFIRSTSEARCH_H
