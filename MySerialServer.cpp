//
// Created by yael6 on 15/01/2020.
//

#include "MySerialServer.h"
#include "ObjectAdapter.h"
#include "BFS.h"
#include "Point.h"
#include "BestFirstSearch.h"

using namespace std;

template<typename P, typename S>
MySerialServer<P, S>::~MySerialServer() {}

template<typename P, typename S>
void MySerialServer<P, S>::open(int port, ClientHandler<P, S> *client) {

    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
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
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        std::cerr << "Error during listening command" << std::endl;
        return;
    } else {
        std::cout << "Server is now listening ..." << std::endl;
    }
    struct timeval tv;
    tv.tv_sec = 120;
    tv.tv_usec = 0;
    setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv);

    thread thClient(&MySerialServer::acceptClient, this, address, client, socketfd);
    thClient.join();
}

template<typename P, typename S>
void MySerialServer<P, S>::stop(int socketServer) {
    needToStop = true;
    close(socketServer);
}

template<typename P, typename S>
MySerialServer<P, S>::MySerialServer() {

}

template<typename P, typename S>
void MySerialServer<P, S>::acceptClient(sockaddr_in address, ClientHandler<P, S> *client, int socketfd) {
    while (!this->needToStop) {
        int client_socket = accept(socketfd, (struct sockaddr *) &address,
                                   (socklen_t *) &address);

        if (client_socket == -1) {
            std::cerr << "Client wasn't connected for 2 minutes" << std::endl;
            this->stop(socketfd);
        } else {
            std::cout << "Client was connected" << std::endl;
            client->handleClient(client_socket);
            this->stop(socketfd);
        }
    }
}

int boot::Main::main(int argc, char *argv) {
    Server<Matrix<Point*>, string> *server = new MySerialServer<Matrix<Point*>, string>();
    Searcher<Point*> *searcher = new BestFirstSearch<Point*>();
    Solver<Matrix<Point*>, string> *solver = new ObjectAdapter<Matrix<Point*>, string, Point*>(searcher);
    CacheManager<Matrix<Point*>, string> *cache = new FileCacheManager<Matrix<Point*>, string>();
    ClientHandler<Matrix<Point*>, string> *clientHandler = new MyTestClientHandler<Matrix<Point*>, string>(solver, cache);
    server->open(5400, clientHandler);
    std::cout <<searcher->getNumberOfNodesEvaluated()<< std::endl;
    return 0;
}