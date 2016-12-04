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

double
Equations::getPolyEquation(const std::vector<double> &coef, double value) {
    double f = 0.0;
    for (unsigned int i = 0; i < coef.size(); ++i) {
        f += coef[i] * pow(value, i);
    }
    return f;
}

/**
 * Calculates the value of a polynomial derivative given in the form
 * d/dx(a_0 + a_1*x + a_2*x^2 + a_3*x^3 ... a_n*x^n)
 * Methods used require a non-zero derivative. The function will jostle the
 * starting value in the event of a zero derivative for a fixed number of iterations
 *
 * @param coef
 * @param value
 * @return - Symbolic evaluation
 */
double
Equations::getPolyDerivative(const std::vector<double> &coef, double value) {

    double df = getPolyDerivativePrivate(coef, value);

    // For now this is hardcoded but you can easily add a switch later if you want
    df = jostleInitialValue(coef, value, df);

    return df;
}

double
Equations::jostleInitialValue(const std::vector<double> &coef, double value,
                              double df) {
    int n = 0;
    while (fabs(df) < DBL_EPSILON) {
        for (int j = 0; j < 100000; ++j) {
        n += 2 * (n + 1);
        value += DBL_EPSILON * n;
            df = getPolyDerivativePrivate(coef, value);

        }
    };

    if (fabs(df) < DBL_EPSILON) {
        std::cout << "No Derivative" << std::endl;
        return __nan();
    } else return df;
}

/**
 * Called by @getPolyDerivative to get the evaluated derivative
 * @param coef
 * @param value
 * @return - Symbolic evaluation
 */
double Equations::getPolyDerivativePrivate(const std::vector<double> &coef,
                                           double value) {
    double df = 0.0;
    for (unsigned int i = 1; i < coef.size(); ++i) {
        df += i * coef[i] * pow(value, i - 1);
    }
    return df;

}

double Equations::getCosine(double value) {
    return cos(value);
}

/**
 * Hard coded cosine derivative
 * @param value
 * @return
 */
double Equations::getCosineDerivative(double value) {
    double df;
    int n = 0;
    int j = 0;

    df = -sin(value);
    df = jostleInitialValue(value, df, n, j);
    return df;
}


double Equations::getCosineIteration(double value) {
    return cos(value) + value;
}

/**
 *
 * @param eq - String containing the equation to evaluate
 * @param value - value to compute from
 * @return - computed equation at value
 */
double Equations::exprtkGenerate2D(const std::string &eq, double value) {
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

            printf("Error: %02d  Position: %02d Type: [%14s] Msg: "
                           "%s\tExpression: %s\n",
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

/**
 *
 * @param eq - String containing the equation to evaluate
 * @param value - value to compute from
 * @return - Derivative of equation at value. Uses numeric approximation.
 */

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

            printf("Error: %02d  Position: %02d Type: [%14s] "
                           "Msg: %s\tExpression: %s\n",
                   static_cast<unsigned int>(i),
                   static_cast<unsigned int>(error.token.position),
                   exprtk::parser_error::to_str(error.mode).c_str(),
                   error.diagnostic.c_str(),
                   expr_string.c_str());
        }

        return __nan();
    }

    double result = jostleInitialValue(x, expression);

    return result;
}


/**
 *
 * @param eq - Equations to be used
 * @param variableValues - Matrix of values. If column vector then we use the
 * same values for each equation.
 * @param variables - Number of variables to be used
 * @return - Returns a column vector representing numerical solution to Jacobian
 */
std::vector<std::vector<double>>
Equations::exprtkJacobian(const std::vector<std::string> &eq,
                          std::vector<std::vector<double> > variableValues,
                          int variables) {

    std::vector<std::vector<double> > JacobianCompiled(0, std::vector<double>(
            (unsigned long) variables));
    std::vector<double> Jacobian;
    int n = 0;

    //std::cout << "Variables Values " << std::endl;
    //TODO: Refactor to less code:

    for (std::string equation : eq) {
        switch (variables) {
            case 1: {
                Jacobian.push_back(
                        exprtkGenerateDerivativePrivate(equation,
                                                        variableValues[n],
                                                        variables,
                                                        "x"));
                break;
            }
            case 2: {
                Jacobian.push_back(
                        exprtkGenerateDerivativePrivate(equation,
                                                        variableValues[n],
                                                        variables,
                                                        "x"));
                Jacobian.push_back(
                        exprtkGenerateDerivativePrivate(equation,
                                                        variableValues[n],
                                                        variables,
                                                        "y"));
                break;
            }
            case 3: {
                Jacobian.push_back(
                        exprtkGenerateDerivativePrivate(equation,
                                                        variableValues[n],
                                                        variables,
                                                        "x"));
                Jacobian.push_back(
                        exprtkGenerateDerivativePrivate(equation,
                                                        variableValues[n],
                                                        variables,
                                                        "y"));
                Jacobian.push_back(
                        exprtkGenerateDerivativePrivate(equation,
                                                        variableValues[n],
                                                        variables,
                                                        "z"));
                break;
            }
            default:
                std::cout << "Jacobian Broken";
                break;
        }
        JacobianCompiled.push_back(Jacobian);
        Jacobian.clear();
        if (variableValues.size() != 1) n++;
    }
    //std::cout << "Jacobian Completed: " << std::endl;
    return JacobianCompiled;
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
Equations::exprtkGenerateDerivativePrivate(const std::string &eq,
                                           std::vector<double> variableValues,
                                           int variables,
                                           std::string withRespectTo) {

    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double> expression_t;
    typedef exprtk::parser<double> parser_t;
    typedef exprtk::parser_error::type error_t;

    std::string expr_string = eq;
    symbol_table_t symbol_table;

//    std::cout << "Jacobians Der Begin: " <<std::endl;
//    std::cout << "Variables " << variables << std::endl;
//    std::cout << "Variable Values: " << variableValues[0] << std::endl;

    switch (variables) {
        case 1: {
            double x = variableValues[0];
            symbol_table.add_variable("x", x);
            //std::cout <<"Added 1 variable(s) to Jacobian " << std::endl;
            break;
        }
        case 2: {
            double x = variableValues[0];
            double y = variableValues[1];
            symbol_table.add_variable("x", x);
            symbol_table.add_variable("y", y);
            //std::cout <<"Added 2 variable(s) to Jacobian " << std::endl;
            break;
        }
        case 3: {
            double x = variableValues[0];
            double y = variableValues[1];
            double z = variableValues[2];
            symbol_table.add_variable("x", x);
            symbol_table.add_variable("y", y);
            symbol_table.add_variable("z", z);
            //std::cout <<"Added 3 variable(s) to Jacobian " << std::endl;
            break;
        }
        default:
            std::cout << "Bad Input to Jacobian Generator";
            break;
    }
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

            printf("Error: %02d  Position: %02d Type: [%14s] "
                           "Msg: %s\tExpression: %s\n",
                   static_cast<unsigned int>(i),
                   static_cast<unsigned int>(error.token.position),
                   exprtk::parser_error::to_str(error.mode).c_str(),
                   error.diagnostic.c_str(),
                   expr_string.c_str());
        }

        return __nan();
    }

    double result = exprtk::derivative(expression, withRespectTo);
    //std::cout << "Jacobian Der Results: " << result << std::endl;
    return result;
}

double Equations::jostleInitialValue(double value, double df, int n, int j) {
    while (fabs(df) < DBL_EPSILON) {
        n += 2 * (n + 1);
        value += DBL_EPSILON * n;
        df = getCosineDerivative(value);
        ++j;
        if (j > 100000) {
            std::__1::cout << "No Derivative" << std::__1::endl;
            return __nan();
        }
    };
    return df;
}

double
Equations::jostleInitialValue(double x,
                              const exprtk::expression<double> &expression) const {
    int n = 0;
    int j = 0;
    double result = derivative(expression, x);
    while (fabs(result) < DBL_EPSILON) {
        n += 2 * (n + 1);
        x += DBL_EPSILON * n;
        result = derivative(expression, x);
        ++j;
        if (j > 100000) {
            std::__1::cout << "No Derivative" << std::__1::endl;
            return __nan();
        }
    };
    return result;
}