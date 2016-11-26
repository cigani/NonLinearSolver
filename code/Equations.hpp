#ifndef EQUATIONS_HPP_
#define EQUATIONS_HPP_

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

class Equations {
public:

    static double polyEquations(double x, const std::vector<double> &p);
    static double polyDerivative(double x, const std::vector<double> &p);
};
#endif /* EQUATIONS_HPP_ */
