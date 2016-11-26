//
// Created by Michael Jaquier on 26.11.16.
//

#include <Equations.hpp>


Equations::~Equations() {}

int main(int argc, char* argv[]) {
    const int n = argc - 1;
    std::vector<double> finalVector;
    for (int i = 0; i < n; ++i) {
        finalVector.push_back(std::atof(argv[i + 1]));
    }

    Equations::Equations((const std::vector<double> &) finalVector);
    return 0;
}

/// Inputs N - Power of Polynomial needs to be given in order. coef of x1^1..x2^2 --> a_0 + a_1 ... etc


Equations::Equations(const std::vector<double>& p) {
    double value;
    for (unsigned int i=0; i<p.size(); ++i){
        std::cout <<"vals " << pow(p[i], i) << std::endl;
        value += pow(p[i], i);
        }
    std::cout << "value " << value << std::endl;
    double dv;
    for (unsigned int i=1; i<p.size(); ++i){
        dv += pow(p[i-1], i-1)/i;
        std::cout <<"dvs " << pow(p[i-1], i-1)/i << std::endl;
    }
    std::cout <<"derivative " << dv << std::endl;
}
