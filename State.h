//
// Created by yael6 on 20/01/2020.
//

#ifndef EX4_STATE_H
#define EX4_STATE_H

template<typename T>
class State {
private:
    int index;
    T state;
    double cost;
    State<T>* cameFrom;
public:
    void setIndex(int index);

    void setState(T state);

    void setCost(double cost);

    void setCameFrom(State<T> *cameFrom);

public:
    State(T state1);
    bool Equals(State<T>* s);
    int getIndex();
    double getCost();
};

template<typename T>
State<T>::State(T state1) {
    this->state = state1;
}

template<typename T>
bool State<T>::Equals(State<T>* s) {
    return state.Equals(s->state);
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

#endif //EX4_STATE_H
