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

    static double getPolyEquation(const std::vector<double> &coef, double value);
    static double getPolyDerivative(const std::vector<double> &coef, double value);
    static double getCosine(double value);
    static double getCosineIteration(double value);

private:
    // Private variables
};

#endif /* EQUATIONS_HPP_ */
