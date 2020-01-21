//
// Created by jenny on 21/01/2020.
//

#ifndef EX4_MATRIX_H
#define EX4_MATRIX_H


#include "Searchable.h"

template<typename T>
class Matrix : public Searchable<T> {
public:
    int size;
    State<T> getInitialState();
    State<T> isGoalState();
    list<State<T>> getAllPossibleStates(State<T> st);
};


#endif //EX4_MATRIX_H
