//
// Created by yael6 on 15/01/2020.
//

#ifndef EX4_CLIENTHANDLER_H
#define EX4_CLIENTHANDLER_H


#include "CacheManager.h"
#include "Solver.h"
template<typename P, typename S>
class ClientHandler {

public:
    ClientHandler()= default;
    virtual void handleClient(int socket) = 0;
    virtual void setCache(CacheManager<P,S>* cacheManager) = 0;
    virtual void setSolver(Solver<P,S>* solver) = 0;
    virtual ~ClientHandler()= default;
};


#endif //EX4_CLIENTHANDLER_H
