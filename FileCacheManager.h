//
// Created by yael6 on 15/01/2020.
//

#ifndef EX4_FILECACHEMANAGER_H
#define EX4_FILECACHEMANAGER_H

#include "CacheManager.h"
#include <map>
using namespace std;

template<typename P, typename S>
class FileCacheManager : public CacheManager<P,S> {
public:
    map<P, string> problemsMap;
    typename map<P, string>::iterator iter;
    FileCacheManager()= default;;
    virtual ~FileCacheManager()= default;;

    bool hasSolution(P problem) override {
        iter = problemsMap.find(problem);
        if (iter != problemsMap.end()) {
            return true;
        }
        return false;
    }

    void save(string fileName, P problem) override {
        problemsMap.insert(pair<P,string>(problem, fileName));
    }

    string getSolution(P problem) override {
        iter = problemsMap.find(problem);
        if (iter != problemsMap.end()) {
            return iter->second;
        }
        return "";
    }
};


#endif //EX4_FILECACHEMANAGER_H
