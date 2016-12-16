//! Aitken.hpp
/*!
  \brief A class constructing an object capable of solving nonlinear systems with the Aitken method.
  \author Jaquier, Michael <michael.jaquier@epfl.ch>
  \author Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
  \version 1.0
  \date  10 December 2016
  \remark Ecole Polytechnic Federal de Lausanne (EPFL)
  \remark MATH-458 Programming Concepts in Scientific Computing
*/

#ifndef AITKEN_HPP_
#define AITKEN_HPP_

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "Expression.hpp"
#include "NonlinearSolver.hpp"

class Aitken : public NonlinearSolver{
public:
    /*! A constructor to instantiate variables for the Aitken method.
     *
     * \param equation An object of the Expression class that contains the mathematical expression for the class to evaluate.
     * \param initial The initial guess of the solution to the equation.
     * \param tolerance The tolerance value.  The method stops once the residual errors fall below this value.
     * \param maxIter The maximum number of iterations.  The method stops once this number is reached.
     * \param verbosity Set to true to print all intermediate and final results onto the console.
     */
    Aitken(Expression &equation,
           double initial,
           double tolerance,
           int maxIter,
           bool verbosity);

    //! A virtual destructor for the Aitken method.
    virtual ~Aitken();

    /*! A function when called returns the solution to the Aitken Method.
     *
     * \return The solution to the Aitken Method.
     */
    double solve();
};
    
#endif /* AITKEN_HPP_ */
