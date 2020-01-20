//
// Created by yael6 on 16/01/2020.
//

#ifndef EX4_STRINGREVERSER_H
#define EX4_STRINGREVERSER_H
using namespace std;

#include <string>
#include <algorithm>
#include "Solver.h"
template<typename P, typename S>
class StringReverser : public Solver<P,S>{
public:
    StringReverser()= default;;
    virtual ~StringReverser()= default;;
    S solve(P problem);
};

template<typename P, typename S>
S StringReverser<P, S>::solve(P problem) {
    string str = problem;
    reverse(str.begin(), str.end());
    return str;
}


#endif //EX4_STRINGREVERSER_H
