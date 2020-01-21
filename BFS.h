//
// Created by jenny on 21/01/2020.
//

#ifndef EX4_BFS_H
#define EX4_BFS_H

#include "Searcher.h"
#include "Searcher.h"

class BFS : public Searcher {
    template<typename T>
    vector<Point> search(Searchable<T> algoritm);
};

template<typename T>
vector<Point> BFS::search(Searchable<T> algoritm) {
    return vector<Point>();
}

#endif //EX4_BFS_H
