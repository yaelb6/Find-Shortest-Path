//
// Created by jenny on 21/01/2020.
//

#ifndef EX4_ASTAR_H
#define EX4_ASTAR_H

#include <set>
#include <tgmath.h>
#include "Searcher.h"
#include <utility>
template<typename T>
class Astar : public Searcher<T>{
private:
    int numOfNodes;
    pair<double, State<T>*> searchInSet(set<pair<double, State<T>*>> set, State<T>* now);
    bool isInSet(set<pair<double, State<T>*>> set, State<T>* now);
    double calculateH(State<T>* now, State<T>* goal);
public:
    Astar();
    virtual ~Astar();
    string search(Searchable<T>* matrix);
    int getNumberOfNodesEvaluated();
};


template<typename T>
string Astar<T>::search(Searchable<T>* matrix) {
    set<pair<double, State<T>*>> openList;
    set<pair<double, State<T>*>> closeList;
    //insert initial state to openList
    openList.insert(make_pair(0.0, matrix->getInitialState()));
    while (!openList.empty()) {
        this->numOfNodes++;
        auto now = openList.begin();
        //check if now has the goal state
        if (matrix->isGoalState(now->second)){
            return Searcher<T>::traceBack(matrix->getGoalState(), matrix->getInitialState());
        }
        //if now doesn't have goal state, we will pass over the adj
        list<State<T>*> adj = matrix->getAllPossibleStates(now->second);
        for (auto iter = adj.begin(); iter != adj.end(); iter++) {
            //if state is in closed list, continue
            if (isInSet(closeList, (*iter))) {
                continue;
            }
//            //if the adj is goal state, update state we came from and call traceBack
//            if (matrix->isGoalState(*iter)) {
//                this->numOfNodes++;
//                (*iter)->setCameFrom(now->second);
//                return Searcher<T>::traceBack(matrix->getGoalState(), matrix->getInitialState());
//            }
            else {
                double h = calculateH((*iter), matrix->getGoalState());
                double f = (h + ((*iter)->getCost()));
                //adding to openList if doesn't exist there
                if (!isInSet(openList, (*iter))) {
                    openList.insert(make_pair(f, *iter));
                    //updating values of state
                    (*iter)->setCameFrom(now->second);
                    (*iter)->setCost((*iter)->getCost() + now->second->getCost());
                }
                //if exist in openList
                else {
                    //if f smaller than the previous f value this state has
                    pair<double, State<T> *> neighbor = searchInSet(openList, (*iter));
                    if (neighbor.first > f) {
                        openList.erase(neighbor);
                        openList.insert(make_pair(f, *iter));
                        //updating values of state
                        (*iter)->setCost((*iter)->getCost() - (*iter)->getCameFrom()->getCost());
                        (*iter)->setCameFrom(now->second);
                        (*iter)->setCost((*iter)->getCost() + now->second->getCost());
                    }
                }
            }
        }
        //deleting from open and insert to close
        openList.erase(*now);
        closeList.insert(*now);
    }
}

template<typename T>
int Astar<T>::getNumberOfNodesEvaluated() {
    return this->numOfNodes;
}

template<typename T>
bool Astar<T>::isInSet(set<pair<double, State<T> *>> set, State<T> * now) {
    for (auto it = set.begin(); it != set.end(); it++)
    {
        State<T>* s = it->second;
        if(s->Equals(now))
            return true;
    }
    return false;
}
template<typename T>
pair<double, State<T>*> Astar<T>::searchInSet(set<pair<double, State<T> *>> set, State<T> * now) {
    for (auto it = set.begin(); it != set.end(); it++)
    {
        State<T>* s = it->second;
        if(s->Equals(now))
            return *it;
    }
}
template<typename T>
double Astar<T>::calculateH(State<T> *now, State<T> *goal) {
    int disX = goal->getState()->getX() - now->getState()->getX();
    int disY = goal->getState()->getY() - now->getState()->getY();

    return (double)sqrt((disX * disX) + (disY *disY));
}

template<typename T>
Astar<T>::Astar() {
    this->numOfNodes = 0;
}

template<typename T>
Astar<T>::~Astar() {
}

#endif //EX4_ASTAR_H
