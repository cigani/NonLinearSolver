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
    /// \brief Newton - solver for a system of equations.
    /// \param system - The system of equations
    /// \param jacobian - The jacobian of the system
    /// \param initial -  Initial guess provided by user
    /// \param tolerance -  The numeric tolerance allowed for the solution
    /// \param maxIter -  The maximum iterations allowed for a solution
    /// \param verbosity -  Print intermediate steps
    NewtonSystem(ExpressionSystem &system,
                 ExpressionSystem &jacobian,
                 std::vector<double> &initial,
                 double tolerance,
                 int maxIter,
                 bool verbosity,
                 int mod);

    virtual ~NewtonSystem();

    /// \brief solves the system of equations uses recurisve calls to Expression class
    /// \return returns a vector of solutions
    std::vector<double> solve();

    /// \brief Printing out the intermediate steps for debugging
    /// \param dfx0
    /// \param name
    void iteratate(std::vector<std::vector<double>> &dfx0,
                   std::string name) const;

    /// \brief Printing out the intermediate steps for debugging
    /// \param fxNeg
    /// \param name
    void iteratate(std::vector<double> &fxNeg, std::string name) const;

    /// \brief Converts a nested vectors to a single vector
    /// \param fx0
    /// \return A single vector [ ex., Matrix[2][2] -> Vector[4] ]
    std::vector<double> convertMatrix2Vector(const std::vector<std::vector<double>> &fx0) const;

    /// \brief Applies the newton modification to each element
    /// \param dxyz
    void applyModifier(std::vector<double> &dxyz);
};


#endif //NEWTONSYSTEM_HPP_
