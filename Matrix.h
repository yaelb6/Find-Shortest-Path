//
// Created by jenny on 21/01/2020.
//

#ifndef EX4_MATRIX_H
#define EX4_MATRIX_H


#include "Searchable.h"

template<typename T>
class Matrix : public Searchable<T> {
private:
    int size;
public:
    State<T> getInitialState();
    bool isGoalState(State<T> v);
    list<State<T>> getAllPossibleStates(State<T> st);
    int getSize();
};

template<typename T>
int Matrix<T>::getSize() {
    return this->size;
}


#endif //EX4_MATRIX_H
