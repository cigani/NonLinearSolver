#ifndef FIXEDPOINT_HPP_
#define FIXEDPOINT_HPP_

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

class FixedPoint {
private:
 // Private variables
	void printVerbose( int i, double &x );

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
    
    double fixedPointExprtkSolver(const std::string &eq,
    		double x0,
    		double tol,
    		int nMax,
    		bool verbose );
};
  
#endif /* FIXEDPOINT_HPP_ */

