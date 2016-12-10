/*
 * NonlinearSolver.cpp
 *
 * Created on: November 27, 2015
 *
 * AUTHORS:
 * Jaquier, Michael <michael.jaquier@epfl.ch>
 * Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
 */

#include "NonlinearSolver.hpp"

NonlinearSolver::NonlinearSolver(
		const std::vector<Expression> &equation,
		std::vector<double> initial,
		double tolerance,
		int maxIter,
		bool verbosity) {
	eq = equation;
	x0 = initial;
	tol = tolerance;
	nMax = maxIter;
	verbose = verbosity;
}

NonlinearSolver::~NonlinearSolver() {}

void NonlinearSolver::printVerbose(int i, std::vector<double> &x) {
	std::vector<double>::const_iterator c;
	for (c = x.begin(); c != x.end();
		 ++c) {
		std::cout << *c << "\n";
	};
}

void NonlinearSolver::printVerbose(int i, double &x) {
    std::cout << std::setw(3) << i << "\t" << std::setw(20)
              << x << std::setprecision(15) << std::endl;
}





