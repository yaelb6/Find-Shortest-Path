//
// Created by yael6 on 15/01/2020.
//

#ifndef EX4_JENNY_YAEL_MYSERIALSERVER_H
#define EX4_JENNY_YAEL_MYSERIALSERVER_H

#include "Server.h"
#include "StringReverser.h"
#include "FileCacheManager.h"
#include "MyTestClientHandler.h"
#include "ClientHandler.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <thread>

using namespace server_side;
template<typename P, typename S>
class MySerialServer : public Server<P,S>{
public:
    bool needToStop = false;
    MySerialServer();
    void open(int port, ClientHandler<P,S>* client) override;
    void acceptClient(sockaddr_in address, ClientHandler<P,S>* client, int socketfd);
    void stop(int socketServer) override;
    virtual ~MySerialServer();
};


#endif //EX4_JENNY_YAEL_MYSERIALSERVER_H
