#ifndef EQUATIONS_HPP_
#define EQUATIONS_HPP_

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "exprtk.hpp"
#include "EquationsControl.h"

class Equations : public EquationsControl {
public:
    // Constructors and destructors

    Equations();
    virtual ~Equations();

    // Public methods

    double exprtkGenerate2D(const std::string &eq, double value);

    double exprtkGenerate2DDerivative(const std::string &eq, double value);


protected:
    double getDerivative(const std::string &eq,
                         std::vector<double> variableValues,
                         std::string withRespectTo);

    double
    getEquations(const std::string &eq, std::vector<double> variableValues);
};

#endif /* EQUATIONS_HPP_ */
