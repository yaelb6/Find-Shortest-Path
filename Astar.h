//
// Created by jenny on 21/01/2020.
//

#ifndef EX4_ASTAR_H
#define EX4_ASTAR_H

#include "Searcher.h"
template<typename T>
class Astar : public Searcher<T>{

    vector<Point> search(Searchable<T> algorithm);
};


template<typename T>
vector<Point> Astar<T>::search(Searchable<T> algorithm) {
    return vector<Point>();
}

#endif //EX4_ASTAR_H
