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

Aitken::Aitken() {}

Aitken::~Aitken() {}

double Aitken::aitkenSolver(std::vector<double> &coef,
                            double x0,
                            double tol,
                            int nMax,
                            bool verbose)
{
    double x1, x2, phat = 0, phatold;
	int i;
	Equations mEquation;
	phatold = x0;
	if (verbose) {
		printVerbose(0,x0);
	}

	x1 = Equations::getPolyEquation(coef, x0);
	if (verbose) {
		printVerbose(1,x1);
	}
  
	if ( fabs(x1-x0) < tol ) {
		return x1;
	} else {
		x0 = x1;
	}
  
	for ( i = 2; i <= nMax; i++ ) {
		x2 = Equations::getPolyEquation(coef, x1);
		phat = x2 - ( x2 - x1 ) * ( x2 - x1 ) / ( x2 - 2 * x1 + x0 );
		if (verbose) {
			printVerbose(i,x2);
		}
		if ( fabs(phatold - phat) < tol ) {
			return phat;
		} else {
			phatold = phat;  x0 = x1;  x1 = x2;
		}
	}
	std::cout << "Maximum number of iterations exceeded" << std::endl;
	return phat;
}

double Aitken::aitkenExprtkSolver(const std::string &eq,
                            double x0,
                            double tol,
                            int nMax,
                            bool verbose)
{
    double x1, x2, phat = 0, phatold;
	int i;
	Equations mEquation;
	phatold = x0;
	if (verbose) {
		printVerbose(0,x0);
	}

	x1 = mEquation.exprtkGenerate2D(eq, x0);
	if (verbose) {
		printVerbose(1,x1);
	}

	if ( fabs(x1-x0) < tol ) {
		return x1;
	} else {
		x0 = x1;
	}

	for ( i = 2; i <= nMax; i++ ) {
		x2 = mEquation.exprtkGenerate2D(eq, x1);
		phat = x2 - ( x2 - x1 ) * ( x2 - x1 ) / ( x2 - 2 * x1 + x0 );
		if (verbose) {
			printVerbose(i,x2);
		}
		if ( fabs(phatold - phat) < tol ) {
			return phat;
		} else {
			phatold = phat;  x0 = x1;  x1 = x2;
		}
	}
	std::cout << "Maximum number of iterations exceeded" << std::endl;
	return phat;
}

void Aitken::printVerbose(int i, double &x) {
	std::cout << std::setw(3) << i << "\t"  << std::setw(20)
	<< x << std::setprecision(15) << std::endl;
}

