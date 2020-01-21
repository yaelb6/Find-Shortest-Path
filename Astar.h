//
// Created by jenny on 21/01/2020.
//

#ifndef EX4_ASTAR_H
#define EX4_ASTAR_H

#include "Searcher.h"
template<typename T>
class Astar : public Searcher<T>{

    vector<State<T>*> search(Searchable<T> matrix);
};


template<typename T>
vector<State<T>*> Astar<T>::search(Searchable<T> matrix) {

    return vector<Point>();
}

#endif //EX4_ASTAR_H
