//
/* AUTHORS:
* Jaquier, Michael <michael.jaquier@epfl.ch>
* Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
*/
//

#ifndef PCSC_NONLINEAR_SYSTEMS_PROJECT_JACOBIAN_H
#define PCSC_NONLINEAR_SYSTEMS_PROJECT_JACOBIAN_H


#include "Equations.hpp"

class Jacobian : public Equations {

public:


    std::vector<std::vector<double>>
    exprtkJacobian(const std::vector<std::string> &eq,
                   std::vector<double> variableValues, int variables);

    void
    getJacobianMatrix(const std::vector<std::string> &eq,
                      std::vector<double> vals,
                      std::vector<std::vector<double>> &JM);
};


#endif //PCSC_NONLINEAR_SYSTEMS_PROJECT_JACOBIAN_H
