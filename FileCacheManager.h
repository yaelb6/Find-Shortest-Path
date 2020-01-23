//
// Created by yael6 on 15/01/2020.
//

#ifndef EX4_FILECACHEMANAGER_H
#define EX4_FILECACHEMANAGER_H

#include "CacheManager.h"
#include "Matrix.h"
#include <map>
#include <fstream>

using namespace std;

template<typename P, typename S>
class FileCacheManager : public CacheManager<P,S> {
public:
    map<string, bool> filesMap;
    map<string, bool>::iterator iter;
    hash<string> hashString;
    FileCacheManager()= default;;
    virtual ~FileCacheManager()= default;;
    FileCacheManager<P,S>* copy();
    FileCacheManager(const FileCacheManager &obj);

    bool hasSolution(P problem) override {
        vector<string> matrixString;
        string allString = "";
        Matrix<Point*> *matrix = dynamic_cast<Matrix<Point*>*>(&problem);
        if(matrix) {
            matrixString = matrix->getMatAsString();
            for (unsigned int i = 0; i < matrixString.size(); i++) {
                allString += matrixString[i];
            }
        }
        size_t num = hashString(allString);
        iter = filesMap.find(to_string(num) + ".txt");
        return iter != filesMap.end();
    }

    void save(string fileContent, P problem) override {
        vector<string> matrixString;
        string allString = "";
        Matrix<Point*> *matrix = dynamic_cast<Matrix<Point*>*>(&problem);
        if(matrix) {
            matrixString = matrix->getMatAsString();
            for (unsigned int i = 0; i < matrixString.size(); i++) {
                allString += matrixString[i];
            }
        }
        size_t num = hashString(allString);
        ofstream writeToFile;
        writeToFile.open(to_string(num) + ".txt", ofstream::out);
        writeToFile.write(const_cast<char *>(fileContent.c_str()), fileContent.length());
        writeToFile.close();
        filesMap.insert(make_pair(to_string(num) + ".txt", true));
    }

    string getSolution(P problem) override {
        vector<string> matrixString;
        string allString = "";
        Matrix<Point*> *matrix = dynamic_cast<Matrix<Point*>*>(&problem);
        if(matrix) {
            matrixString = matrix->getMatAsString();
            for (unsigned int i = 0; i < matrixString.size(); i++) {
                allString += matrixString[i];
            }
        }
        size_t num = hashString(allString);
        iter = filesMap.find(to_string(num) + ".txt");
        if (iter != filesMap.end()) {
            return iter->first;
        }
        return "";
    }
};

template<typename P, typename S>
FileCacheManager<P, S> *FileCacheManager<P, S>::copy() {
    return new FileCacheManager(*this);
}
template<typename P, typename S>
FileCacheManager<P,S>::FileCacheManager(const FileCacheManager &obj){
    this->filesMap = obj.filesMap;
    this->iter = obj.iter;
    this->hashString = obj.hashString;
}


#endif //EX4_FILECACHEMANAGER_H
