/* AUTHORS:
* Jaquier, Michael <michael.jaquier@epfl.ch>
* Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
*/

#include "Equations.hpp"

Equations::Equations() {}

Equations::~Equations() {}

/// Inputs N - Power of Polynomial needs to be given in order. coef of x1^1..x2^2 --> a_0 + a_1 ... etc

double Equations::getPolyEquation(const std::vector<double> &coef, double value) {
	double f = 0.0;
    for (unsigned int i = 0; i < coef.size(); ++i) {
        	f += coef[i]*pow(value, i);
    }
    return f;
}

double Equations::getPolyDerivative(const std::vector<double> &coef, double value) {
    // Set an exception for methods where the derivative is a denominator.
	// This way we can avoid null errors (this extends to 0.0 as well).
	// Different compilers/settings may treat uninitialized variables differently, so we should
	// initialize this (i.e. crash/error when the original function is a constant).
	// g++ w/ c++11 compiled program automatically defaults to 0.0 anyway.
    double df = 0.0;
    for (unsigned int i = 1; i < coef.size(); ++i) {
    		df += i*coef[i]*pow(value, i-1);
    }
    return df;
}

double Equations::getCosine(double value) {
    return cos(value);
}

double Equations::getCosineDerivative(double value) {
    return -sin(value);
}

double Equations::getCosineIteration(double value) {
    return cos(value) + value;
}


double Equations::exprtkGenerate2D(const std::string &eq, double value) {
    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double> expression_t;
    typedef exprtk::parser<double> parser_t;
    typedef exprtk::parser_error::type error_t;

    std::string expr_string = eq;

    double x = value;

    // This is currently running as y = func(x);
    // We can add more variables i.e., Z = func(x,y) by uncommenting the following;
    // The limit is 20 parameters for this method of doing the function,
    // It can be refactored to accept unlimited paramters but the code is more complex;

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
        printf("Error: %s\tExpression: %s\n",
               parser.error().c_str(),
               expr_string.c_str());

        for (std::size_t i = 0; i < parser.error_count(); ++i) {
            error_t error = parser.get_error(i);

            printf("Error: %02d  Position: %02d Type: [%14s] Msg: %s\tExpression: %s\n",
                   static_cast<unsigned int>(i),
                   static_cast<unsigned int>(error.token.position),
                   exprtk::parser_error::to_str(error.mode).c_str(),
                   error.diagnostic.c_str(),
                   expr_string.c_str());
        }

        return __nan();
    }

    double result = expression.value();
    return result;
}


double
Equations::exprtkGenerate2DDerivative(const std::string &eq, double value) {
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
        printf("Error: %s\tExpression: %s\n",
               parser.error().c_str(),
               expr_string.c_str());

        for (std::size_t i = 0; i < parser.error_count(); ++i) {
            error_t error = parser.get_error(i);

            printf("Error: %02d  Position: %02d Type: [%14s] Msg: %s\tExpression: %s\n",
                   static_cast<unsigned int>(i),
                   static_cast<unsigned int>(error.token.position),
                   exprtk::parser_error::to_str(error.mode).c_str(),
                   error.diagnostic.c_str(),
                   expr_string.c_str());
        }

        return __nan();
    }
    return exprtk::derivative(expression, x);
}
