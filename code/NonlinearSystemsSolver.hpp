//! NonlinearSystemsSolver.hpp
/*!
  \brief An abstract class for the family of solvers of nonlinear systems.
  \author Jaquier, Michael <michael.jaquier@epfl.ch>
  \author Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
  \version 1.0
  \date  10 December 2016
  \remark Ecole Polytechnic Federal de Lausanne (EPFL)
  \remark MATH-458 Programming Concepts in Scientific Computing
*/

#ifndef NONLINEARSYSTEMSSOLVER_HPP_
#define NONLINEARSYSTEMSSOLVER_HPP_

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "Expression.hpp"
#include "ExpressionSystem.hpp"

class NonlinearSystemsSolver {
protected:
	/// A standard vector holding the strings representing mathematical expressions.
	ExpressionSystem system;

	/// A standard vector holding the doubles representing the initial guess of the solution to the equation.
	std::vector<double> v0;

	/// The tolerance value.  The method stops once the residual errors fall below this value.
	double tol;

	/// The maximum number of iterations.  The method stops once this number is reached.
	int nMax;

	/// Set to true to print all intermediate and final results onto the console.
	bool verbose;

public:

    /*! A contructor to instantiate common variables to the family of nonlinear solvers.
     *
     * \param sys An ExpressionSystem object containing the system of equations.
     * \param initial The initial guess of the solution to the equation.
     * \param tolerance The tolerance value.  The method stops once the residual errors fall below this value.
     * \param maxIter The maximum number of iterations.  The method stops once this number is reached.
     * \param verbosity Set to true to print all intermediate and final results onto the console.
     */
    NonlinearSystemsSolver(
			ExpressionSystem &sys,
			std::vector<double> &initial,
            double tolerance,
            int maxIter,
            bool verbosity);

    //! A virtual destructor for the family of nonlinear solvers.
    virtual ~NonlinearSystemsSolver();

    //! A pure virtual solver method for the family of nonlinear solvers.
    virtual std::vector<double> solve() = 0;

    /*! A function that takes a constant integer and a vector argument and prints to the console.
     *
     * \param i The current index or iteration to print out to the console.
     * \param v The vector that contains current solution of the nonlinear problem.
     */
	void printVerbose(int i, std::vector<double> &v);

};
    
#endif /* NONLINEARSYSTEMSSOLVER_HPP_ */
