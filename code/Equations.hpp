#ifndef EQUATIONS_HPP_
#define EQUATIONS_HPP_

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "exprtk.hpp"
#include "EquationsControl.h"

class Equations : public EquationsControl {
public:
    // Constructors and destructors

    Equations();
    virtual ~Equations();

    // Public methods

    double exprtkGenerate2D(const std::string &eq, double value);

    double exprtkGenerate2DDerivative(const std::string &eq, double value);

    void ExtractMinor(std::vector<std::vector<double>> &M,
                      const int size,
                      const int col,
                      std::vector<std::vector<double>> &minor);



private:
    static double getPolyDerivativePrivate(const std::vector<double> &coef,
                                           double value);

protected:
    double getDerivative(const std::string &eq,
                         std::vector<double> variableValues,
                         std::string withRespectTo);


    static double jostleInitial(const std::vector<double> &coef, double value);
};

#endif /* EQUATIONS_HPP_ */
