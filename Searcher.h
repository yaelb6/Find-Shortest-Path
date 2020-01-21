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
template<typename T>
class Searcher {
public:
    virtual string search(Searchable<T> matrix) = 0;
    virtual int getNumberOfNodesEvaluated() = 0;
    string traceBack(vector<State<T>*>);
};

template<typename T>
string Searcher<T>::traceBack(State<T> *) {
    //create the trace back from the given goal

}


#endif //EX4_SEARCHER_H
