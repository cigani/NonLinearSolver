#ifndef CHORD_HPP_
#define CHORD_HPP_

#include <iostream>
#include <iomanip>
#include <vector>

class Chord {
private:
	void printVerbose(int i, double &x);

public:

    // Constructors and destructors
    Chord();
    virtual ~Chord();
    
    // Public variables
    typedef double (*func1arg) (double);
    
    // Public methods
    double chordSolver ( const std::vector<double>& coef,
                         double x0,
                         double tol,
                         int nMax,
                         bool verbose );
};
    
#endif /* CHORD_HPP_ */
