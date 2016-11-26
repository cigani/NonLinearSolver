#ifndef SECANT_HPP_
#define SECANT_HPP_

#include <iostream>
#include <iomanip>
#include <math>

class Secant {
public:

    // Constructors and destructors
    Secant();
    virtual ~Secant();
    
    // Public variables
    typedef double (*func1arg) (double);
    
    // Public methods
    double secantSolver ( func1arg f,
			  double x0,
			  double x1,
			  double tol,
			  int nMax,
			  bool verbose );
	
private:
    
    // Private variables

}
  
#endif /* SECANT_HPP_ */
#endif /* SECANT_HPP_ */
