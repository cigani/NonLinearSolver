#ifndef AITKEN_HPP_
#define AITKEN_HPP_

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

class Aitken {
private:
	void printVerbose(int i, double &x);

public:

    // Constructors and destructors
    Aitken();
    virtual ~Aitken();
    
    // Public variables
    typedef double (*func1arg) (double);
    
    // Public methods
	double aitkenSolver(std::vector<double> &coef,
			double x0,
			double tol,
			int nMax,
			bool verbose);

	double aitkenExprtkSolver(const std::string &eq,
			double x0,
			double tol,
			int nMax,
			bool verbose);
};
    
#endif /* AITKEN_HPP_ */
