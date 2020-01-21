//
// Created by yael6 on 20/01/2020.
//

#ifndef EX4_STATE_H
#define EX4_STATE_H

template<typename T>
class State {
private:
    int index;
public:
    int getIndex() const;

private:
    T state;
    double cost;
    State<T> cameFrom;
public:
    State(T state1);
    bool Equals(State<T> s);
};

template<typename T>
State<T>::State(T state1) {
    this->state = state1;
}

template<typename T>
bool State<T>::Equals(State<T> s) {
    return state.Equals(s.state);
}

template<typename T>
int State<T>::getIndex() const {
    return index;
}


#endif //EX4_STATE_H
