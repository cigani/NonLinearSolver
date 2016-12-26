//! NonlinearSolver.hpp
/*!
  \brief An abstract class for the family of nonlinear solvers.
  \author Jaquier, Michael <michael.jaquier@epfl.ch>
  \author Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
  \version 1.0
  \date  10 December 2016
  \remark Ecole Polytechnic Federal de Lausanne (EPFL)
  \remark MATH-458 Programming Concepts in Scientific Computing
*/

#ifndef NONLINEARSOLVER_HPP_
#define NONLINEARSOLVER_HPP_

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "Expression.hpp"

class NonlinearSolver {
protected:
	/// An object of the Expression class holding the strings representing mathematical expressions.
    Expression eq;

	/// A doubles representing the initial guess of the solution to the equation.
	double x0;

	/// The tolerance value.  The method stops once the residual errors fall below this value.
	double tol;

	/// The maximum number of iterations.  The method stops once this number is reached.
	int nMax;

	/// Set to true to print all intermediate and final results onto the console.
	bool verbose;

public:
    /*! A contructor to instantiate common variables to the family of nonlinear solvers.
     *
     * \param equation An object of the Expression class that contains the mathematical expression for the class to evaluate.
     * \param initial The initial guess of the solution to the equation.
     * \param tolerance The tolerance value.  The method stops once the residual errors fall below this value.
     * \param maxIter The maximum number of iterations.  The method stops once this number is reached.
     * \param verbosity Set to true to print all intermediate and final results onto the console.
     */
	NonlinearSolver(Expression &equation, double initial,
					double tolerance, int maxIter,
					bool verbosity);

    //! A virtual destructor for the family of nonlinear solvers.
    virtual ~NonlinearSolver();

    //! A pure virtual solver method for the family of nonlinear solvers.
    virtual double solve() = 0;

    /*! A function that takes a constant integer and a vector argument and prints to the console.
     *
     * \param i The current index or iteration to print out to the console.
     * \param x The current solution of the nonlinear problem.
     */
	void printVerbose(int i, double &x);

};
    
#endif /* NONLINEARSOLVER_HPP_ */
