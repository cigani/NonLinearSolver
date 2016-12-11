//! Jacobian.hpp
/*!
  \brief A class constructing an object containing the Jacobian.
  \author Jaquier, Michael <michael.jaquier@epfl.ch>
  \author Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
  \version 1.0
  \date  10 December 2016
  \remark Ecole Polytechnic Federal de Lausanne (EPFL)
  \remark MATH-458 Programming Concepts in Scientific Computing
*/

#ifndef PCSC_NONLINEAR_SYSTEMS_PROJECT_JACOBIAN_H
#define PCSC_NONLINEAR_SYSTEMS_PROJECT_JACOBIAN_H


#include "Equations.hpp"
#include "Expression.hpp"
#include "ExpressionSystem.hpp"

class Jacobian : public Equations {

public:


    std::vector<std::vector<double>>
    exprtkJacobian(const std::vector<std::string> &eq,
                   std::vector<double> variableValues, int variables);

    void
    getJacobianMatrix(const std::vector<std::string> &eq,
                      std::vector<double> vals,
                      std::vector<std::vector<double>> &JM);

    std::vector<std::vector<double>>
    getJacobianNewton(ExpressionSystem &eq, std::vector<double> vals);
};


#endif //PCSC_NONLINEAR_SYSTEMS_PROJECT_JACOBIAN_H
