//
// Created by yael6 on 15/01/2020.
//

#ifndef EX4_CACHEMANAGER_H
#define EX4_CACHEMANAGER_H
#include <map>
using namespace std;

template<typename P, typename S>
class CacheManager {
public:
    map<P,S> problemsMap;
    CacheManager()= default;;
    virtual ~CacheManager()= default;;
    virtual bool hasSolution(P problem) = 0;
    virtual void save(S solution, P problem) = 0;
    virtual S getSolution(P problem) = 0;
};


#endif //EX4_CACHEMANAGER_H
