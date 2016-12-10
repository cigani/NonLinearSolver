/* * FixedPoint.cpp * * DESCRIPTION: Returns the fixed point of an arbitrary nonlinear function using *              general fixed point iteration * * INPUTS: *          g        iteration function *                   must take single argument of type double and return *                   single value of type double *          x0       initial guess for location of fixed point *                   type: double *          tol      absolute error convergence tolerance *                   type: double *          nMax     maximum number of iterations to achieve convergence *                   type: int *          verbose  print intermediate results (default false) *                   type: boolean * * OUTPUT: *          point    approximate location of fixed point *                   type: double * * Created on: November 26, 2015 * * AUTHORS: * Jaquier, Michael <michael.jaquier@epfl.ch> * Lorkowski, Alexander <alexander.lorkowski@epfl.ch> */#include "FixedPoint.hpp"FixedPoint::FixedPoint(const std::string &equation,		double initial,		double tolerance,		int maxIter,		bool verbosity)		: NonlinearSolver(equation, initial, tolerance, maxIter, verbosity){}FixedPoint::~FixedPoint() {}double FixedPoint::solve(){	double x1 = 0, error_est;	int i;	Equations mEquation;    if (verbose) {    	printVerbose(0, x0);    }    for (i = 1; i <= nMax; i++) {    	x1 = mEquation.exprtkGenerate2D(eq, x0);    	if (verbose) {    		printVerbose(i, x1);    	}    	error_est = fabs(x1 - x0);    	if ( error_est < tol ) {    		return x1;    	} else {   			x0 = x1;  		}    }    std::cout << "Maximum number of iterations exceeded" << std::endl;    return x0;}