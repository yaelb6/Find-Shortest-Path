//
// Created by yael6 on 20/01/2020.
//

#ifndef EX4_STATE_H
#define EX4_STATE_H

#include "Point.h"
template<typename T>
class State {
private:
    int index;
    T state;
    double cost;
    State<T>* cameFrom;
public:
    T getState();

    State<T> *getCameFrom();

    void setIndex(int index);

    void setState(T state);

    void setCost(double cost);

    void setCameFrom(State<T> *cameFrom);

    State(int index1,T point, double cost1);

    bool Equals(State<T>* s);
    int getIndex();
    double getCost();
};
template<typename T>
State<T>::State(int index1,T point,double cost1) {
    this->index= index1;
    this->state = point;
    this->cost = cost1;
    this->cameFrom = nullptr;
}

template<typename T>
bool State<T>::Equals(State<T>* s) {
    return state->Equals(s->getState());
}

template<typename T>
int State<T>::getIndex() {
    return this->index;
}

template<typename T>
double State<T>::getCost() {
    return this->cost;
}

template<typename T>
void State<T>::setIndex(int index) {
    State::index = index;
}

template<typename T>
void State<T>::setState(T state) {
    State::state = state;
}

template<typename T>
void State<T>::setCost(double cost) {
    State::cost = cost;
}

template<typename T>
void State<T>::setCameFrom(State<T> *cameFrom) {
    State::cameFrom = cameFrom;
}

template<typename T>
T State<T>::getState() {
    return this->state;
}

template<typename T>
State<T> *State<T>::getCameFrom() {
    return this->cameFrom;
}


#endif //EX4_STATE_H
