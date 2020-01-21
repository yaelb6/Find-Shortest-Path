//
// Created by yael6 on 20/01/2020.
//

#ifndef EX4_SEARCHER_H
#define EX4_SEARCHER_H

#include <vector>
#include "Searcher.h"
#include "Point.h"
#include "Searchable.h"

using namespace std;

class Searcher {
public:
    template<typename T>
    virtual vector<Point> search(Searchable<T> algoritm) = 0;
};


#endif //EX4_SEARCHER_H
