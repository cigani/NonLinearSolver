#ifndef EQUATIONS_HPP_
#define EQUATIONS_HPP_

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "exprtk.hpp"
#include <string>
class Equations {
public:
    // Constructors and destructors

    Equations();
    virtual ~Equations();

    // Public methods

    static double getPolyEquation(const std::vector<double> &coef, double value);
    static double getPolyDerivative(const std::vector<double> &coef, double value);
    static double getCosine(double value);
    static double getCosineDerivative(double value);
    static double getCosineIteration(double value);

    std::vector<double>
    exprtkJacobian(const std::vector<std::string> &eq,
                   std::vector<double> variableValues,
                   int unknown);

    // These aren't static on purpose
    double exprtkGenerate2D(const std::string &eq, double value);

    double exprtkGenerate2DDerivative(const std::string &eq, double value);

private:
    static double getPolyDerivativePrivate(const std::vector<double> &coef,
                                           double value);

    double exprtkGenerateDerivativePrivate(const std::string &eq,
                                           std::vector<double> variableValues,
                                           int variables,
                                           char *withRespectTo);
};

#endif /* EQUATIONS_HPP_ */
