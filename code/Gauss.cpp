//
/* AUTHORS:
* Jaquier, Michael <michael.jaquier@epfl.ch>
* Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
*/
//

#include "Gauss.h"

void Gauss::GaussPartialPivoting(
        std::__1::vector<std::__1::vector<double>> &jacobian,
        std::__1::vector<double> &funcSolutions) {

    int n = (int) funcSolutions.size();
    {
        for (int k = 0; k < n; ++k) {
            Pivot(jacobian, funcSolutions, k, n);

            for (int i = k + 1; i < n; ++i) {
                double m = jacobian[i][k] / jacobian[k][k];
                for (int j = k + 1; j < n; ++j) {
                    jacobian[i][j] -= m * jacobian[k][j];
                }
                funcSolutions[i] -= m * funcSolutions[k];
            }
            // Zero out below
            for (int i = k + 1; i < n; ++i) {
                jacobian[i][k] = 0;
            }
        }
    }
}

void Gauss::Pivot(std::__1::vector<std::__1::vector<double>> &jacobian,
                  std::__1::vector<double> &funcSolution, const int k,
                  const int n) {
    double max = fabs(jacobian[k][k]);
    int idx_max = k;

    for (int i = k + 1; i < n; ++i) {
        double ev = fabs(jacobian[i][k]);
        if (ev > max) {
            max = ev;
            idx_max = i;
        }
    }

    // Swap values in rhs b
    double t = funcSolution[k];
    funcSolution[k] = funcSolution[idx_max];
    funcSolution[idx_max] = t;

    // Swap rows in matrix A
    std::__1::vector<double> p = jacobian[k];
    jacobian[k] = jacobian[idx_max];
    jacobian[idx_max] = p;
}

std::vector<double>
Gauss::BackwardSolve(std::__1::vector<std::__1::vector<double>> &jacobian,
                     std::__1::vector<double> &funcSolution) {
    std::vector<double> x(funcSolution.size());
    int n = (int) funcSolution.size();
    for (int i = n - 1; i >= 0; --i) {
        x[i] = funcSolution[i];
        for (int j = i + 1; j < n; ++j) {
            x[i] -= jacobian[i][j] * x[j];
        }
        x[i] /= jacobian[i][i];
    }
    return x;
}