//
// Created by jenny on 21/01/2020.
//

#ifndef EX4_ASTAR_H
#define EX4_ASTAR_H

#include "Searcher.h"
#include "Searcher.h"

class Astar : public Searcher{
    template<typename T>
    vector<Point> search(Searchable<T> algoritm);
};


template<typename T>
vector<Point> Astar::search(Searchable<T> algoritm) {
    return vector<Point>();
}

#endif //EX4_ASTAR_H
