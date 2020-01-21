//
// Created by jenny on 21/01/2020.
//

#ifndef EX4_BFS_H
#define EX4_BFS_H

#include "Searcher.h"
template<typename T>
class BFS : public Searcher<T> {
    vector<Point> search(Searchable<T> algorithm);
};

template<typename T>
vector<Point> BFS<T>::search(Searchable<T> algorithm) {
    return vector<Point>();
}

#endif //EX4_BFS_H
