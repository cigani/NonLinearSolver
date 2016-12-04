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

    static std::vector<std::vector<double>>
    exprtkJacobian(const std::vector<std::string> &eq,
                   std::vector<std::vector<double>> variableValues,
                   int variables);


    // These aren't static on purpose
    double exprtkGenerate2D(const std::string &eq, double value);

    double exprtkGenerate2DDerivative(const std::string &eq, double value);

private:
    static double getPolyDerivativePrivate(const std::vector<double> &coef,
                                           double value);

    static double exprtkGenerateDerivativePrivate(const std::string &eq,
                                                  std::vector<double> variableValues,
                                                  int variables,
                                                  std::string withRespectTo);

    double
    jostleInitialValue(double x,
                       const exprtk::expression<double> &expression) const;

    static double jostleInitialValue(double value, double df, int n, int j);

    static double
    jostleInitialValue(const std::vector<double> &coef, double value,
                       double df);
};

#endif /* EQUATIONS_HPP_ */
