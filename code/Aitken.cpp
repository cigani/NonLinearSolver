/*
 * Aitken.cpp
 *
 * DESCRIPTION: Acceleration technique applied to the fixed point method to find the 
 *              roots of an arbitrary nonlinear function
 *
 * INPUTS:
 *          g        iteration function
 *                   must take single argument of type double and return
 *                   single value of type double
 *          x0       initial guess for location of fixed point
 *                   type: double
 *          tol      absolute error convergence tolerance
 *                   type: double
 *          nMax     maximum number of iterations to achieve convergence
 *                   type: int
 *          verbose  print intermediate results (default false)
 *                   type: boolean
 *
 * OUTPUT:
 *          point    approximate location of fixed point
 *                   type: double
 *
 * Created on: November 21, 2015
 *
 * AUTHORS:
 * Jaquier, Michael <michael.jaquier@epfl.ch>
 * Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
 */

#include "Aitken.hpp"
#include "Equations.hpp"

Aitken::Aitken(std::vector<Expression> &equation,
               std::vector<double> initial,
               double tolerance,
               int maxIter,
               bool verbosity)
		: NonlinearSolver(equation, initial, tolerance, maxIter, verbosity)
{}

Aitken::~Aitken() {}

std::vector<double> Aitken::solve() {

    std::vector<double> returnVec;
    Expression singleEq = eq.at(0);

    double singleValue = x0.at(0);
    double x1, x2, phat, phatold;
    int i;

    phatold = singleValue;

	if (verbose) {
        printVerbose(0, x0.at(0));
	}

	x1 = singleEq.evaluate(singleValue);

	if (verbose) {
		printVerbose(1,x1);
	}

    if (fabs(x1 - singleValue) < tol) {
        returnVec.push_back(x1);
        return returnVec;
	} else {
        singleValue = x1;
	}

	for ( i = 2; i <= nMax; i++ ) {
        x2 = singleEq.evaluate(x1);
        phat = x2 - (x2 - x1) * (x2 - x1) / (x2 - 2 * x1 + singleValue);
		if (verbose) {
			printVerbose(i, phat);
		}
		if ( fabs(phatold - phat) < tol ) {
            returnVec.push_back(phat);
            return returnVec;
		} else {
            phatold = phat;
            singleValue = x1;
            x1 = x2;
		}
	}
	std::cout << "Maximum number of iterations exceeded" << std::endl;
    returnVec.push_back(phat);
    return returnVec;
}


