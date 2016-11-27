//
// Created by Michael Jaquier on 26.11.16.
//

#include "Equations.hpp"

Equations::Equations() {}

Equations::~Equations() {}

/// Inputs N - Power of Polynomial needs to be given in order. coef of x1^1..x2^2 --> a_0 + a_1 ... etc

double Equations::getEquation(const std::vector<double>& coef, double value) {
	double f;
    //std::cout << "x = " << value << std::endl;
    //std::cout << "The equation is: " << std::endl;
    for (unsigned int i = 0; i < coef.size(); ++i){
        	//std::cout << " + (" << coef[i]  << " * x^" << i << ")";
        	f += coef[i]*pow(value, i);
        }
    //std::cout << std::endl;
    //std::cout << "result: " << f << std::endl;
    //std::cout << std::endl;
    return f;
}

double Equations::getDerivative(const std::vector<double>& coef, double value) {
    // Do NOT set this to = 0.0. This will lead to bad errors during calculation that we wont notice.
    double df;
    //std::cout << "x = " << value << std::endl;
    //std::cout << "The derivative is: " << std::endl;
    for (unsigned int i = 1; i < coef.size(); ++i) {
    		//std::cout << " + (" << i*coef[i]  << " * x^" << i-1 << ")";
    		df += i*coef[i]*pow(value, i-1);
    }
    //std::cout << std::endl;
    //std::cout << "result: " << df << std::endl;
    //std::cout << std::endl;
    return df;
}

double Equations::getCosine(double value) {
    return cos(value);
}

double Equations::getCosineIteration(double value) {
    return cos(value) + value;
}
