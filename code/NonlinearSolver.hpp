#ifndef NONLINEARSOLVER_HPP_
#define NONLINEARSOLVER_HPP_

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

class NonlinearSolver {
protected:
	std::string eq;
	double x0;
	double tol;
	int nMax;
	bool verbose;

public:
    // Constructors and Destructors
	NonlinearSolver(const std::string &equation,
    		double initial,
    		double tolerance,
    		int maxIter,
    		bool verbosity);
    virtual ~NonlinearSolver();

    // Abstract method
	virtual double solve() = 0;

	// Methods
	void printVerbose(int i, double &x);

};
    
#endif /* NONLINEARSOLVER_HPP_ */
