//
// Created by Alexander Lorkowski on 12/15/16.
//

#ifndef INITIALVECTOR_HPP_
#define INITIALVECTOR_HPP_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class InitialVector {
private:
    /// System of <doubles> expressions.
    std::vector<double> mInitialVector;
    /// Filename to load our matrix from.
    std::string filename;
    void read();

    /// Rows and columns present in the matrix
    int rows;
    int columns;

public:
    ///Constructor to generate the system of equations
    InitialVector(std::string input);
    InitialVector();
    virtual ~InitialVector();

    /// Method to return the values contained in the vector.
    std::vector<double> getValues();

    /// Method to print out the equations
    void print();

    /// \brief Method to return an individual equation from the system matrix
    /// \param i  The index of the value to be returned.
    /// \return  Returns a Expression which contains a single equation.
    double getValue(int i);
};


#endif //INITIALVECTOR_HPP_
