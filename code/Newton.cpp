/*
 * Newton.cpp
 *
 * DESCRIPTION: Returns the root of an arbitrary nonlinear function using
 *              Newton's method or the modified Newton's method
 *
 * INPUTS:
 *          f        function whose root is to be determined
 *                   must take single argument of type double and return
 *                   single value of type double
 *          df       derivative of function whose root is to be determined
 *                   must take single argument of type double and return
 *                   single value of type double
 *          x0       initial guess for location of root
 *                   type: double
 *          tol      absolute error convergence tolerance
 *                   type: double
 *          nMax     maximum number of iterations to achieve convergence
 *                   type: int
 *          verbose  print intermediate results (default false)
 *                   type: boolean
 *          m        the multiplicity of the zeros of the function known apriori
 *                   type: int
 *
 * OUTPUT:
 *          root     approximate location of root
 *                   type: double
 *
 * Created on: November 27, 2015
 *
 * AUTHORS:
 * Jaquier, Michael <michael.jaquier@epfl.ch>
 * Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
 */

#include "Newton.hpp"
#include "EquationTools.h"
#include "Jacobian.h"
#include "Gauss.h"

Newton::Newton(const std::vector<std::string> &equation,
               std::vector<double> initial,
               double tolerance,
               int maxIter,
               bool verbosity)
	: NonlinearSolver(equation, initial, tolerance, maxIter, verbosity)
{
	m = 1;
}

Newton::Newton(const std::vector<std::string> &equation,
               std::vector<double> initial,
               double tolerance,
               int maxIter,
               bool verbosity,
               int modifier)
	: NonlinearSolver(equation, initial, tolerance, maxIter, verbosity)
{
	m = modifier;
}

Newton::~Newton() {}

double Newton::solve() {
    std::vector<double> dx, fx0, dxyz;
    std::vector<std::vector<double>> dfx0;
    Equations mEquation;
    EquationTools mEquationTools;
    Jacobian mJacobian;
    Gauss mGauss;
    int i;

//    if (verbose) {
//    	printVerbose(0, x0);
//    }

    for (i = 1; i <= nMax; i++) {
        fx0 = mEquationTools.getSystemEquations(eq, x0);
        dfx0 = mJacobian.exprtkJacobian(eq, x0, (int) x0.size());
        mGauss.GaussPartialPivoting(dfx0, fx0);
        dxyz = mGauss.BackwardSolve(dfx0, fx0);
        dx = mEquationTools.addVectors(fx0, dxyz);
        x0 = dx;
        if (verbose) {
        	printVerbose(i, x0);
        }
        if (fabs(dx) < tol) {
            return x0;
        }
    }
    std::cout << "Maximum number of iterations exceeded" << std::endl;
    return x0;
}


