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

Aitken::Aitken(Expression &equation,
               double initial,
               double tolerance,
               int maxIter,
               bool verbosity)
		: NonlinearSolver(equation, initial, tolerance, maxIter, verbosity)
{}

Aitken::~Aitken() {}

double Aitken::solve() {

    double x1, x2, phat = 0, phatold;
    int i;

    phatold = x0;

	if (verbose) { printVerbose(0, phatold); }

	x1 = eq.evaluate(x0);

	if (verbose) { printVerbose(1, x1); }

    if (fabs(x1 - x0) < tol) {
        return x1;
	} else {
        x0 = x1;
	}

	for ( i = 2; i <= nMax; i++ ) {
        x2 = eq.evaluate(x1);
        phat = x2 - (x2 - x1) * (x2 - x1) / (x2 - 2 * x1 + x0);

		if (verbose) { printVerbose(i, phat); }

		if ( fabs(phatold - phat) < tol ) {
            return phat;
		} else {
            phatold = phat;
            x0 = x1;
            x1 = phat;
		}
	}

	std::cout << "Maximum number of iterations exceeded" << std::endl;
    return phat;
}


