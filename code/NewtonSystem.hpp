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
#include "NonlinearSolver.hpp"
#include "Equations.hpp"

class NewtonSystem : public NonlinearSolver {
private:
    std::vector<std::vector<Expression>> jac;
    int m;

public:
    NewtonSystem(const std::vector<Expression> &equation,
                 const std::vector<std::vector<Expression>> &derivative,
                 std::vector<double> initial,
                 double tolerance,
                 int maxIter,
                 bool verbosity);

    virtual ~NewtonSystem();

    std::vector<double> solve();
};


#endif //NEWTONSYSTEM_HPP_
