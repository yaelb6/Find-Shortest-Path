//
// Created by yael6 on 20/01/2020.
//

#ifndef EX4_OBJECTADAPTER_H
#define EX4_OBJECTADAPTER_H


#include "Solver.h"
#include "Searcher.h"

template<typename P, typename S, typename T>
class ObjectAdapter : public Solver<P, S> {
private:
    Searcher<T>* searcher;
public:
//    ObjectAdapter(const Searcher<T> &searcher) : searcher(searcher) {
//        this->searcher = searcher;
//    }
    ObjectAdapter(Searcher<T>* searcher) {
        this->searcher = searcher;
    }
    virtual ~ObjectAdapter() {}

    const Searcher<T> &getSearcher() const {
        return searcher;
    }

    void setSearcher(const Searcher<T> &searcher) {
        ObjectAdapter::searcher = searcher;
    }

    S solve(P problem) {
        Searchable<T> *searchable = dynamic_cast<Searchable<T> *>(&problem);
        if (searchable) {
            return searcher->search(searchable);
        }
    }
};


#endif //EX4_OBJECTADAPTER_H
