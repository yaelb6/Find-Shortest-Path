//
// Created by jenny on 21/01/2020.
//

#ifndef EX4_BESTFIRSTSEARCH_H
#define EX4_BESTFIRSTSEARCH_H


#include "Searcher.h"
template<typename T>
class BestFirstSearch  : public Searcher<T>{
    vector<Point> search(Searchable<T> algorithm);
};

template<typename T>
vector<Point> BestFirstSearch<T>::search(Searchable<T> algorithm) {
    return vector<Point>();
}


#endif //EX4_BESTFIRSTSEARCH_H
