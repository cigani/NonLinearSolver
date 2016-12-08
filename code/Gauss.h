//
/* AUTHORS:
* Jaquier, Michael <michael.jaquier@epfl.ch>
* Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
*/
//

#ifndef PCSC_NONLINEAR_SYSTEMS_PROJECT_GAUSS_H
#define PCSC_NONLINEAR_SYSTEMS_PROJECT_GAUSS_H


#include "Equations.hpp"

class Gauss : public Equations {

public:
    void
    GaussPartialPivoting(std::__1::vector<std::__1::vector<double>> &jacobian,
                         std::__1::vector<double> &funcSolutions);

    void Pivot(std::__1::vector<std::__1::vector<double>> &jacobian,
               std::__1::vector<double> &funcSolution, const int k,
               const int n);

    std::vector<double>
    BackwardSolve(std::__1::vector<std::__1::vector<double>> &jacobian,
                  std::__1::vector<double> &funcSolution);
};


#endif //PCSC_NONLINEAR_SYSTEMS_PROJECT_GAUSS_H
