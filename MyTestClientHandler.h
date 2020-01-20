//
// Created by yael6 on 15/01/2020.
//

#ifndef EX4_MYTESTCLIENTHANDLER_H
#define EX4_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include "FileCacheManager.h"

template<typename P, typename S>
class MyTestClientHandler : public ClientHandler<P,S>{
private:
    Solver<P,S>* solver;
    FileCacheManager<P,S>* fileCache;
public:
    MyTestClientHandler(Solver<P,S>* solver, CacheManager<P,S>* cache);
    virtual ~MyTestClientHandler()= default;;
    void handleClient(int socket) override;
    void setCache(CacheManager<P,S>* cacheManager);
    void setSolver(Solver<P,S>* solver);
};


#endif //EX4_MYTESTCLIENTHANDLER_H
