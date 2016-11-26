#ifndef FIXEDPOINT_HPP_
#define FIXEDPOINT_HPP_

#include <iostream>
#include <iomanip>
#include <math>

class FixedPoint {
public:

    // Constructors and destructors
    FixedPoint();
    virtual ~FixedPoint();
    
    // Public variables
    typedef double (*func1arg) (double);
    
    // Public methods
    double fixedPointSolver ( func1arg g,
			      double x0,
			      double tol,
			      int nMax,
			      bool verbose );
    
private:
    
    // Private variables

};
  
#endif /* FIXEDPOINT_HPP_ */
#endif /* FIXEDPOINT_HPP_ */
