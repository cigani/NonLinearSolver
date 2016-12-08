//
/* AUTHORS:
* Jaquier, Michael <michael.jaquier@epfl.ch>
* Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
*/
//

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
};


#endif //PCSC_NONLINEAR_SYSTEMS_PROJECT_EQUATIONTOOLS_H
