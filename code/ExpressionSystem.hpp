//! ExpressionSystem.hpp
/*!
  \brief A class responsible for storing a matrix of Expression objects.
  \author Jaquier, Michael <michael.jaquier@epfl.ch>
  \author Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
  \version 1.0
  \date  10 December 2016
  \remark Ecole Polytechnic Federal de Lausanne (EPFL)
  \remark MATH-458 Programming Concepts in Scientific Computing
*/

#ifndef EXPRESSIONSYSTEM_HPP_
#define EXPRESSIONSYSTEM_HPP_

#include "Expression.hpp"
#include <vector>

class ExpressionSystem {
private:
    /// System of <Expression> expressions.
    std::vector<std::vector<Expression>> system;
    /// Filename to load our matrix from.
    std::string filename;
    void read();

    /// Rows and columns present in the matrix
    int rows;
    int columns;

public:
    ///Constructor to generate the system of equations
    ExpressionSystem(std::string input);
    ExpressionSystem();
    virtual ~ExpressionSystem();

    /// Method to return the vector compromising the system of equations.
    std::vector<std::vector<Expression>> getSystem();

    /// Method to print out the equations
    void print();

    /// \brief Method to return an individual equation from the system matrix
    /// \param i  The column
    /// \param j  The row
    /// \return  Returns a Expression which contains a single equation.
    Expression getEquation(int i, int j);

    /// \brief Evaluates the matrix of equations with the given values
    /// \param value Vector of values used to evaluate the function
    /// \return Returns a matrix which represents the evaluation
    std::vector<std::vector<double>> evaluate(std::vector<double> &value);

    int getColumns();

    /// \brief Generates a Numeric APPROXIMATION of the jacobian
    /// \param value Vector Values to evaluate the numeric Jacobian at
    /// \return A numeric APROXIMATION of the Jacobian at a set of points
    std::vector<std::vector<double>> jacobian(std::vector<double> &value);
};


#endif //EXPRESSIONSYSTEM_HPP_
