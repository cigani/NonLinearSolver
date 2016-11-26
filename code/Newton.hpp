#ifndef NEWTON_HPP_
#define NEWTON_HPP_

#include <iostream>
#include <iomanip>
#include <math>

class Newton {
public:
    
    // Constructors and destructors
    Newton();
    virtual ~Newton();
    
    // Public variables
    typedef double (*func1arg) (double);
    
    // Public methods
    double newtonSolver ( func1arg f,
			  func1arg df,
			  double x0,
			  double tol,
			  int nMax,
			  boolean verbose );

    double modifiedNewtonSolver ( func1arg f,
				  func1arg df,
				  double x0,
				  double tol,
				  int nMax,
				  int m,
				  boolean verbose );

    double adaptiveNewtonSolver ( func1arg f,
				  func1arg df,
				  double x0,
				  double tol,
				  int nMax,
				  boolean verbose );

    double newtonSystemSolver ( func1arg f,
				func1arg df,
				double x0,
				double tol,
				int nMax,
				boolean verbose );

    double modifiedNewtonSystemSolver ( func1arg f,
					func1arg df,
					double x0,
					double tol,
					int nMax,
					int m,
					boolean verbose );
    
private:
	 
 // Private variables

}
    
#endif /* NEWTON_HPP_ */
#endif /* NEWTON_HPP_ */
