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
#include "Exception.hpp"

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

	x1 = eq.evaluate(x0);  // Any iterative method can be used.  Here we use fixed point method.

	for ( i = 1; i <= nMax; i++ ) {
        x2 = eq.evaluate(x1);

        try {
            phat = x2 - (x2 - x1) * (x2 - x1) / (x2 - 2 * x1 + x0);
            // For when x2 = x0 = -x1 caused by the previous iteration having x0 = -x1.
            if (!std::isfinite(phat)) {
                throw Exception("phat", "The denominator has become 0.  Returning last valid solution.");
            }
        } catch (Exception& error) {
            if (verbose) { error.PrintDebug(); }
            return phatold;
        }

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


