#ifndef BISECTION_HPP_
#define BISECTION_HPP_

#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>

class Bisection {
private:
	double getSign(double value);
	void printVerbose(int i, double &x);

public:
	virtual ~Bisection();
	Bisection();

double bisectionSolver ( const std::string &eq,
		double a,
		double b,
		double tol,
		int nMax,
		bool verbose );
};

#endif /* BISECTION_HPP_ */
