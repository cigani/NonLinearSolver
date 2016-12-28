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

Expression::Expression() {
    equation_ = "0";
}

void Expression::setEquation(const std::string &eq) {
    equation_ = eq;
    generateEquation();
}

Expression::Expression(const std::string &eq)
        : equation_(eq) {
    generateEquation();
}

void Expression::generateEquation() {
    symbol_table_t symbol_table;
    symbol_table.create_variable("x", 0.0);
    symbol_table.create_variable("y", 0.0);
    symbol_table.create_variable("z", 0.0);
    symbol_table.add_constants();

    var_.push_back(symbol_table.variable_ref("x"));
    var_.push_back(symbol_table.variable_ref("y"));
    var_.push_back(symbol_table.variable_ref("z"));

    expression_.register_symbol_table(symbol_table);

    parser_t parser;

    if (!parser.compile(equation_, expression_)) {
        printf("ERROR - Failed to compile: %s\n", equation_.c_str());
    }
}

std::string Expression::getEquation() {
    return equation_;
}

Expression::T Expression::evaluate(const T &x) {
    var_[e_x].get() = x;
    //std::cout << var_[e_x] << "\t" << expression_.value() << "\n";
    return expression_.value();
}

Expression::T Expression::evaluate(const std::vector<T> &values) {
    switch (values.size()) {
        case 3 :
            var_[e_z].get() = values[e_z];
        case 2 :
            var_[e_y].get() = values[e_y];
        case 1 :
            var_[e_x].get() = values[e_x];
        default:
            break;
    }

    return expression_.value();
}

Expression::T Expression::deriv(std::vector<T> &value,
                                std::string withrespect) {
    switch (value.size()) {
        case 3 :
            var_[e_z].get() = value[e_z];
        case 2 :
            var_[e_y].get() = value[e_y];
        case 1 :
            var_[e_x].get() = value[e_x];
        default:
            break;
    }
    return exprtk::derivative(expression_, withrespect);
}


