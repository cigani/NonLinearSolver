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
#include "Equations.hpp"

FixedPoint::FixedPoint() {}
FixedPoint::~FixedPoint() {}

double FixedPoint::fixedPointSolver (const std::vector<double>& coef,
				      double x0,
				      double tol,
				      int nMax,
				      bool verbose )
{
	double x1 = 0, error_est;
	int i;
	Equations mEquation;

	std::vector<double> phi_coef(coef);
	phi_coef[1] = phi_coef[1] + 1;

	if (verbose) {
		std::cout << std::setw(3) << 0 << "\t"  << std::setw(20)
		<< x0 << std::setprecision(15) << std::endl;
	}
  
	for ( i = 1; i <= nMax; i++ ) {
		//x1 = mEquation.getEquation(phi_coef, x0);
        x1 = mEquation.getCosine(x0);

		if (verbose) {
			std::cout << std::setw(3) << i << "\t" << std::setw(20)
			<< x1 << std::setprecision(15) << std::endl;
		}

		error_est = fabs(x1 - x0);
		if ( error_est < tol ) {
			return x1;
		} else {
			x0 = x1;
		}
	}
	std::cout << "Maximum number of iterations exceeded" << std::endl;
	return x1;
}
