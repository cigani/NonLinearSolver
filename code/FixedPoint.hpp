#ifndef FIXEDPOINT_HPP_
#define FIXEDPOINT_HPP_

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "NonlinearSolver.hpp"
#include "Equations.hpp"

class FixedPoint : public NonlinearSolver {
private:
public:
    // Constructors and destructors
    FixedPoint(const std::vector<std::string> &equation,
               std::vector<double> initial,
               double tolerance,
               int maxIter,
               bool verbosity);
    virtual ~FixedPoint();
    
    // Public methods
    double solve();
    
};
  
#endif /* FIXEDPOINT_HPP_ */

