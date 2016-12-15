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
#include "EquationTools.h"

class NewtonSystem : public NonlinearSystemsSolver {
private:
    /// An object that contains the jacobian of the system.
    ExpressionSystem jac;

    /// The modification parameter for the modified newton method.
    int m;

    /// A class containing linear algebra operators.
    EquationTools convert;

public:
    /// \brief Newton - solver for a system of equations.
    /// \param system - The system of equations
    /// \param jacobian - The jacobian of the system
    /// \param initial -  Initial guess provided by user
    /// \param tolerance -  The numeric tolerance allowed for the solution
    /// \param maxIter -  The maximum iterations allowed for a solution
    /// \param verbosity -  Print intermediate steps
    /// \param mod - Set the modifying power of the Steps.
    NewtonSystem(ExpressionSystem &system,
                 ExpressionSystem &jacobian,
                 std::vector<double> &initial,
                 double tolerance,
                 int maxIter,
                 bool verbosity,
                 int mod);

    //! A virtual destructor for the Newton System method.
    virtual ~NewtonSystem();

    /// \brief solves the system of equations uses recursive calls to Expression class
    /// \return returns a vector of solutions
    std::vector<double> solve();

    /// \brief Applies the newton modification to each element
    /// \param dxyz
    void applyModifier(std::vector<double> &dxyz);
};


#endif //NEWTONSYSTEM_HPP_
