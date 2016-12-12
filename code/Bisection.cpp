/*
 * Bisection.cpp
 *
 * DESCRIPTION: Returns the root of an arbitrary nonlinear function using
 *                          the bisection method
 *
 * INPUTS:
 *          f        function whose root is to be determined
 *                   must take single argument of type double and return
 *                   single value of type double
 *          a        left bound of interval known to contain root
 *                   type: double
 *          b       right bound of interval known to contain root
 *                   type: double
 *          tol     absolute error convergence tolerance
 *                   type: double
 *          nMax maximum number of iterations to achieve convergence
 *                   type: int
 *          verbose  print intermediate results (default false)
 *                       type: bool
 *
 * OUTPUT:
 *          root   approximate location of root
 *                   type: double
 *
 *
 * Created on: November 27, 2015
 *
 * AUTHORS:
 * Jaquier, Michael <michael.jaquier@epfl.ch>
 * Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
 */

#include "Bisection.hpp"

Bisection::~Bisection() {}


Bisection::Bisection(Expression &equation,
                     double initial,
                     double tolerance,
                     int maxIter,
                     bool verbosity)
        : NonlinearSolver(equation, initial, tolerance, maxIter, verbosity)
{
	a = -1;
	b = 1;
}

Bisection::Bisection(Expression &equation,
                     double initial,
                     double tolerance,
                     int maxIter,
                     bool verbosity,
                     double lowerBound,
                     double upperBound)
        : NonlinearSolver(equation, initial, tolerance, maxIter, verbosity)
{
	a = lowerBound;
	b = upperBound;
}

double Bisection::solve() {
    double sign_fa, sign_fb, sign_mp, midpoint, prev_midpoint = 0, error_est;
    int i;

    sign_fa = getSign(eq.evaluate(a));
    sign_fb = getSign(eq.evaluate(b));

    assert ( (sign_fa *  sign_fb) < 0 );

    for ( i = 1; i <= nMax; i++ ) {
        midpoint = a + (b - a)/2.0;

        if ( verbose ) {
            printVerbose(i, midpoint);
        }

        sign_mp = getSign(eq.evaluate(midpoint));

        if  ( sign_fa *  sign_mp < 0 ) {
            b = midpoint;
            sign_fb = sign_mp;
        } else if  ( sign_fb *  sign_mp < 0 ) {
            a = midpoint;
            sign_fa = sign_mp;
        } else {
            return midpoint;
        }

        if (i > 2){
            error_est = fabs(midpoint - prev_midpoint);
            if ( fabs(error_est) < tol ) {
                return midpoint;
            }
        }
         prev_midpoint = midpoint;
    }

    std::cout << "Maximum number of iterations exceeded" << std::endl;
    return midpoint;
}

double Bisection::getSign(double value){
	double sign;
	if (value > 0) {
		sign = 1.0;
	} else if (value < 0) {
		sign = -1.0;
	} else {
		sign = 0.0;
	}
	return sign;
}
