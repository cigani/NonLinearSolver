/*
 * AUTHORS:
 * Jaquier, Michael <michael.jaquier@epfl.ch>
 * Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
 */

#ifndef NEWTONSYSTEM_HPP_
#define NEWTONSYSTEM_HPP_

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "NonlinearSystemsSolver.hpp"
#include "ExpressionSystem.hpp"

class NewtonSystem : public NonlinearSystemsSolver {
private:
    ExpressionSystem jac;
    int m;

public:
    NewtonSystem(ExpressionSystem &equation,
                 ExpressionSystem &derivative,
                 std::vector<double> initial,
                 double tolerance,
                 int maxIter,
                 bool verbosity);

    virtual ~NewtonSystem();

    std::vector<double> solve();
};


#endif //NEWTONSYSTEM_HPP_
