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

    double getPolyEquation(const std::vector<double> &coef, double value);

    double getPolyDerivative(const std::vector<double> &coef, double value);

    double getCosine(double value);

    double getCosineDerivative(double value);

    double getCosineIteration(double value);

    std::vector<std::vector<double>> createMinor(unsigned long size);

    double Determinant(std::vector<std::vector<double>> &M, const int size);

    std::vector<std::vector<double>> exprtkJacobian(
            const std::vector<std::string> &eq,
            std::vector<std::vector<double>> variableValues,
            int variables);

    double exprtkGenerate2D(const std::string &eq, double value);

    double exprtkGenerate2DDerivative(const std::string &eq, double value);

private:
    double getPolyDerivativePrivate(const std::vector<double> &coef,
                                    double value);

    double exprtkGenerateDerivativePrivate(const std::string &eq,
                                           std::vector<double> variableValues,
                                           int variables,
                                           std::string withRespectTo);

    double jostleInitial(const std::vector<double> &coef, double value);

    void ExtractMinor(std::vector<std::vector<double>> &M, const int size,
                      const int col, std::vector<std::vector<double>> &minor);
};

#endif /* EQUATIONS_HPP_ */
