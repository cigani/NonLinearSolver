/*
 * Newton.cpp
 *
 * DESCRIPTION: Returns the root of an arbitrary nonlinear function using
 *              Newton's method or the modified Newton's method
 *
 * Created on: November 27, 2016
 *
 * AUTHORS:
 * Jaquier, Michael <michael.jaquier@epfl.ch>
 * Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
 */

#include "Newton.hpp"

Newton::Newton(Expression &equation,
               Expression &derivative,
               double initial,
               double tolerance,
               int maxIter,
               bool verbosity)
	: NonlinearSolver(equation, initial, tolerance, maxIter, verbosity)
{
    df = derivative;
	m = 1;
}

Newton::Newton(Expression &equation,
               Expression &derivative,
               double initial,
               double tolerance,
               int maxIter,
               bool verbosity,
               int modifier)
	: NonlinearSolver(equation, initial, tolerance, maxIter, verbosity)
{
    df = derivative;
	m = modifier;
}

Newton::~Newton() {}

double Newton::solve() {

    double dx, fx0, dfx0;

    if (verbose) { printVerbose(0, x0); }

    for (int i = 1; i <= nMax; i++) {

        fx0 = eq.evaluate(x0);
        dfx0 = df.evaluate(x0);
        dx = fx0 / dfx0;

        x0 -= (double)m * dx;

        if (verbose) { printVerbose(i, x0); }

        if (fabs((double)m * dx) < tol) { return x0; }
    }

    std::cout << "Maximum number of iterations exceeded" << std::endl;
    return x0;
}