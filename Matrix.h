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
    vector <vector<State<T>*>> matrix;
    vector<string> matAsString;
public:
    void setMatAsString(const vector <string> &matAsString);

public:
    const vector <string> &getMatAsString() const;

private:
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
    vector <vector<State<T>*>> mtx;
    int index = 0;
    int i = 0, j;
    setMatAsString(matAsString);
    for(int k=0;k<matAsString.size()-2;k++){
        vector <string> splitedLine;
        vector <State<T>*> line;
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
    this->size = i;
    vector <string> splitInitial = split(matAsString[size], ",");
    int xInitial = stoi(splitInitial[0]);
    int yInitial = stoi(splitInitial[1]);
    this->initial = matrix[xInitial][yInitial];
    vector <string> splitGoal = split(matAsString[size+1], ",");
    int xGoal = stoi(splitGoal[0]);
    int yGoal = stoi(splitGoal[1]);
    this->goal = matrix[xGoal][yGoal];
}

template<typename T>
State<T> *Matrix<T>::getInitialState() {
    return initial;
}

template<typename T>
bool Matrix<T>::isGoalState(State<T> *v) {
    //check if v is the goal state
    return v->Equals(this->goal);
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
    int i, j;
    //the state cordinates
    i = st->getState()->getX();
    j = st->getState()->getY();
    Point *up = new Point(i - 1, j);
    Point *right = new Point(i, j + 1);
    Point *left = new Point(i, j - 1);
    Point *down = new Point(i + 1, j);
    //check if every neighbour is legal
    //down neighbour
    if ((down->getX() <= maxRow) && (matrix[i + 1][j]->getCost() != -1)) {
        adj.push_back(matrix[i + 1][j]);
    }
    //right neighbour
    if ((right->getY() <= maxCol) && (matrix[i][j + 1]->getCost() != -1)) {
        adj.push_back(matrix[i][j + 1]);
    }
    //up neighbour
    if ((up->getX() >= minRow) && (matrix[i - 1][j]->getCost() != -1)) {
        adj.push_back(matrix[i - 1][j]);
    }
    //left neighbour
    if ((left->getY() >= minCol) && (matrix[i][j - 1]->getCost() != -1)) {
        adj.push_back(matrix[i][j - 1]);
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

template<typename T>
const vector <string> &Matrix<T>::getMatAsString() const {
    return matAsString;
}

template<typename T>
void Matrix<T>::setMatAsString(const vector <string> &matAsString) {
    Matrix::matAsString = matAsString;
}

template<typename T>
State<T> *Matrix<T>::getGoalState() {
    return this->goal;
}


#endif //EX4_MATRIX_H
