#ifndef EQUATIONS_HPP_
#define EQUATIONS_HPP_

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

class Equations {
public:
    // Constructors and destructors

    Equations();
    virtual ~Equations();

    // Public methods

    double getEquation(const std::vector<double> &coef, double value);
    double getDerivative(const std::vector<double> &coef, double value);

private:
    // Private variables
};

#endif /* EQUATIONS_HPP_ */
