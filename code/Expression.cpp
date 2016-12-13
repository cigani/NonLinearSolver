/*
 * EquationParser.cpp
 *
 * DESCRIPTION: Parses the string into a symbolic table.
 *
 * Created on: December 10, 2016
 *
 * AUTHORS:
 * Jaquier, Michael <michael.jaquier@epfl.ch>
 * Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
 */

#include "Expression.hpp"

Expression::Expression() {
    equation = "0";
}

// Univariate
Expression::Expression(const std::string &eq) {
    equation = eq;
}

// Systems
Expression::Expression(const std::vector<std::string> &eq) {
    for (std::string mEquation : eq) {
        equations.push_back(mEquation);
    }
}

void Expression::setEquation(const std::string &eq) {
    equation = eq;
}

std::string Expression::getEquation(){
    return equation;
}

double Expression::evaluate(double &value) {
    symbol_table_t symbol_table;
    symbol_table.add_variable("x", value);
    symbol_table.add_constants();

    expression_t expression;
    expression.register_symbol_table(symbol_table);

    parser_t parser;
    parser.compile(equation, expression);

    return expression.value();
}

double Expression::evaluate(std::vector<double> &value) {
    std::cout << "I've been called!" << std::endl;
    symbol_table_t symbol_table;
    double x = value.at(0);
    symbol_table.add_variable("x", x);
    if (value.size() != 1) {
        double y = value[1];
        symbol_table.add_variable("y", y);
        if (value.size() == 3) {
            double z = value[2];
            symbol_table.add_variable("z", z);
        }
    }
    symbol_table.add_constants();

    expression_t expression;
    expression.register_symbol_table(symbol_table);

    parser_t parser;
    parser.compile(equation, expression);

    return expression.value();
}
