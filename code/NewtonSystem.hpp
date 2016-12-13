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
#include "Expression.hpp"
#include "ExpressionSystem.hpp"

class NewtonSystem : public NonlinearSystemsSolver {
private:
    ExpressionSystem jac;
    int m;

public:
    NewtonSystem(ExpressionSystem &system,
                 ExpressionSystem &jacobian,
                 std::vector<double> initial,
                 double tolerance,
                 int maxIter,
                 bool verbosity);

    virtual ~NewtonSystem();

    std::vector<double> solve();

    void iteratate(std::vector<std::vector<double>> &dfx0,
                   std::string name) const;

    void iteratate(std::vector<double> &fxNeg, std::string name) const;

    std::vector<double> convertMatrix2Vector(const std::vector<std::vector<double>> &fx0) const;
};


#endif //NEWTONSYSTEM_HPP_
