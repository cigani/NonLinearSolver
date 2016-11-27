//
// Created by Michael Jaquier on 26.11.16.
//

#include "Equations.hpp"

Equations::Equations() {}

Equations::~Equations() {}

/// Inputs N - Power of Polynomial needs to be given in order. coef of x1^1..x2^2 --> a_0 + a_1 ... etc

double Equations::getPolyEquation(const std::vector<double> &coef, double value) {
	double f;
    for (unsigned int i = 0; i < coef.size(); ++i) {
        	f += coef[i]*pow(value, i);
    }
    return f;
}

double Equations::getPolyDerivative(const std::vector<double> &coef, double value) {
    // Set an exception for methods where the derivative is a denominator.
	// This way we can avoid null errors (this extends to 0.0 as well).
    double df;
    for (unsigned int i = 1; i < coef.size(); ++i) {
    		df += i*coef[i]*pow(value, i-1);
    }
    return df;
}

double Equations::getCosine(double value) {
    return cos(value);
}

double Equations::getCosineDerivative(double value) {
    return -sin(value);
}

double Equations::getCosineIteration(double value) {
    return cos(value) + value;
}
