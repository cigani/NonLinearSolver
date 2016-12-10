/* AUTHORS:
* Jaquier, Michael <michael.jaquier@epfl.ch>
* Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
*/

#include <cfloat>
#include <boost/function.hpp>
#include "Equations.hpp"

//TODO::  Psuedo Inverse::  J^- = (J^T J)^-1 J^T

Equations::Equations() {}

Equations::~Equations() {}

/**
 * * Calculates the value of a polynomial given in the form
 * (a_0 + a_1*x + a_2*x^2 + a_3*x^3 ... a_n*x^n)
 * @param coef - Vector of coefficients.
 * @param value - Initial Value
 * @return - Symbolic Evaluation
 */

//TODO: Delete this. Replace with @getEquations method
double Equations::exprtkGenerate2D(const std::string &eq,
                                   double value) {

    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double> expression_t;
    typedef exprtk::parser<double> parser_t;
    typedef exprtk::parser_error::type error_t;

    std::string expr_string = eq;

    double x = value;
    double y;
    double z;

    symbol_table_t symbol_table;
    symbol_table.add_variable("x", x);
    symbol_table.add_variable("y", y);
    symbol_table.add_variable("z", z);
    symbol_table.add_constants();

    expression_t expression;
    expression.register_symbol_table(symbol_table);

    parser_t parser;
    parser.compile(expr_string, expression);
    if (!parser.compile(expr_string, expression)) {
        logErrors(expr_string, parser);
        return __nan();
    }

    double result = expression.value();
    return result;
}



/**
 *
 * @param eq - String containing the equation to evaluate
 * @param value - value to compute from
 * @return - Derivative of equation at value. Uses numeric approximation.
 */

//TODO: Delete this and replace all method calls with @getDerivative
double Equations::exprtkGenerate2DDerivative(const std::string &eq,
                                             double value) {

    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double> expression_t;
    typedef exprtk::parser<double> parser_t;
    typedef exprtk::parser_error::type error_t;

    std::string expr_string = eq;
    double x = value;
    double y;
    double z;

    symbol_table_t symbol_table;
    symbol_table.add_variable("x", x);
    symbol_table.add_variable("y", y);
    symbol_table.add_variable("z", z);
    symbol_table.add_constants();

    expression_t expression;
    expression.register_symbol_table(symbol_table);

    parser_t parser;
    parser.compile(expr_string, expression);
    if (!parser.compile(expr_string, expression)) {
        logErrors(expr_string, parser);
        return __nan();
    }
    double result = derivative(expression, x);
    int j = 0;
    while ((fabs(result) < DBL_EPSILON) && ++j < 100000) {
        x += DBL_EPSILON * exp(j * j + 1);
        result = derivative(expression, x);
    };
    return result;
}


/**
 * This is used by @exprtkJacobian to calculate the Jacobian
 * @param eq
 * @param variableValues
 * @param variables
 * @param withRespectTo
 * @return a singlle double (df/(dx_i))
 */
double
Equations::getDerivative(const std::string &eq,
                         std::vector<double> variableValues,
                         std::string withRespectTo) {

    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double> expression_t;
    typedef exprtk::parser<double> parser_t;
    typedef exprtk::parser_error::type error_t;

    std::string expr_string = eq;
    symbol_table_t symbol_table;

    /* Use .at here to make use of the bounds check vectors come with
    we only need it for the first check. After that we can shave off nano
    seconds by not checking the bounds since we know its there via size() */

    double x = variableValues.at(0);
    symbol_table.add_variable("x", x);
    if (variableValues.size() != 1) {
        double y = variableValues[1];
        symbol_table.add_variable("y", y);
        if (variableValues.size() == 3) {
            double z = variableValues[2];
            symbol_table.add_variable("z", z);
        }
    }
    symbol_table.add_constants();

    expression_t expression;
    expression.register_symbol_table(symbol_table);

    parser_t parser;
    parser.compile(expr_string, expression);
    if (!parser.compile(expr_string, expression)) {
        logErrors(expr_string, parser);
        return __nan();
    }
//     x = 1;
//     y = 2; Changing these will change the result.
//     z = 3;
    double result = derivative(expression, withRespectTo);
    return result;
}

double
Equations::getEquations(const std::string &eq,
                        std::vector<double> variableValues) {

    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double> expression_t;
    typedef exprtk::parser<double> parser_t;
    typedef exprtk::parser_error::type error_t;

    std::string expr_string = eq;
    symbol_table_t symbol_table;

    /* Use .at here to make use of the bounds check vectors come with
    we only need it for the first check. After that we can shave off nano
    seconds by not checking the bounds since we know its there via size() */

    double x = variableValues.at(0);
    symbol_table.add_variable("x", x);
    if (variableValues.size() != 1) {
        double y = variableValues[1];
        symbol_table.add_variable("y", y);
        if (variableValues.size() == 3) {
            double z = variableValues[2];
            symbol_table.add_variable("z", z);
        }
    }
    symbol_table.add_constants();

    expression_t expression;
    expression.register_symbol_table(symbol_table);

    parser_t parser;
    parser.compile(expr_string, expression);
    if (!parser.compile(expr_string, expression)) {
        logErrors(expr_string, parser);
        return __nan();
    }
//     x = 1;
//     y = 2; Changing these will change the result.
//     z = 3;
    return expression.value();
}
