#ifndef BISECTION_HPP_
#define BISECTION_HPP_

#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>
#include <cmath>
#include "NonlinearSolver.hpp"

class Bisection : public NonlinearSolver{
private:
	double getSign(double value);
	double a;
	double b;

public:
	virtual ~Bisection();

	Bisection(const std::string &equation,
			double initial,
			double tolerance,
			int maxIter,
			bool verbosity);

	Bisection(const std::string &equation,
				double initial,
				double tolerance,
				int maxIter,
				bool verbosity,
				double lowerBound,
				double upperBound);

	double solve();
};

#endif /* BISECTION_HPP_ */
