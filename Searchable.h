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
    State<T> getInitialState();
    State<T> isGoalState();
    list<State<T>> getAllPossibleStates(State<T> st);
};

template<typename T>
State<T> Searchable<T>::getInitialState() {
    return State<T>(T());
}

template<typename T>
list<State<T>> Searchable<T>::getAllPossibleStates(State<T> st) {
    return list<State<T>>();
}

template<typename T>
State<T> Searchable<T>::isGoalState() {
    return State<T>(T());
}


#endif //EX4_SEARCHABLE_H
