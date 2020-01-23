//
// Created by yael6 on 15/01/2020.
//

#ifndef EX4_MYTESTCLIENTHANDLER_H
#define EX4_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include "FileCacheManager.h"
#include "ObjectAdapter.h"
#include "Matrix.h"
#include <sys/socket.h>
#include <string>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <fstream>
#include <iostream>
#include <ratio>
#include <thread>
#include "Astar.h"

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
    ClientHandler<P,S>* copy();
    MyTestClientHandler(const MyTestClientHandler &obj);
};

template<typename P, typename S>
void MyTestClientHandler<P, S>::handleClient(int socket) {
    std::cout << "Im in handle" << std::endl;
    char buffer[1024] = "";
    vector<string> vectorString;
    string s = "";
    int count=0;
    chrono::duration<int, milli> d(5000);
    while (read(socket, buffer, 1024) > 0) {
        this_thread::sleep_for(d);
        //converting char array to string
        for (unsigned int i = 0; i < sizeof(buffer); i++) {
            if((buffer[i] == '\0') || (buffer[i] == ' ')){
                continue;
            }
            if (buffer[i] == '\n'){
                //string is "end", ending connection with client
                if (s == "end") {
                    //close(socket);
                    break;
                } else {
                    count++;
                    std::cout << count << std::endl;
                    vectorString.push_back(s);
                    std::cout << s << std::endl;
                    s = "";
                    continue;
                }
            }
            s = s + buffer[i];
        }
        if (s == "end") {
            //close(socket);
            break;
        }
    }
    std::cout << "finish to read" << std::endl;
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
    this_thread::sleep_for(d);
    send(socket , solutionString , strlen(solutionString) , 0);
    close(socket);
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
MyTestClientHandler<P,S>::MyTestClientHandler(const MyTestClientHandler &obj){
    this->solver = new ObjectAdapter<Matrix<Point*>,string,Point*>(new Astar<Point*>());
    this->fileCache = obj.fileCache->copy();
}

//clone
template<typename P, typename S>
ClientHandler<P,S> *MyTestClientHandler<P, S>::copy(){
    return new MyTestClientHandler(*this);
}

#endif //EX4_MYTESTCLIENTHANDLER_H
