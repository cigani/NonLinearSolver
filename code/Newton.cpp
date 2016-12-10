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

Newton::Newton(const std::vector<Expression> &equation,
               const std::vector<Expression> &derivative,
               std::vector<double> initial,
               double tolerance,
               int maxIter,
               bool verbosity)
	: NonlinearSolver(equation, initial, tolerance, maxIter, verbosity)
{
    df = derivative;
	m = 1;
}

Newton::Newton(const std::vector<Expression> &equation,
               const std::vector<Expression> &derivative,
               std::vector<double> initial,
               double tolerance,
               int maxIter,
               bool verbosity,
               int modifier)
	: NonlinearSolver(equation, initial, tolerance, maxIter, verbosity)
{
    df = derivative;
	m = modifier;
}

Newton::~Newton() {}

std::vector<double> Newton::solve() {
    double dx, fx0, dfx0;
    Expression singleEq = eq.at(0);

    if (verbose) {
    	printVerbose(0, x0);
    }

    for (int i = 1; i <= nMax; i++) {

        fx0 = singleEq.evaluate(x0);
        dfx0 = singleEq.evaluate(x0);
        dx = fx0 / dfx0;

        for(int i=0; i < x0.size(); i++){
            x0[i] -= m*dx;
        }

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

//std::vector<double> Newton::solveSystem() {
//    std::vector<double> dx, fx0, dxyz, fxNeg;
//    std::vector<std::vector<double>> dfx0;
//    double prevNorm, nextNorm;
//    Equations mEquation;
//    EquationTools mEquationTools;
//    Jacobian mJacobian;
//    Gauss mGauss;
//
//    if (verbose) {
//    	printVerbose(0, x0);
//    }
//
//    for (int i = 1; i <= nMax; i++) {
//        prevNorm = mEquationTools.getNorm(x0);
//        fx0 = mEquationTools.getSystemEquations(eq, x0);
//        dfx0 = mJacobian.exprtkJacobian(eq, x0, (int) x0.size());
//        fxNeg = mEquationTools.negateVector(fx0);
//        mGauss.GaussPartialPivoting(dfx0, fxNeg);
//        dxyz = mGauss.BackwardSolve(dfx0, fxNeg);
//        dx = mEquationTools.addVectors(fx0, dxyz);
//        x0 = dx;
//        nextNorm = mEquationTools.getNorm(x0);
//        //if (verbose) {
//        //	printVerbose(i, x0);}
//        if (fabs(prevNorm - nextNorm) < tol) {
//            return x0;
//        }
//    }
//    std::cout << "Maximum number of iterations exceeded" << std::endl;
//    return x0;
//}



