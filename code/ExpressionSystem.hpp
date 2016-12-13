//
// Created by Alexander Lorkowski on 12/11/16.
//

#ifndef EXPRESSIONSYSTEM_HPP_
#define EXPRESSIONSYSTEM_HPP_

#include "Expression.hpp"
#include "FileReader.hpp"
#include <vector>

class ExpressionSystem {
private:
    std::vector<std::vector<Expression>> system;    // System of equations
    std::string filename;
    void read();
    int rows;
    int columns;

public:
    ExpressionSystem(std::string input);
    ExpressionSystem();
    virtual ~ExpressionSystem();

    std::vector<std::vector<Expression>> getSystem();
    void print();
    Expression getEquation(int i, int j);
    std::vector<std::vector<double>> evaluate(std::vector<double> &value);

    int getColumns();

};


#endif //EXPRESSIONSYSTEM_HPP_
