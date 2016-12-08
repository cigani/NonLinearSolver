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

    void getJacobianMatrix(const std::__1::vector<std::__1::string> &eq,
                           const std::__1::vector<std::__1::vector<double>> &vals,
                           std::__1::vector<std::__1::vector<double>> &JM);

public:
    std::__1::vector<std::__1::vector<double>> exprtkJacobian(
            const std::__1::vector<std::__1::string> &eq,
            std::__1::vector<std::__1::vector<double>> variableValues,
            int variables);

    std::vector<std::vector<double>>
    exprtkJacobian(const std::vector<std::string> &eq,
                   std::vector<double> variableValues, int variables);

    void getJacobianMatrix(const std::vector<std::string> &eq,
                           const std::vector<double> &vals,
                           std::vector<std::vector<double>> &JM);
};


#endif //PCSC_NONLINEAR_SYSTEMS_PROJECT_JACOBIAN_H
