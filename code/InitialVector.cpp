/*
 * InitialVector.cpp
 *
 * DESCRIPTION: Class responsible from reading a file and putting it into a vector.
 *
 * Created on: December 14, 2016
 *
 * AUTHORS:
 * Jaquier, Michael <michael.jaquier@epfl.ch>
 * Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
 */

#include <cassert>
#include <sstream>
#include "InitialVector.hpp"

InitialVector::InitialVector(std::string input) {
    filename = input;
    read();
}

InitialVector::InitialVector() {}

InitialVector::~InitialVector() {};

void InitialVector::read() {
    rows = 0;
    columns = 0;
    std::ifstream fin(filename);
    assert(fin.is_open());
    std::string line;
    while (std::getline(fin, line)) {                       // for each line
        mInitialVector.push_back(std::stod(line));          // add to the current row
    }
}

std::vector<double> InitialVector::getValues() {
    return mInitialVector;
}

double InitialVector::getValue(int i) {
    return mInitialVector.at(i);
}

void InitialVector::print() {
    std::vector<double>::iterator row;

    for (row = mInitialVector.begin(); row != mInitialVector.end(); ++row) {
            std::cout << (*row) << std::endl;
    };
}
