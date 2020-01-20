//
// Created by yael6 on 15/01/2020.
//

#ifndef EX4_JENNY_YAEL_SERVER_H
#define EX4_JENNY_YAEL_SERVER_H

#include "ClientHandler.h"
using namespace std;

namespace server_side {
    template<typename P, typename S>
    class Server {
    public:
        //open the server and wait to customers
        virtual void open(int port, ClientHandler<P,S>* client){};
        //close the server
        virtual void stop(int socketServer){};

    };
}
namespace boot {
    class Main {
    public:
        static int main(int argc, char *argv);
    };
}
#endif //EX4_JENNY_YAEL_SERVER_H
