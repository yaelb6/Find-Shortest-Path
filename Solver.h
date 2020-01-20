//
// Created by yael6 on 15/01/2020.
//

#ifndef EX4_SOLVER_H
#define EX4_SOLVER_H

template <typename P, typename S>
class Solver{
public:
    Solver()= default;;
    virtual ~Solver()= default;;
    virtual S solve(P problem);
};


#endif //EX4_SOLVER_H
