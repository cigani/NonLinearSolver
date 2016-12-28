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
#include <functional>
#include <cmath>
#include <cstdio>
#include <vector>
#include "exprtk.hpp"




class Expression {


public:

    /// A symbolic table containing the variables.
    /// An adapter for the symbol table.
    /// Parsed equations with the symbol table loaded.

    typedef double T;
    typedef exprtk::parser<T>             parser_t;
    typedef exprtk::expression<T>     expression_t;
    typedef exprtk::symbol_table<T> symbol_table_t;
    enum var_index { e_x = 0, e_y = 1, e_z = 2 };

    /*! A constructor to instantiate the container for the parsed expression.
     */
    Expression();

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
     T evaluate(const T &x);
    /*! A method to evaluate the mathematical expression in this class with vectors.
     *
     * \param value A vector of values.
     */
    T evaluate(const std::vector<T>& values);

    /*! A method to evaluate the derivative of the Expression class.
     *
     * \param value A value to evaluate the expression.
     * \param withrespect The variable to differentiate with respect to.
     */
    T deriv(std::vector<T> &value, std::string withrespect);


private:

    std::string  equation_;
    expression_t expression_;
    std::vector<std::reference_wrapper<T> > var_;
    void generateEquation();
};



#endif /* EXPRESSION_HPP_ */
