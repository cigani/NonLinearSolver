#ifndef AITKEN_HPP_
#define AITKEN_HPP_

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

class Aitken {
public:

    // Constructors and destructors
    Aitken();
    virtual ~Aitken();
    
    // Public variables
    typedef double (*func1arg) (double);
    
    // Public methods
	double aitkenSolver(std::__1::vector<double> &coef,
						double x0,
						double tol,
						int nMax,
						bool verbose);
    
private:
    
    // Private variables
    
};
    
#endif /* AITKEN_HPP_ */
