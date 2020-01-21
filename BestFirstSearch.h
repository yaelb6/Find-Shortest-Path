//
// Created by jenny on 21/01/2020.
//

#ifndef EX4_BESTFIRSTSEARCH_H
#define EX4_BESTFIRSTSEARCH_H


#include "Searcher.h"

class BestFirstSearch  : public Searcher{
    template<typename T>
    vector<Point> search(Searchable<T> algoritm);
};

template<typename T>
vector<Point> BestFirstSearch::search(Searchable<T> algoritm) {
    return vector<Point>();
}


#endif //EX4_BESTFIRSTSEARCH_H
