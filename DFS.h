//
// Created by jenny on 21/01/2020.
//

#ifndef EX4_DFS_H
#define EX4_DFS_H

#include "Searcher.h"
#include "Searcher.h"

class DFS : public Searcher{
    template<typename T>
    vector<Point> search(Searchable<T> algoritm);
};

template<typename T>
vector<Point> DFS::search(Searchable<T> algoritm) {
    return vector<Point>();
}
#endif //EX4_DFS_H
