/* AUTHORS:
* Jaquier, Michael <michael.jaquier@epfl.ch>
* Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
*/

#include <cfloat>
#include "Equations.hpp"

//TODO::  Psuedo Inverse::  J^- = (J^T J)^-1 J^T

Equations::Equations() {}

Equations::~Equations() {}

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
            return __nan();
        }
    };

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

    create_tables(eq, variableValues, variables, JacobianCompiled,
                  Jacobian, n);
    //std::cout << "Jacobian Completed: " << std::endl;
    return JacobianCompiled;
}

void Equations::create_tables(const std::vector<std::string> &eq,
                              const std::vector<std::vector<double>> &variableValues,
                              int variables,
                              std::vector<std::vector<double>> &JacobianCompiled,
                              std::vector<double> &Jacobian, int n) {
    for (std::__1::string equation : eq) {
        switch (variables) {
            case 1: {
                Jacobian.push_back(getJacobian(equation, variableValues[n],
                                               variables, "x"));
                break;
            }
            case 2: {
                Jacobian.push_back(getJacobian(equation, variableValues[n],
                                               variables, "x"));
                Jacobian.push_back(getJacobian(equation, variableValues[n],
                                               variables, "y"));
                break;
            }
            case 3: {
                Jacobian.push_back(getJacobian(equation, variableValues[n],
                                               variables, "x"));
                Jacobian.push_back(getJacobian(equation, variableValues[n],
                                               variables, "y"));
                Jacobian.push_back(getJacobian(equation, variableValues[n],
                                               variables, "z"));
                break;
            }
            default:
                std::__1::cout << "Jacobian Broken";
                break;
        }
        JacobianCompiled.push_back(Jacobian);
        Jacobian.clear();
        if (variableValues.size() != 1) n++;
    }
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
Equations::getJacobian(const std::string &eq,
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
            symbol_table.add_variable("x", variableValues[0]);
            //std::cout <<"Added 1 variable(s) to Jacobian " << std::endl;
            break;
        }
        case 2: {
            symbol_table.add_variable("x", variableValues[0]);
            symbol_table.add_variable("y", variableValues[1]);
            //std::cout <<"Added 2 variable(s) to Jacobian " << std::endl;
            break;
        }
        case 3: {
            symbol_table.add_variable("x", variableValues[0]);
            symbol_table.add_variable("y", variableValues[1]);
            symbol_table.add_variable("z", variableValues[2]);
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

/**
 * Extract the Minor for a given Matrix. Edits the given Matrix via Refrence
 *
 * @param M - Given Matrix
 * @param size - Size of Matrix (in our case M.Size());
 * @param col - Column that will act as scalar in Det
 * @param minor - Minor from @createMinor
 */
void Equations::ExtractMinor(std::vector<std::vector<double>> &M,
                             const int size,
                             const int col,
                             std::vector<std::vector<double>> &minor) {
    for (int row = 1; row < size; ++row) {
        for (int k = 0; k < col; ++k) {
            minor[row - 1][k] = M[row][k];
        }
        for (int k = col + 1; k < size; ++k) {
            minor[row - 1][k - 1] = M[row][k];
        }
    }
}

/**
 * Create a vector<vector> to be populated later
 * @param size - of the Main Vector<Vector> - 1
 * @return A NxN vector<vector> of zeros
 */
std::vector<std::vector<double>>
Equations::createMinor(unsigned long size) {
    std::vector<std::vector<double>> minor(size, std::vector<double>(size));
    return minor;
}

/**
 * Calculate the Det of an input Vector<Vector>
 * Special Case: If it's a 2x2 Matrix we just calculate it in place
 * @param M - Initial Vector<Vector>
 * @param size - Size of the <Vector<Vector> : M.Size()
 * @return The determinant
 */
double
Equations::Determinant(std::vector<std::vector<double>> &M, const int size) {

    //TODO: special case for 3x3 matrix. Speeds it up

    if (size == 2) {
        return M[0][0] * M[1][1] - M[0][1] * M[1][0];
    } else {
        double det = 0;
        for (int col = 0; col < size; ++col) {
            std::vector<std::vector<double>> minor = createMinor(
                    (unsigned long) size);
            ExtractMinor(M, size, col, minor);
            det += M[0][col] * std::pow(-1.0, col)
                   * Determinant(minor, size - 1);
        }
        return det;
    }
}
