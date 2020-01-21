//
// Created by yael6 on 20/01/2020.
//

#ifndef EX4_SEARCHER_H
#define EX4_SEARCHER_H

#include <vector>
#include <string>
#include "Searcher.h"
#include "Point.h"
#include "Searchable.h"

using namespace std;
template<typename T>
class Searcher {
public:
    virtual string search(Searchable<T> matrix) = 0;
    virtual int getNumberOfNodesEvaluated() = 0;
    string traceBack(State<T>*);
};

template<typename T>
string Searcher<T>::traceBack(State<T> *) {
    return std::__cxx11::string();
}


#endif //EX4_SEARCHER_H
