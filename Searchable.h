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
    virtual State<T> getInitialState() = 0;
    virtual State<T> isGoalState() = 0;
    virtual list<State<T>> getAllPossibleStates(State<T> st) = 0;
};


#endif //EX4_SEARCHABLE_H
