//! Bisection.hpp
/*!
  \brief A class constructing an object capable of solving nonlinear systems with the Bisection method.
  \author Jaquier, Michael <michael.jaquier@epfl.ch>
  \author Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
  \version 1.0
  \date  10 December 2016
  \remark Ecole Polytechnic Federal de Lausanne (EPFL)
  \remark MATH-458 Programming Concepts in Scientific Computing
*/

#ifndef BISECTION_HPP_
#define BISECTION_HPP_

#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>
#include <cmath>
#include "NonlinearSolver.hpp"
#include "Expression.hpp"

class Bisection : public NonlinearSolver{
private:
    /*! A method that returns the sign of an expression evaluated at the provided value.
     *
     * \param value The value at which to evaluate this object's mathematical expression.
     * \return 1 if the evaluation is positive.  -1 if the evalutaion is negative.
     */
	double getSign(double value);

    /// The lower bound on the domain where the program looks for the solution.
	double a;

    /// The upper bound on the domain where the program looks for the solution.
	double b;

public:
    //! A virtual destructor for the Bisection method.
	virtual ~Bisection();

	/*! A constructor to instantiate variables for the Bisection method.  The default bound is [-1,1].
     *
     * \param equation An object of the Expression class that contains the mathematical expression for the class to evaluate.
     * \param initial The initial guess of the solution to the equation.
     * \param tolerance The tolerance value.  The method stops once the residual errors fall below this value.
     * \param maxIter The maximum number of iterations.  The method stops once this number is reached.
     * \param verbosity Set to true to print all intermediate and final results onto the console.
     */
    Bisection(Expression &equation,
              double initial,
              double tolerance,
              int maxIter,
              bool verbosity);

	/*! A constructor to instantiate variables for the Bisection method.
     *
     * \param equation An object of the Expression class that contains the mathematical expression for the class to evaluate.
     * \param initial The initial guess of the solution to the equation.
     * \param tolerance The tolerance value.  The method stops once the residual errors fall below this value.
     * \param maxIter The maximum number of iterations.  The method stops once this number is reached.
     * \param verbosity Set to true to print all intermediate and final results onto the console.
     * \param lowerBound The lower bound on the domain where the program looks for the solution.
     * \param upperBound The upper bound on the domain where the program looks for the solution.
     */
    Bisection(Expression &equation,
              double initial,
              double tolerance,
              int maxIter,
              bool verbosity,
              double lowerBound,
              double upperBound);

    /*! A function that returns the solution to the Bisection method.
     *
     * \return The solution to the Bisection Method.
     */
	double solve();

};

#endif /* BISECTION_HPP_ */
