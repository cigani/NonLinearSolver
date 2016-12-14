//! FixedPoint.hpp
/*!
  \brief A class constructing an object capable of solving nonlinear systems with the Fixed Point method.
  \author Jaquier, Michael <michael.jaquier@epfl.ch>
  \author Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
  \version 1.0
  \date  10 December 2016
  \remark Ecole Polytechnic Federal de Lausanne (EPFL)
  \remark MATH-458 Programming Concepts in Scientific Computing
*/

#ifndef FIXEDPOINT_HPP_
#define FIXEDPOINT_HPP_

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "NonlinearSolver.hpp"


class FixedPoint : public NonlinearSolver {
public:
    /*! A constructor to instantiate variables for the Fixed Point method.
     *
     * \param equation A string that contains the mathematical expression for the class to evaluate.
     * \param initial The initial guess of the solution to the equation.
     * \param tolerance The tolerance value.  The method stops once the residual errors fall below this value.
     * \param maxIter The maximum number of iterations.  The method stops once this number is reached.
     * \param verbosity Set to true to print all intermediate and final results onto the console.
     */
    FixedPoint(Expression &equation,
               double initial,
               double tolerance,
               int maxIter,
               bool verbosity);

    //! A virtual destructor for the Fixed Point method.
    virtual ~FixedPoint();

    /*! A function that returns the solution to the Fixed Point method.
     *
     * \return The solution to the Fixed Point Method.
     */
    double solve();
    
};
  
#endif /* FIXEDPOINT_HPP_ */

