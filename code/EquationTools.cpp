/*
 * EquationTools.cpp
 *
 * DESCRIPTION: Various linear algebra tools.
 *
 * Created on: December 14, 2016
 *
 * AUTHORS:
 * Jaquier, Michael <michael.jaquier@epfl.ch>
 * Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
 */

#include "EquationTools.h"


void EquationTools::ExtractMinor(std::vector<std::vector<double>> &M,
                                 const int size,
                                 const int col,
                                 std::vector<std::vector<double>> &minor) {
    for (int row = 1; row < size; ++row) {
        for (int k = 0; k < col; ++k) {
            minor[row - 1][k] = M[row][k];
        }
        for (int k = col + 1; k < size; ++k) {
            minor[row - 1][k - 1] = M[row][k];
        }
    }
}

/**
 * Create a vector<vector> to be populated later
 * @param size - of the Main Vector<Vector> - 1
 * @return A NxN vector<vector> of zeros
 */
std::vector<std::vector<double>>
EquationTools::createMinor(unsigned long size) {
    std::vector<std::vector<double>> minor(size,
                                                     std::vector<double>(
                                                             size));
    return minor;
}

/**
 * Calculate the Det of an input Vector<Vector>
 * Special Case: If it's a 2x2 Matrix we just calculate it in place
 * @param M - Initial Vector<Vector>
 * @param size - Size of the <Vector<Vector> : M.Size()
 * @return The determinant
 */
double
EquationTools::Determinant(std::vector<std::vector<double>> &M,
                           const int size) {

    if (size == 2) {
        return M[0][0] * M[1][1] - M[0][1] * M[1][0];
    } else {
        double det = 0;
        for (int col = 0; col < size; ++col) {
            std::vector<std::vector<double>> minor = createMinor(
                    (unsigned long) size);
            ExtractMinor(M, size, col, minor);
            det += M[0][col] * std::pow(-1.0, col)
                   * Determinant(minor, size - 1);
        }
        return det;
    }
}

/// \brief Subtract two vectors point wise
/// \param v1 - A Vector of doubles
/// \param v2 - A Same or Other vector of doubles
/// \return  Vector 1 - Vector 2

std::vector<double> EquationTools::subtractVectors(
        std::vector<double> &v1, std::vector<double> &v2) {
    std::vector<double> result;
    transform(v1.begin(), v1.end(), v2.begin(),
              back_inserter(result),
              [](double v1, double v2) { return (v1 - v2); });
    return result;
}

/// \brief Add two vectors point wise
/// \param v1 - A Vector of doubles
/// \param v2 - A Same or Other vector of doubles
/// \return Vector 1 + Vector 2
std::vector<double> EquationTools::addVectors(
        std::vector<double> &v1, std::vector<double> &v2) {
    std::vector<double> result;
    transform(v1.begin(), v1.end(), v2.begin(),
              back_inserter(result),
              [](double v1, double v2) { return (v1 + v2); });
    return result;
}

/// \brief Transform the vector into its negative (V)*(-1) point wise.
/// \param v1 - A Cector of doubles
/// \return The negative of the vector (V)*(-1)
std::vector<double> EquationTools::negateVector(
        std::vector<double> &v1) {
    std::vector<double> result;
    transform(v1.begin(), v1.end(), back_inserter(result),
              [](double v1) {
                  return (-v1);
              });
    return result;
}

/**
 *
 * @param vec A vector of doubles
 * @return The Euclidean norm
 */
double
EquationTools::getNorm(std::vector<double> &vec) {
    std::vector<double>::const_iterator c;
    double result = 0.0;
    for (c = vec.begin(); c != vec.end(); ++c) {
        result += *c * *c;
    }
    return sqrt(result);
};

std::vector<double> EquationTools::convertMatrix2Vector(
        std::vector<std::vector<double>> &fx0) {
    std::vector<std::vector<double>>::iterator it;
    std::vector<double>::iterator it2;
    std::vector<double> returns;
    for (it = fx0.begin(); it != fx0.end(); ++it) {
        for (it2 = (*it).begin();
             it2 != (*it).end(); ++it2) { returns.push_back(*it2); }
    }
    return returns;
}
