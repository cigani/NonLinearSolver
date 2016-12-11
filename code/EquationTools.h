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
    ExtractMinor(std::vector<std::vector<double>> &M, const int size,
                 const int col,
                 std::vector<std::vector<double>> &minor);

public:
    std::vector<std::vector<double>> createMinor(unsigned long size);

    double
    Determinant(std::vector<std::vector<double>> &M, const int size);

    std::vector<double>
    subtractVectors(std::vector<double> &v1,
                    std::vector<double> &v2);

    std::vector<double>
    getSystemEquations(const std::vector<std::string> &eq,
                       std::vector<double> variableValues);


    std::vector<double>
    addVectors(std::vector<double> &v1, std::vector<double> &v2);

    double getNorm(std::vector<double> &vec);

    std::vector<double> negateVector(std::vector<double> &v1);

    void printVec(std::vector<double> &dx);
};


#endif //PCSC_NONLINEAR_SYSTEMS_PROJECT_EQUATIONTOOLS_H
