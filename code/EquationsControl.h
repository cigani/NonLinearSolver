//! EquationsControl.hpp
/*!
  \brief A class handling the errors of the exprtk parser.
  \author Jaquier, Michael <michael.jaquier@epfl.ch>
  \author Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
  \version 1.0
  \date  10 December 2016
  \remark Ecole Polytechnic Federal de Lausanne (EPFL)
  \remark MATH-458 Programming Concepts in Scientific Computing
*/

#ifndef PCSC_NONLINEAR_SYSTEMS_PROJECT_EQUATIONSCONTROL_H
#define PCSC_NONLINEAR_SYSTEMS_PROJECT_EQUATIONSCONTROL_H


#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "exprtk.hpp"

class EquationsControl {

protected:
    void logErrors(const std::__1::string &expr_string,
                   exprtk::parser<double> &parser) const;
};


#endif //PCSC_NONLINEAR_SYSTEMS_PROJECT_EQUATIONSCONTROL_H
