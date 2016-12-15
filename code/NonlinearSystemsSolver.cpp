/*
 * NonlinearSystemsSolver.cpp
 *
 * Created on: November 27, 2015
 *
 * AUTHORS:
 * Jaquier, Michael <michael.jaquier@epfl.ch>
 * Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
 */

#include "NewtonSystem.hpp"
#include "NonlinearSystemsSolver.hpp"

NonlinearSystemsSolver::NonlinearSystemsSolver(
		ExpressionSystem &sys,
		std::vector<double> &initial,
		double tolerance,
		int maxIter,
		bool verbosity) {
	system = sys;
	v0 = initial;
	tol = tolerance;
	nMax = maxIter;
	verbose = verbosity;
}

NonlinearSystemsSolver::~NonlinearSystemsSolver() {}

void NonlinearSystemsSolver::printVerbose(int i, std::vector<double> &v) {
	std::vector<double>::const_iterator c;
    std::cout << std::setw(3) << i << "\t";
	for (c = v.begin(); c != v.end(); ++c) {
		std::cout << std::setw(20) << std::setprecision(15) << *c << " ";
	};
    std::cout << std::endl;
}
