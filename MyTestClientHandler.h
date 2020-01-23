//
// Created by yael6 on 15/01/2020.
//

#ifndef EX4_MYTESTCLIENTHANDLER_H
#define EX4_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include "FileCacheManager.h"
#include "Matrix.h"
#include <sys/socket.h>
#include <string>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <fstream>

template<typename P, typename S>
class MyTestClientHandler : public ClientHandler<P,S>{
private:
    Solver<P,S>* solver;
    FileCacheManager<P,S>* fileCache;
public:
    MyTestClientHandler();
    MyTestClientHandler(Solver<P,S>* solver, CacheManager<P,S>* cache);
    virtual ~MyTestClientHandler()= default;;
    void handleClient(int socket) override;
    void setCache(CacheManager<P,S>* cacheManager);
    void setSolver(Solver<P,S>* solver);
};

template<typename P, typename S>
void MyTestClientHandler<P, S>::handleClient(int socket) {
    char buffer[1024] = "";
    vector<string> vectorString;
    while (read(socket, buffer, 1024) > 0) {
        //converting char array to string
        string s = "";
        for (unsigned int i = 0; i < sizeof(buffer); i++) {
            if (buffer[i] == '\n') {
                break;
            }
            s = s + buffer[i];
        }
        //string is "end", ending connection with client
        if (s == "end") {
            close(socket);
            break;
        } else {
            vectorString.push_back(s);
        }
    }
    Matrix<Point*> *matrix = new Matrix<Point*>(vectorString);

    string fileName, solToClient, contentFile;
    //if string exist in fileCacheManager
    if (fileCache->hasSolution(*matrix)) {
        //return file name
        fileName = fileCache->getSolution(*matrix);
    }
    //calling the solver to find solution for problem
    else {
        //return file content
        contentFile = solver->solve(*matrix);
        //save file in cache
        fileCache->save(contentFile, *matrix);
        //return file name
        fileName = fileCache->getSolution(*matrix);
    }
    ifstream readSolution(fileName);
    if (readSolution) {
        getline(readSolution, solToClient);
    }
    readSolution.close();
    char* solutionString = const_cast<char *>(solToClient.c_str());
    //sending the solution to client
    send(socket , solutionString , strlen(solutionString) , 0);
}


template<typename P, typename S>
void MyTestClientHandler<P, S>::setSolver(Solver<P, S>* solver) {
    this->solver = solver;
}

template<typename P, typename S>
void MyTestClientHandler<P, S>::setCache(CacheManager<P, S>* cacheManager) {
    FileCacheManager<P,S> *fileCache1 = dynamic_cast<FileCacheManager<P,S> *>(cacheManager);
    if(fileCache1) {
        this->fileCache = fileCache1;
    }
}

template<typename P, typename S>
MyTestClientHandler<P, S>::MyTestClientHandler(Solver<P, S> *solver, CacheManager<P, S> *cache) {
    this->solver = solver;
    auto *fileCache1 = dynamic_cast<FileCacheManager<P,S> *>(cache);
    if(fileCache1) {
        this->fileCache = fileCache1;
    }
}

template<typename P, typename S>
MyTestClientHandler<P, S>::MyTestClientHandler() = default;


#endif //EX4_MYTESTCLIENTHANDLER_H
