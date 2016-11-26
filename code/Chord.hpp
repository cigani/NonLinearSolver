#ifndef CHORD_HPP_
#define CHORD_HPP_

#include <iostream>
#include <iomanip>
#include <jmorecfg.h>

class Chord {
public:

    // Constructors and destructors
    Chord();
    virtual ~Chord();
    
    // Public variables
    typedef double (*func1arg) (double);
    
    // Public methods
    double chordSolver ( func1arg f,
			 func1arg fp,
			 double x0,
			 double tol,
			 int nMax,
			 boolean verbose );
	
private:
    
    // Private variables

};
    
#endif /* CHORD_HPP_ */
