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

    double aitkenExprtkSolver(const std::string &eq,
                              double x0,
                              double tol,
                              int nMax,
                              bool verbose);
};
    
#endif /* AITKEN_HPP_ */
