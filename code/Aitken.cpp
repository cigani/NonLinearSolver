/*
 * Aitken.cpp
 *
 * DESCRIPTION: Acceleration technique applied to the fixed point method to find the 
 *              roots of an arbitrary nonlinear function
 *
 * Created on: November 21, 2016
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

    if (fabs(x1 - x0) < tol) {
        return x1;
	} else {
        x0 = x1;
	}

	for ( i = 2; i <= nMax; i++ ) {
        x2 = eq.evaluate(x1);
        phat = x2 - (x2 - x1) * (x2 - x1) / (x2 - 2 * x1 + x0);

		if (verbose) { printVerbose(i-1, phat); }

		if ( fabs(phatold - phat) < tol ) {
            return phat;
		} else {
            phatold = phat;
            x0 = x1;
            x1 = x2;
		}
	}

	std::cout << "Maximum number of iterations exceeded" << std::endl;
    return phat;
}


