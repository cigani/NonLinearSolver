#include <iostream>
#include "Exception.hpp"

//Constructor
Exception::Exception(std::string tagString, std::string probString) {
    mProblem = probString;
    mTag = tagString;
}

void Exception::PrintDebug() const {
    std::cerr << "\n** Error ("<< mTag <<") **\n";
    std::cerr << "Problem: " << mProblem << "\n\n";
}