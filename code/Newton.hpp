//! Newton.hpp
/*!
  \brief A class constructing an object capable of solving nonlinear systems with the Newton method.
  \author Jaquier, Michael <michael.jaquier@epfl.ch>
  \author Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
  \version 1.0
  \date  10 December 2016
  \remark Ecole Polytechnic Federal de Lausanne (EPFL)
  \remark MATH-458 Programming Concepts in Scientific Computing
*/

#ifndef NEWTON_HPP_
#define NEWTON_HPP_

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "NonlinearSolver.hpp"

class Newton : public NonlinearSolver{
private:
	/// The integer value for the modified Newton method. If m == 1, then the modified Newton method is equivalent to the normal Newton Method.
	int m;

    /// A standard vector holding the strings representing mathematical expressions.
    Expression df;

public:
	/*! A constructor to instantiate variables for the Newtwon method.
     *
     * \param equation An object of the Expression class that contains the mathematical expression for the class to evaluate.
     * \param derivative An object of the Expression class that contains the derivative of the expression for the class to evaluate.
     * \param initial The initial guess of the solution to the equation.
     * \param tolerance The tolerance value.  The method stops once the residual errors fall below this value.
     * \param maxIter The maximum number of iterations.  The method stops once this number is reached.
     * \param verbosity Set to true to print all intermediate and final results onto the console.
     */
	Newton(Expression &equation,
           Expression &derivative,
		   double initial,
		   double tolerance,
		   int maxIter,
		   bool verbosity);

	/*! A constructor to instantiate variables for the modified Newtwon method.
     *
     * \param equation An object of the Expression class that contains the mathematical expression for the class to evaluate.
     * \param derivative An object of the Expression class that contains the derivative of the expression for the class to evaluate.
     * \param initial The initial guess of the solution to the equation.
     * \param tolerance The tolerance value.  The method stops once the residual errors fall below this value.
     * \param maxIter The maximum number of iterations.  The method stops once this number is reached.
     * \param verbosity Set to true to print all intermediate and final results onto the console.
     * \param modifier The integer value for the modified Newton method.
     */
	Newton(Expression &equation,
           Expression &derivative,
           double initial,
		   double tolerance,
		   int maxIter,
		   bool verbosity,
		   int modifier);

    //! A virtual destructor for the Newton method.
    virtual ~Newton();

    /*! A function when called returns the solution to the Newton Method/Modified Newton Method.
     *
     * \return The solution to the Newton Method/Modified Newton Method.
     */
    double solve();

};
    
#endif /* NEWTON_HPP_ */
