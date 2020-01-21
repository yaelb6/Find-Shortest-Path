//
// Created by jenny on 21/01/2020.
//

#ifndef EX4_DFS_H
#define EX4_DFS_H

#include "Searcher.h"
template<typename T>
class DFS : public Searcher<T>{
    vector<Point> search(Searchable<T> algorithm);
};

template<typename T>
vector<Point> DFS<T>::search(Searchable<T> algorithm) {
    return vector<Point>();
}
#endif //EX4_DFS_H
