#ifndef FIXEDPOINT_HPP_
#define FIXEDPOINT_HPP_

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

class FixedPoint {
public:

    // Constructors and destructors
    FixedPoint();
    virtual ~FixedPoint();
    
    // Public variables
    
    // Public methods
    double fixedPointSolver ( const std::vector<double>& coef,
			      double x0,
			      double tol,
			      int nMax,
			      bool verbose );
    
private:
    
    // Private variables

};
  
#endif /* FIXEDPOINT_HPP_ */

