//
/* AUTHORS:
* Jaquier, Michael <michael.jaquier@epfl.ch>
* Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
*/
//

#ifndef PCSC_NONLINEAR_SYSTEMS_PROJECT_EQUATIONSCONTROL_H
#define PCSC_NONLINEAR_SYSTEMS_PROJECT_EQUATIONSCONTROL_H


#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "exprtk.hpp"

class EquationsControl {

protected:
    void logErrors(const std::__1::string &expr_string,
                   exprtk::parser<double> &parser) const;
};


#endif //PCSC_NONLINEAR_SYSTEMS_PROJECT_EQUATIONSCONTROL_H
