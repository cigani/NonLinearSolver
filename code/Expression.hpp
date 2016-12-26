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

    /// A standard string representing mathematical expressions.
    std::string equation;

    /// A symbolic table containing the variables.
    typedef exprtk::symbol_table<double> symbol_table_t;

    /// An adapter for the symbol table.
    typedef exprtk::expression<double> expression_t;

    /// Parsed equations with the symbol table loaded.
    typedef exprtk::parser<double> parser_t;

    expression_t expression_;
    //parser_t parser_;
    //symbol_table_t symbol_table_;
    double x_, y_, z_;

public:
    /*! A constructor to instantiate the container for the parsed expression.
     */
    //Expression();

    /*! A constructor to instantiate the container for the parsed expression.
     *
     * \param eq A string that contains the mathematical expression for the class to evaluate.
     */
    Expression(const std::string &eq);

    virtual ~Expression() {}

    /*! A method to set a mathematical expression as a string to this object.
     *
     * \param eq A string that contains the mathematical expression for the class to evaluate.
     */
    void setEquation(const std::string &eq);

    /*! A method to return a mathematical expression as a string to this object.
     *
     * \return The mathematical expression assigned to this object.
     */
    std::string getEquation();

    /*! A method to evaluate the mathematical expression in this class.
     *
     * \param value A value to evaluate the expression.
     */
    double evaluate(double &value);

    /*! A method to evaluate the mathematical expression in this class with vectors.
     *
     * \param value A vector of values.
     */
    double evaluate(std::vector<double> &value);

    /*! A method to evaluate the derivative of the Expression class.
     *
     * \param value A value to evaluate the expression.
     * \param withrespect The variable to differentiate with respect to.
     */
    double deriv(std::vector<double> &value, std::string withrespect);
};

#endif /* EXPRESSION_HPP_ */
