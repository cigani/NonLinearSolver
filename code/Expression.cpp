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

Expression::Expression(const std::string &eq) {
    equation = eq;
}

Expression::~Expression() {}

void Expression::setEquation(const std::string &eq){
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
