//! Aitken.hpp
/*!
  \brief A class constructing an object capable of solving nonlinear systems with the Aitken method.
  \author Jaquier, Michael <michael.jaquier@epfl.ch>
  \author Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
  \version 1.0
  \date  10 December 2016
  \remark Ecole Polytechnic Federal de Lausanne (EPFL)
  \remark MATH-458 Programming Concepts in Scientific Computing
*/

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
