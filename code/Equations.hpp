//! Equations.hpp
/*!
  \brief A class handling the parsing of the mathematical expression and evaluation.
  \author Jaquier, Michael <michael.jaquier@epfl.ch>
  \author Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
  \version 1.0
  \date  10 December 2016
  \remark Ecole Polytechnic Federal de Lausanne (EPFL)
  \remark MATH-458 Programming Concepts in Scientific Computing
*/

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


private:

    double getDerivative(const std::string &eq,
                         std::vector<double> variableValues,
                         std::string withRespectTo);

protected:

    double
    getEquations(const std::string &eq, std::vector<double> variableValues);

};

#endif /* EQUATIONS_HPP_ */
