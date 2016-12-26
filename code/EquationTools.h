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
#include "exprtk.hpp"

class EquationTools {
    /**
 * Extract the Minor for a given Matrix. Edits the given Matrix via Refrence
 *
 * @param M - Given Matrix
 * @param size - Size of Matrix (in our case M.Size());
 * @param col - Column that will act as scalar in Det
 * @param minor - Minor from @createMinor
 */
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
    addVectors(std::vector<double> &v1, std::vector<double> &v2);

    double getNorm(std::vector<double> &vec);

    std::vector<double> negateVector(std::vector<double> &v1);

    /// \brief Converts a nested vectors to a single vector
    /// \param fx0 - A matrix to be converted
    /// \return A single vector [ ex., Matrix[2][2] -> Vector[4] ]
    static std::vector<double>
    convertMatrix2Vector(std::vector<std::vector<double>> &fx0);
};


#endif //PCSC_NONLINEAR_SYSTEMS_PROJECT_EQUATIONTOOLS_H
