//
// Created by jenny on 21/01/2020.
//

#ifndef EX4_MATRIX_H
#define EX4_MATRIX_H


#include "Searchable.h"
#include "Point.h"
#include <vector>
#include <string>
#include <cstring>


template<typename T>
class Matrix : public Searchable<T> {
private:
    int size;
public:
    Matrix(vector <string> matAsString);

    State<T> *getInitialState();

    bool isGoalState(State<T> *v);

    list<State<T> *> getAllPossibleStates(State<T> *st);

    int getSize();

    State<T> *getGoalState();

    vector <string> split(string &basicString, string basicString1);
};

template<typename T>
int Matrix<T>::getSize() {
    return this->size;

}

template<typename T>
//the constructor recieve vector of strings,
//and create vector of vectors of States.
Matrix<T>::Matrix(vector <string> matAsString) {
    int index=0;
    int row=0;
    vector <string> splitedLine;
    vector<State<T>> line;
    int i=0,j;
    for (auto it = matAsString.begin(); it != matAsString.end(); it++) {
        j=0;
        //split the string by ","
        string splitBy = ",";
        splitedLine = split(*it,splitBy);
        for(auto iter = splitedLine.begin(); iter != splitedLine.end(); iter++) {
            int index1= index;
            index++;
            //the cost is the given number
            double cost1 = stod(*iter);
            Point *statePoint = new Point(i,j);
            j++;
            State<T> *s = new State(index1,statePoint, cost1);
        }
        i++;
    }
}

vector <string> split(string str, string splitBy) {
    vector <string> splited;
    while (str.size() > 0) {
        int i = str.find(splitBy);
        if (i != string::npos) {
            //insert the splites into the vector
            splited.push_back(str.substr(0, i));
            str = str.substr(i + splitBy.size());
            if (str.size() == 0) {
                splited.push_back(str);
            }
        } else {
            splited.push_back(str);
            str = "";
        }
    }
    return splited;
}


#endif //EX4_MATRIX_H
