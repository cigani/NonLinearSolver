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

    std::vector<double> aitkenExprtkSolver(const std::vector<std::string> &eq,
                                           std::vector<double> x0,
                                           double tol,
                                           int nMax,
                                           bool verbose);
};
    
#endif /* AITKEN_HPP_ */
