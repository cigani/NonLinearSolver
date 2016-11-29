#ifndef AITKEN_HPP_
#define AITKEN_HPP_

#include <iostream>
#include <iomanip>
#include <math>

class Aitken {
public:

    // Constructors and destructors
    Aitken();
    virtual ~Aitken();
    
    // Public variables
    typedef double (*func1arg) (double);
    
    // Public methods
    double aitkenSolver( func1arg g,
			 double x0,
			 double tol,
			 int nMax,
			 bool verbose );
    
private:
    
    // Private variables

};
    
#endif /* AITKEN_HPP_ */
#endif /* AITKEN_HPP_ */
