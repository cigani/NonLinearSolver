/*
 * FixedPoint.cpp
 *
 * DESCRIPTION: Returns the fixed point of an arbitrary nonlinear function using
 *              general fixed point iteration
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
 * Created on: November 26, 2015
 *    Author: Alexander Lorkowski <alexander.lorkowski@epfl.ch>
 */

#include "FixedPoint.hpp"

FixedPoint::FixedPoint() {}
FixedPoint::~FixedPoint() {}

double FixedPoint::fixedPointSolver ( func1arg g,
				      double x0,
				      double tol,
				      int nMax,
				      bool verbose )
{
	double x1 = 0, xm1 = 0, lambda, error_est;
	int i;

	if (verbose) {
		std::cout << std::setw(3) << 0 << "\t"  << std::setw(20)
		<< x0 << std::setprecision(15) << std::endl;
	}
  
	for ( i = 1; i <= nMax; i++ ) {
		x1 = g(x0);
		if (verbose) {
			std::cout << std::setw(3) << i << "\t" << std::setw(20)
			<< x1 << std::setprecision(15) << std::endl;
		}
         
		if ( i > 2 ) {
			lambda = ( x1 - x0 ) / ( x0 - xm1 );
			error_est = lambda / ( 1 - lambda ) * ( x1 - x0 );
			if ( fabs(error_est) < tol ) {
				return x1;
			}
		}

		xm1 = x0;
		x0 = x1;
	}
	std::cout << "Maximum number of iterations exceeded" << std::endl;
	return x1;
}
