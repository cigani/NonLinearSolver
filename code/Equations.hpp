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

    std::vector<std::vector<double>> createMinor(unsigned long size);

    double Determinant(std::vector<std::vector<double>> &M, const int size);

    std::vector<std::vector<double>> exprtkJacobian(
            const std::vector<std::string> &eq,
            std::vector<std::vector<double>> variableValues,
            int variables);

    double exprtkGenerate2D(const std::string &eq, double value);

    double exprtkGenerate2DDerivative(const std::string &eq, double value);

    std::vector<double>
    subtractVectors(std::vector<double> &v1, std::vector<double> &v2);

private:

    double getJacobianVector(const std::string &eq,
                             std::vector<double> variableValues,
                             std::string withRespectTo);

    void ExtractMinor(std::vector<std::vector<double>> &M, const int size,
                      const int col, std::vector<std::vector<double>> &minor);

    void getJacobianMatrix(const std::vector<std::string> &eq,
                           const std::vector<std::vector<double>> &variableValues,
                           std::vector<std::vector<double>> &JacobianCompiled);

};

#endif /* EQUATIONS_HPP_ */
