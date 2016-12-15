//
// Created by Alexander Lorkowski on 12/11/16.
//

#include <cassert>
#include "ExpressionSystem.hpp"

ExpressionSystem::ExpressionSystem(std::string input) {
    filename = input;
    read();
}

ExpressionSystem::ExpressionSystem() {}

ExpressionSystem::~ExpressionSystem() {};

void ExpressionSystem::read() {
    rows = 0;
    columns = 0;
    int count = 0;
    std::ifstream fin(filename);
    assert(fin.is_open());
    std::string line;
    while (std::getline(fin, line)) {         // for each line
        std::vector<Expression> lineData;    // create a new row
        std::string val;
        std::istringstream lineStream(line);
        while (lineStream >> val) {           // for each value in line
            Expression eq(val);
            lineData.push_back(eq);          // add to the current row
            if ( count == 0 ) {
                columns++;
            }
        }
        system.push_back(lineData);        // add row to equations
        rows++;
        count++;
    }
}

std::vector<std::vector<Expression>> ExpressionSystem::getSystem() {
    return system;
}

Expression ExpressionSystem::getEquation(int i, int j) {
    return system.at(i).at(j);
}

void ExpressionSystem::print() {
    std::vector<std::vector<Expression>>::iterator row;
    std::vector<Expression>::iterator col;
    Expression value;

    for (row = system.begin(); row != system.end(); ++row) {
        for (col = row->begin(); col != row->end(); ++col) {
            std::cout << (*col).getEquation() << std::endl;
        }
    };
}

std::vector<std::vector<double>> ExpressionSystem::evaluate(std::vector<double> &value) {
    std::vector<std::vector<double>> results(rows, std::vector<double>(columns));
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            results[row][col] = system[row][col].evaluate(value);
        }
    }
    return results;
}

int ExpressionSystem::getColumns() {
    return columns;
}

std::vector<std::vector<double>>
ExpressionSystem::jacobian(std::vector<double> &value) {
    std::vector<std::vector<double>> results(rows,
                                             std::vector<double>(rows));
    std::vector<std::string> vars{"x", "y", "z"};
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < rows; col++) {
            std::cout << "Column \t" << col << "\t Row: \t" << row << "\n";
            results[row][col] = system[row][0].deriv(value, vars[col]);
        }
    }
    return results;
}