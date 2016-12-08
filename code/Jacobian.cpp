//
/* AUTHORS:
* Jaquier, Michael <michael.jaquier@epfl.ch>
* Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
*/
//

#include "Jacobian.h"

/**
 *
 * @param eq - Equations to be used
 * @param variableValues - Matrix of values. If column vector then we use the
 * same values for each equation.
 * @param variables - Number of variables to be used
 * @return - Returns a column vector representing numerical solution to Jacobian
 **/
std::__1::vector<std::__1::vector<double>>
Jacobian::exprtkJacobian(const std::__1::vector<std::__1::string> &eq,
                         std::__1::vector<double> variableValues,
                         int variables) {

    std::__1::vector<std::__1::vector<double> > jm(0, std::__1::vector<double>(
            (unsigned long) variables));
    getJacobianMatrix(eq, variableValues, jm);
    return jm;
}

void Jacobian::getJacobianMatrix(const std::__1::vector<std::__1::string> &eq,
                                 std::__1::vector<double> vals,
                                 std::__1::vector<std::__1::vector<double>> &JM) {

    std::__1::vector<double> Jacobian;

    for (std::__1::string equation : eq) {
        Jacobian.push_back(
                getDerivative(equation, vals, "x"));
        Jacobian.push_back(
                getDerivative(equation, vals, "y"));
        Jacobian.push_back(
                getDerivative(equation, vals, "z"));
        JM.push_back(Jacobian);
        Jacobian.clear();
    }
}