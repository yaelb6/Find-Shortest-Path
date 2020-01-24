//
// Created by jenny on 23/01/2020.
//

#ifndef EX4_MYPARALLELSERVER_H
#define EX4_MYPARALLELSERVER_H

#include "Server.h"
#include "Solver.h"
#include "FileCacheManager.h"
#include "MyTestClientHandler.h"
#include "MyParallelServer.h"
#include "ClientHandler.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <netinet/in.h>
#include <thread>
#include <stack>
#include <chrono>
#include <unistd.h>





using namespace server_side;

template<typename P, typename S>
class MyParallelServer : public Server<P, S> {
private:
    struct fieldsThread {
        int sockfd;
        ClientHandler<P, S> *clientHandler;
    };
    stack<pthread_t> stackOfThreads;
    struct fieldsThread *fields = new fieldsThread;
public:
    bool needToStop = false;
    MyParallelServer();
    int client_socket;
    int port;
    int socketfd;
    sockaddr_in address;
    ClientHandler<P,S> *clientHandler;
    static void *acceptThreadClient(void *fieldsThread);
    void open(int port, ClientHandler<P,S> *c);
    void acceptClient(sockaddr_in address, ClientHandler<P, S> *client, int socketfd);
    void acceptClient();
    void start();
    void stop();
};

template<typename P, typename S>
class threadInfo {
public:
    threadInfo() {}
    int socket;
    ClientHandler<P,S> *clientHandlerThread;
};

#endif //EX4_JENNY_YAEL_MYSERIALSERVER_H
