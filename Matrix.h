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
#include <list>


template<typename T>
class Matrix : public Searchable<T> {
private:
    vector <vector<State<T>>> matrix;
    State<T> *initial;
    State<T> *goal;
    int size;

public:

    Matrix(vector <string> matAsString);

    State<T> *getInitialState();

    bool isGoalState(State<T> *v);

    list<State<T> *> getAllPossibleStates(State<T> *st);

    int getSize();

    State<T> *getGoalState();

    vector <string> split(string str, string splitBy);
};

template<typename T>
int Matrix<T>::getSize() {
    return this->size;

}

template<typename T>
//the constructor recieve vector of strings,
//and create vector of vectors of States.
Matrix<T>::Matrix(vector <string> matAsString) {
    vector <vector<State<T>>> mtx;
    int index = 0;
    int i = 0, j;
    for(int k=0;k<matAsString.size()-2;k++){
        vector <string> splitedLine;
        vector <State<T>> line;
        j = 0;
        //split the string by ","
        string splitBy = ",";
        splitedLine = split(matAsString[k], splitBy);
        for (auto iter = splitedLine.begin(); iter != splitedLine.end(); iter++) {
            int index1 = index;
            index++;
            //the cost is the given number
            double cost1 = stod(*iter);
            Point *statePoint = new Point(i, j);
            j++;
            State<Point *> *s = new State<Point *>(index1, statePoint, cost1);
            line.push_back(s);
        }
        i++;
        mtx.push_back(line);
    }
    this->matrix = mtx;
    vector <string> splitInitial = split(matAsString[size-2], ",");
    int xInitial = stoi(splitInitial[0]);
    int yInitial = stoi(splitInitial[1]);
    this->initial = matrix[xInitial][yInitial];
    vector <string> splitGoal = split(matAsString[size-1], ",");
    int xGoal = stoi(splitInitial[0]);
    int yGoal = stoi(splitInitial[1]);
    this->goal = matrix[xGoal][yGoal];
}

template<typename T>
State<T> *Matrix<T>::getInitialState() {
    return initial;
}

template<typename T>
bool Matrix<T>::isGoalState(State<T> *v) {
    //check if v is the goal state
    return v->Equals(goal);
}

template<typename T>
list<State<T> *> Matrix<T>::getAllPossibleStates(State<T> *st) {
    list < State<Point *> * > adj;
    typename list<State<T> *>::iterator it;
    //the edges are the matrix size
    int maxCol = size - 1;
    int maxRow = size - 1;
    int minCol = 0;
    int minRow = 0;
    //the state cordinates
    int i = st->getState().getX();
    int j = st->getState().getY();
    Point *up = new Point(i - 1, j);
    Point *right = new Point(i, j + 1);
    Point *left = new Point(i, j - 1);
    Point *down = new Point(i + 1, j);
    //check if every neighbour is legal
    //up neighbour
    if ((up->getX() >= minRow) && (matrix[i - 1][j] != -1)) {
        adj.push_back(matrix[i - 1][j]);
    }
    //right neighbour
    if ((right->getY() <= maxCol) && (matrix[i][j + 1] != -1)) {
        adj.push_back(matrix[i][j + 1]);
    }
    //left neighbour
    if ((left->getY() >= minCol) && (matrix[i][j - 1] != -1)) {
        adj.push_back(matrix[i][j - 1]);
    }
    //down neighbour
    if ((down->getY() <= maxRow) && (matrix[i + 1][j] != -1)) {
        adj.push_back(matrix[i + 1][j]);
    }
    return adj;
}

template<typename T>
vector <string> Matrix<T>::split(string str, string splitBy) {
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
