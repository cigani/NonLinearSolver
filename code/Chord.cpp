/*
 * Chord.cpp
 *
 * DESCRIPTION: Returns the root of an arbitrary nonlinear function using
 *              the secant method
 *
 * Created on: November 27, 2015
 *
 * AUTHORS:
 * Jaquier, Michael <michael.jaquier@epfl.ch>
 * Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
 */

#include "Chord.hpp"

Chord::Chord(Expression &equation,
             double initial,
             double tolerance,
             int maxIter,
             bool verbosity)
		: NonlinearSolver(equation, initial, tolerance, maxIter, verbosity)
{}

Chord::~Chord() {}

double Chord::solve() {

    double xnew = 0, dx, fx0, fx1;
    double x1 = x0 + 1;
	int i;

    if (verbose) { printVerbose(0, x0); }

    fx0 = eq.evaluate(x0);

    for ( i = 1; i <= nMax; i++ ) {
    	fx1 = eq.evaluate(x1);
    	dx = fx1 * ( x1 - x0 ) / ( fx1 - fx0 );
    	xnew = x1 - dx;

    	if ( verbose ) { printVerbose(i, xnew); }

    	if (fabs(dx) < tol ) {
            return xnew;
    	} else {
            x0 = x1;
    		fx0 = fx1;
    		x1 = xnew;
        }
    }

    std::cout << "Maximum number of iterations exceeded" << std::endl;
    return xnew;
}
