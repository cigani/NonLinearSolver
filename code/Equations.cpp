/* AUTHORS:
* Jaquier, Michael <michael.jaquier@epfl.ch>
* Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
*/
///
#include <cfloat>
#include "Equations.hpp"


Equations::Equations() {}

Equations::~Equations() {}

/// Inputs N - Power of Polynomial needs to be given in order.
/// coef of x1^1..x2^2 --> a_0 + a_1 ... etc

double
Equations::getPolyEquation(const std::vector<double> &coef, double value) {
    double f = 0.0;
    for (unsigned int i = 0; i < coef.size(); ++i) {
        f += coef[i] * pow(value, i);
    }
    return f;
}

double
Equations::getPolyDerivative(const std::vector<double> &coef, double value) {

    // Set an exception for methods where the derivative is a denominator.
    // This way we can avoid null errors (this extends to 0.0 as well).
    // Different compilers/settings may treat uninitialized variables
    // differently, so we should initialize this (i.e. crash/error when
    // the original function is a constant). g++ w/ c++11 compiled program
    // automatically defaults to 0.0 anyway.
    int n = 0;

    double df = getPolyDerivativePrivate(coef, value);

    if (fabs(df) < DBL_EPSILON) {
        for (int j = 0; j < 100000; ++j) {
        n += 2 * (n + 1);
        value += DBL_EPSILON * n;
            df = getPolyDerivativePrivate(coef, value);
        }
    };

    if (fabs(df) < DBL_EPSILON) {
        std::cout << "No Derivative" << std::endl;
        std::exit(1);
    } else return df;
}

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

double Equations::getCosineDerivative(double value) {
    double df;
    int n = 0;
    int j = 0;

    df = -sin(value);

    while (fabs(df) < DBL_EPSILON) {
        n += 2 * (n + 1);
        value += DBL_EPSILON * n;
        df = getCosineDerivative(value);
        ++j;
        if (j > 100000) {
            std::cout << "No Derivative" << std::endl;
            std::exit(1);
        }
    };
    return df;
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
    int n = 0;
    int j = 0;

    double result = exprtk::derivative(expression, x);
    while (fabs(result) < DBL_EPSILON) {
        n += 2 * (n + 1);
        x += DBL_EPSILON * n;
        result = exprtk::derivative(expression, x);
        ++j;
        if (j > 100000) {
            std::cout << "No Derivative" << std::endl;
            std::exit(1);
        }
    };

    return result;
}

std::vector<double>
Equations::exprtkJacobian(const std::vector<std::string> &eq,
                          std::vector<std::vector<double> > variableValues,
                          int variables) {

    std::vector<double> Jacobian;
    int n = 0;

    //std::cout << "Variables Values " << std::endl;
    //TODO: Assuming this works - Refactor to less code:

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
        n++;
    }
    //std::cout << "Jacobian Completed: " << std::endl;
    return Jacobian;
}

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
