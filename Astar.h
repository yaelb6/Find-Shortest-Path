//
// Created by jenny on 21/01/2020.
//

#ifndef EX4_ASTAR_H
#define EX4_ASTAR_H

#include <set>
#include <tgmath.h>
#include "Searcher.h"
template<typename T>
class Astar : public Searcher<T>{
private:
    int numOfNodes = 0;
    bool isInSet(set<pair<double, State<T>*>> set, State<T>* now);
    double calculateH(State<T>* now, State<T>* goal);
public:
    string search(Searchable<T> matrix);
    int getNumberOfNodesEvaluated();
};


template<typename T>
string Astar<T>::search(Searchable<T> matrix) {
    set<pair<double, State<T>*>> openList;
    set<pair<double, State<T>*>> closeList;
    //insert initial state to openList
    openList.insert(make_pair(0.0, matrix.getInitialState()));
    while (!openList.empty()) {
        //deleting from open and insert to close
        auto now = openList.begin();
        openList.erase(now);
        closeList.insert(now);

        //check if now has the goal state
        if (matrix.isGoalState(now->second)){
            return traceBack(matrix.getGoalState());
        }
        //if now doesn't have goal state, we will pass over the adj of the state now has
        list<State<T>*> adj = matrix.getAllPossibleStates(now->second);
        for (auto iter = adj.begin(); iter != adj.end(); iter++) {
            //if state is in closed list or is blocked, continue
            if ((!isInSet(closeList, iter)) || (iter->getCost() == -1)) {
                continue;
            }
            //if the adj is goal state, update state we came from and call traceBack
            if (matrix.isGoalState(iter)) {
                iter->setCameFrom(now->second);
                return traceBack(iter);
            }
            else {
                double h = calculateH(iter, matrix.getGoalState());
                double f = (h + (iter->getCost()));
                //adding to openList if doesn't exist there or if exist but f smaller than now->first(previous f value)
                if ((!isInSet(openList, iter)) || ((isInSet(openList, iter)) && (f < now->first))) {
                    openList.insert(make_pair(f, iter));
                    //updating values of state
                    iter->setCameFrom(now->second);
                    iter->setCost(iter->getCost + now->second->getCost());
                }
            }
        }
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
double Astar<T>::calculateH(State<T> *now, State<T> *goal) {
    int disX = goal->getState()->getX() - now->getState()->getX();
    int disY = goal->getState()->getY() - now->getState()->getY();

    return (double)sqrt((disX * disX) + (disY *disY));
}

#endif //EX4_ASTAR_H
