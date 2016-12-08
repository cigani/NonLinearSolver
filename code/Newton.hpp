#ifndef NEWTON_HPP_
#define NEWTON_HPP_

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "NonlinearSolver.hpp"
#include "Equations.hpp"

class Newton : public NonlinearSolver{
private:
	int m;
public:
    // Constructors and destructors
	Newton(const std::vector<std::string> &equation,
		   std::vector<double> initial,
		   double tolerance,
		   int maxIter,
		   bool verbosity);

	Newton(const std::vector<std::string> &equation,
		   std::vector<double> initial,
		   double tolerance,
		   int maxIter,
		   bool verbosity,
		   int modifier);

    virtual ~Newton();

    // Public methods
	std::vector<double> solve();
};
    
#endif /* NEWTON_HPP_ */
