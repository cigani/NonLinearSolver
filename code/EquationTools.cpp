//
/* AUTHORS:
* Jaquier, Michael <michael.jaquier@epfl.ch>
* Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
*/
//

#include "Equations.hpp"
#include "EquationTools.h"

/**
 * Extract the Minor for a given Matrix. Edits the given Matrix via Refrence
 *
 * @param M - Given Matrix
 * @param size - Size of Matrix (in our case M.Size());
 * @param col - Column that will act as scalar in Det
 * @param minor - Minor from @createMinor
 */
void EquationTools::ExtractMinor(std::__1::vector<std::__1::vector<double>> &M,
                                 const int size,
                                 const int col,
                                 std::__1::vector<std::__1::vector<double>> &minor) {
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
std::__1::vector<std::__1::vector<double>>
EquationTools::createMinor(unsigned long size) {
    std::__1::vector<std::__1::vector<double>> minor(size,
                                                     std::__1::vector<double>(
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
EquationTools::Determinant(std::__1::vector<std::__1::vector<double>> &M,
                           const int size) {

    //TODO: special case for 3x3 matrix. Speeds it up

    if (size == 2) {
        return M[0][0] * M[1][1] - M[0][1] * M[1][0];
    } else {
        double det = 0;
        for (int col = 0; col < size; ++col) {
            std::__1::vector<std::__1::vector<double>> minor = createMinor(
                    (unsigned long) size);
            ExtractMinor(M, size, col, minor);
            det += M[0][col] * std::__1::pow(-1.0, col)
                   * Determinant(minor, size - 1);
        }
        return det;
    }
}

std::__1::vector<double> EquationTools::subtractVectors(
        std::__1::vector<double> &v1, std::__1::vector<double> &v2) {
    std::__1::vector<double> result;
    transform(v1.begin(), v1.end(), v2.begin(),
              back_inserter(result),
              [](double v1, double v2) { return (v1 - v2); });
    return result;
}

std::__1::vector<double> EquationTools::addVectors(
        std::__1::vector<double> &v1, std::__1::vector<double> &v2) {
    std::__1::vector<double> result;
    transform(v1.begin(), v1.end(), v2.begin(),
              back_inserter(result),
              [](double v1, double v2) { return (v1 + v2); });
    return result;
}

std::__1::vector<double> EquationTools::negateVector(
        std::__1::vector<double> &v1) {
    std::__1::vector<double> result;
    transform(v1.begin(), v1.end(), back_inserter(result),
              [](double v1) { return (-v1); });
    return result;
}

std::__1::vector<double>
EquationTools::getSystemEquations(const std::__1::vector<std::__1::string> &eq,
                                  std::__1::vector<double> variableValues) {
    std::__1::vector<double> systemReturns;
    for (std::__1::string equations : eq) {
        systemReturns.push_back(getEquations(equations, variableValues));
    }
    return systemReturns;
}


double
EquationTools::getNorm(std::vector<double> &vec) {
    std::vector::const_iterator c;
    double result = 0.0;
    for (c = vec.begin(); c != vec.end(); ++c) {
        result += *c * *c;
    }
    return sqrt(result);
};


