//
// Created by jenny on 23/01/2020.
//

#include "MyParallelServer.h"
#include "Server.h"
#include "MyParallelServer.h"
#include "StringReverser.h"
#include "FileCacheManager.h"
#include "MyTestClientHandler.h"
#include "ClientHandler.h"
#include "Astar.h"
#include "ObjectAdapter.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <thread>
#include <pthread.h>

using namespace std;

template<typename P, typename S>
void MyParallelServer<P, S>::open(int portThread, ClientHandler<P, S> *client) {
    this->port = portThread;
    this->clientHandler = client;
    //create socket
    this->socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        return;
    }
    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(port);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
        return;
    }
    //making socket listen to the port
    if (listen(socketfd, 10) == -1) { //can also set to SOMAXCON (max connections)
        std::cerr << "Error during listening command" << std::endl;
        return;
    } else {
        std::cout << "Server is now listening ..." << std::endl;
    }
    acceptClient();
}

//template<typename P, typename S>
//static void *acceptThreadClient(void *fieldsThread) {
//    auto data = (threadInfo<P, S> *) fieldsThread;
//    data->clientHandlerThread->handleClient(data->socket);
//    delete data;
//}

template<typename P, typename S>
void MyParallelServer<P, S>::acceptClient() {
    while (true) {
        struct timeval tv;
        client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);
        fd_set fds;
        // fd_set rfds;
        FD_SET(client_socket, &fds);
        tv.tv_sec = 120;
        setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv);
        if (client_socket == -1) {
            cout << "Client wasn't connected for 2 minutes" << endl;
            stop();
            break;
        } else {
            cout << "Client was connected" << endl;
        }
        setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv);
        auto data = new threadInfo<P, S>;
        data->socket = client_socket;
        data->clientHandlerThread = clientHandler->copy();
        pthread_t thread1;
        if (pthread_create(&thread1, nullptr,&MyParallelServer::acceptThreadClient,data) > 0) {
            cout << "error creating thread" << endl;
        }
        stackOfThreads.push(thread1);
        std::cout << "Client is now connected" << std::endl;
        //clientHandler->handleClient(client_socket);
    }
}

template<typename P, typename S>
void MyParallelServer<P, S>::stop() {
// close the server
    while (!stackOfThreads.empty()) {
        pthread_join(stackOfThreads.top(), nullptr);
        stackOfThreads.pop();
    }
    close(socketfd);
}

template<typename P, typename S>
MyParallelServer<P, S>::MyParallelServer() {
}

template<typename P, typename S>
void *MyParallelServer<P, S>::acceptThreadClient(void *fieldsThread) {
    auto data = (threadInfo<P, S> *) fieldsThread;
    data->clientHandlerThread->handleClient(data->socket);
    delete data;
}

int boot::Main::main(int argc, char *argv) {
    Server<Matrix<Point*>, string> *server = new MyParallelServer<Matrix<Point*>, string>();
    Searcher<Point*> *searcher = new Astar<Point*>();
    Solver<Matrix<Point*>, string> *solver = new ObjectAdapter<Matrix<Point*>, string, Point*>(searcher);
    CacheManager<Matrix<Point*>, string> *cache = new FileCacheManager<Matrix<Point*>, string>();
    ClientHandler<Matrix<Point*>, string> *clientHandler = new MyTestClientHandler<Matrix<Point*>, string>(solver, cache);
    server->open(5401, clientHandler);
    std::cout << searcher->getNumberOfNodesEvaluated() << std::endl;
    return 0;
}

