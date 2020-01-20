//
// Created by yael6 on 15/01/2020.
//
//using namespace std;
//#include "MyTestClientHandler.h"
//#include <sys/socket.h>
//#include <string>
//#include <unistd.h>
//#include <cstring>
//
//template<typename P, typename S>
//void MyTestClientHandler<P, S>::handleClient(int socket) {
//    char buffer[1024] = "";
//    while (read(socket, buffer, 1024) > 0) {
//        //converting char array to string
//        string s = "";
//        for (unsigned int i = 0; i < sizeof(buffer); i++) {
//            if (buffer[i] == '\0') {
//                break;
//            }
//            s = s + buffer[i];
//        }
//        //string is "end", ending connection with client
//        if (s == "end") {
//            close(socket);
//            return;
//        } else {
//            string solution;
//            //if string exist in fileCacheManager
//            if (fileCache->hasSolution(s)) {
//                solution = fileCache->getSolution(s);
//                char* solutionString = const_cast<char *>(solution.c_str());
//                //sending the solution to client
//                send(socket , solutionString , strlen(solutionString) , 0);
//            }
//            //calling the solver to find solution for problem
//            else {
//                solution = solver->solve(s);
//                fileCache->save(solution, s);
//                char* solutionString = const_cast<char *>(solution.c_str());
//                //sending the solution to client
//                send(socket , solutionString , strlen(solutionString) , 0);
//            }
//        }
//    }
//}
//
//
//template<typename P, typename S>
//void MyTestClientHandler<P, S>::setSolver(Solver<P, S>* solver) {
//    this->solver = solver;
//}
//
//template<typename P, typename S>
//void MyTestClientHandler<P, S>::setCache(CacheManager<P, S>* cacheManager) {
//    FileCacheManager<P,S> *fileCache1 = dynamic_cast<FileCacheManager<P,S> *>(cacheManager);
//    if(fileCache1) {
//        this->fileCache = fileCache1;
//    }
//}
//
//template<typename P, typename S>
//MyTestClientHandler<P, S>::MyTestClientHandler(Solver<P, S> *solver, CacheManager<P, S> *cache) {
//    this->solver = solver;
//    auto *fileCache1 = dynamic_cast<FileCacheManager<P,S> *>(cache);
//    if(fileCache1) {
//        this->fileCache = fileCache1;
//    }
//}
//
//template<typename P, typename S>
//MyTestClientHandler<P, S>::MyTestClientHandler() = default;
