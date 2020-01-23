//
// Created by yael6 on 20/01/2020.
//

#ifndef EX4_SEARCHABLE_H
#define EX4_SEARCHABLE_H
using namespace std;

#include "State.h"
#include "list"

template<typename T>
class Searchable {
public:
    virtual State<T>* getInitialState() = 0;
    virtual bool isGoalState(State<T>* v) = 0;
    virtual list<State<T>*> getAllPossibleStates(State<T>* st) = 0;
    virtual State<T>* getGoalState() = 0;
};


#endif //EX4_SEARCHABLE_H
