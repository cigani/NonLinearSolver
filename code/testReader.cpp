#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "string.hpp"
#include "ExpressionSystem.hpp"

int main(int argc, char *argv[]) {

    if (argc < 3) {
        return 1;
    }

    ExpressionSystem functions(argv[1]);
    ExpressionSystem jacobian(argv[2]);

    std::cout << "F(x)" << std::endl;
    functions.print();

    std::cout << std::endl;
    std::cout << "J(x)" << std::endl;
    jacobian.print();

    std::cout << std::endl;
    std::cout << "F(x) at (0,0)" << std::endl;
    std::cout << functions.getEquation(0,0).getEquation() << std::endl;
    std::cout << "F(x) at (1,0)" << std::endl;
    std::cout << functions.getEquation(1,0).getEquation() << std::endl;

    return 0;
}


