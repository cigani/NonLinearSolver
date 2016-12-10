//
// Created by Alexander Lorkowski on 12/10/16.
//

#include "Helper.hpp"

Helper::Helper(std::string name) {
	programName = name;
}

Helper::~Helper() {};

std::string Helper::stringPadding(std::string original, size_t charCount) {
    original.resize(charCount, ' ');
    return original;
}

void Helper::show_usage() {
    std::cerr << std::endl
              << "Usage: "
              << programName
              << " -m %s"
              << " -e '%s'"
              << " -d '%s'"
              << " -xi %d"
              << " -nmax %i"
              << " -t %d"
              << " -v %b"
              << " -l %d"
              << " -u %d"
              << std::endl
              << std::endl
              << "Required:\n"
              << "\t"
              << stringPadding("-m,--method", 20)
              << stringPadding("Specify Non-Linear Solver", 60)
              << std::endl
              << "\t"
              << stringPadding("-e,--expression", 20)
              << stringPadding(
                      "Mathematical expression to solve enclosed in ''", 60)
              << std::endl
              << std::endl
              << "Newton Requirement:\n"
              << "\t"
              << stringPadding("-d,--derivative", 20)
              << stringPadding(
                      "The derivative to solve enclosed in ''", 60)
              << std::endl
              << std::endl
              << "Optional:\n"
              << "\t"
              << stringPadding("-h,--help", 20)
              << stringPadding("Show this help message", 60)
              << std::endl
              << "\t"
              << stringPadding("-xi", 20)
              << stringPadding("Initial guess of the solution [default: 0.0]",
                               60)
              << std::endl
              << "\t"
              << stringPadding("-nmax", 20)
              << stringPadding("Maximum number of iterations [default: 1000]",
                               60)
              << std::endl
              << "\t"
              << stringPadding("-t", 20)
              << stringPadding("The convergence tolerance [default: 0.001]",
                               60)
              << std::endl
              << "\t"
              << stringPadding("-v", 20)
              << stringPadding(
                      "print all intermediate calculations [default: false]",
                      60)
              << std::endl
              << "\t"
              << stringPadding("-l", 20)
              << stringPadding(
                      "The lower bound of the search interval [default: -1.0]",
                      60)
              << std::endl
              << "\t"
              << stringPadding("-u", 20)
              << stringPadding(
                      "The upper bound of the search interval [default: 1.0]",
                      60)
              << std::endl;
    show_methods();
}

void Helper::show_methods() {
    std::cerr << std::endl
              << "Non-Linear Solvers:"
              << std::endl
              << "\t"
              << stringPadding("aitken", 20)
              << stringPadding("Aitken Method", 40)
              << std::endl
              << "\t"
              << stringPadding("bisection", 20)
              << stringPadding("Bisection Method", 40)
              << std::endl
              << "\t"
              << stringPadding("chord", 20)
              << stringPadding("Chord Method", 40)
              << std::endl
              << "\t"
              << stringPadding("fixedpoint", 20)
              << stringPadding("Fixed Point Method", 40)
              << std::endl
              << "\t"
              << stringPadding("newton", 20)
              << stringPadding("Newton Method", 40)
              << std::endl
              << std::endl;
}
