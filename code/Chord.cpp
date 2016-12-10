/*
 * Chord.cpp
 *
 * DESCRIPTION: Returns the root of an arbitrary nonlinear function using
 *              the secant method
 *
 * INPUTS:
 *          f        function whose root is to be determined
 *                   must take single argument of type double and return
 *                   single value of type double
 *          x0       one initial guess for location of root
 *                   type: double
 *          x1       another initial guess for location of root
 *                   type: double
 *          tol      absolute error convergence tolerance
 *                   type: double
 *          nMax     maximum number of iterations to achieve convergence
 *                   type: int
 *          verbose  print intermediate results (default false)
 *                   type: bool
 *
 * OUTPUT:
 *          root     approximate location of root
 *                   type: double
 *
 *
 * Created on: November 27, 2015
 *
 * AUTHORS:
 * Jaquier, Michael <michael.jaquier@epfl.ch>
 * Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
 */

#include "Chord.hpp"

Chord::Chord(const std::vector<std::string> &equation,
             std::vector<double> initial,
             double tolerance,
             int maxIter,
             bool verbosity)
		: NonlinearSolver(equation, initial, tolerance, maxIter, verbosity)
{}

Chord::~Chord() {}

std::vector<double> Chord::solve() {
    std::vector<double> returnVec;
    std::vector<double> print;
    double singleVal = x0.at(0);
    std::string singleEq = (std::basic_string<char, std::char_traits<char>,
            std::allocator<char>> &&) eq.at(0);
	double xnew, dx , fx0, fx1;
    double x1 = singleVal + 1;
	int i;

	Equations mEquation;

    if (verbose) {
        print.push_back(x1);
    	printVerbose(0, x0);
        printVerbose(1, print);
        print.clear();
    }

    fx0 = mEquation.exprtkGenerate2D(singleEq, singleVal);
    for ( i = 2; i <= nMax; i++ ) {
        fx1 = mEquation.exprtkGenerate2D(singleEq, x1);
        dx = fx1 * (x1 - singleVal) / (fx1 - fx0);
    	xnew = x1 - dx;
    	if ( verbose ) {
            print.push_back(xnew);
            printVerbose(i, print);
            print.clear();
        }
    	if (fabs(dx) < tol ) {
            returnVec.push_back(xnew);
            return returnVec;
    	} else {
            singleVal = x1;
    		fx0 = fx1;
    		x1 = xnew;
        }
    }
    std::cout << "Maximum number of iterations exceeded" << std::endl;
    return x0;
}
