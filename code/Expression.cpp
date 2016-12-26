/*
 * Expression.cpp
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

//Expression::Expression() {
//    equation = "0";
//}

void Expression::setEquation(const std::string &eq) {
    equation = eq;
}

Expression::Expression(const std::string &eq)
        : equation(eq),
          x_(0.0), y_(0.0), z_(0.0) {
    equation = eq;

    symbol_table_t symbol_table;
    symbol_table.add_variable("x", x_);
    symbol_table.add_variable("y", y_);
    symbol_table.add_variable("z", z_);
    symbol_table.add_constants();

    expression_.register_symbol_table(symbol_table);

    parser_t parser;
//    if (!parser.compile(equation, expression_))
//    {
//        // error... throw an exception or perform some
//        // kind of error handling.
//    }
    parser.compile(equation, expression_);
}

std::string Expression::getEquation(){
    return equation;
}

double Expression::evaluate(double &value) {
    x_ = value;
    std::cout << expression_.value() << "\t" << x_ << "\t" << "\n";
    return expression_.value();

}

double Expression::evaluate(std::vector<double> &value) {
    switch (value.size()) {
        case 3 :
            z_ = value[2];
        case 2 :
            y_ = value[1];
        case 1 :
            x_ = value[0];
        default :
            std::cout << "BROKEN EVALUATE MATE" << "\n";
    }

    return expression_.value();
}

double Expression::deriv(std::vector<double> &value, std::string withrespect) {
    return exprtk::derivative(expression_, withrespect);
}