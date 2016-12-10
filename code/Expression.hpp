//! Expression.hpp
/*!
  \brief A class handling the parsing of the mathematical expression and evaluation.
  \author Jaquier, Michael <michael.jaquier@epfl.ch>
  \author Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
  \version 1.0
  \date  10 December 2016
  \remark Ecole Polytechnic Federal de Lausanne (EPFL)
  \remark MATH-458 Programming Concepts in Scientific Computing
*/

#ifndef EXPRESSION_HPP_
#define EXPRESSION_HPP_

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "exprtk.hpp"

class Expression {
private:
    std::string equation;
    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double>     expression_t;
    typedef exprtk::parser<double>             parser_t;

public:
    // Constructors and destructors
    Expression();
    Expression(const std::string &eq);
    virtual ~Expression();

    void setEquation(const std::string &eq);

    std::string getEquation();

    double evaluate(double &value);

};

#endif /* EXPRESSION_HPP_ */
