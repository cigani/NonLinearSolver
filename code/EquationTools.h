//! EquationTools.hpp
/*!
  \brief A class handling linear algebra operations.
  \author Jaquier, Michael <michael.jaquier@epfl.ch>
  \author Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
  \version 1.0
  \date  10 December 2016
  \remark Ecole Polytechnic Federal de Lausanne (EPFL)
  \remark MATH-458 Programming Concepts in Scientific Computing
*/

#ifndef PCSC_NONLINEAR_SYSTEMS_PROJECT_EQUATIONTOOLS_H
#define PCSC_NONLINEAR_SYSTEMS_PROJECT_EQUATIONTOOLS_H


#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "Equations.hpp"
#include "exprtk.hpp"
#include "EquationsControl.h"

class EquationTools : public Equations {

    void
    ExtractMinor(std::__1::vector<std::__1::vector<double>> &M, const int size,
                 const int col,
                 std::__1::vector<std::__1::vector<double>> &minor);

public:
    std::__1::vector<std::__1::vector<double>> createMinor(unsigned long size);

    double
    Determinant(std::__1::vector<std::__1::vector<double>> &M, const int size);

    std::__1::vector<double>
    subtractVectors(std::__1::vector<double> &v1,
                    std::__1::vector<double> &v2);

    std::__1::vector<double>
    getSystemEquations(const std::__1::vector<std::__1::string> &eq,
                       std::__1::vector<double> variableValues);


    std::vector<double>
    addVectors(std::vector<double> &v1, std::vector<double> &v2);

    double getNorm(std::vector<double> &vec);

    std::vector<double> negateVector(std::vector<double> &v1);
};


#endif //PCSC_NONLINEAR_SYSTEMS_PROJECT_EQUATIONTOOLS_H
