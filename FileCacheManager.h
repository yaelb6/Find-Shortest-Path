//
// Created by yael6 on 15/01/2020.
//

#ifndef EX4_FILECACHEMANAGER_H
#define EX4_FILECACHEMANAGER_H

#include "CacheManager.h"
#include <map>
#include <fstream>

using namespace std;

template<typename P, typename S>
class FileCacheManager : public CacheManager<P,S> {
public:
    map<string, bool> filesMap;
    map<string, bool>::iterator iter;
    hash<string> hashString;
    FileCacheManager()= default;;
    virtual ~FileCacheManager()= default;;

    bool hasSolution(P problem) override {
        size_t num = hashString(problem);
        iter = filesMap.find(to_string(num) + ".txt");
        return iter != filesMap.end();
    }

    void save(string fileName, P problem) override {
        size_t num = hashString(problem);
        filesMap.insert(make_pair(to_string(num) + ".txt", true));
    }

    string getSolution(P problem) override {
        iter = filesMap.find(problem);
        if (iter != filesMap.end()) {
            return iter->first;
        }
        return "";
    }
};


#endif //EX4_FILECACHEMANAGER_H
