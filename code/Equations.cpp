//
// Created by Michael Jaquier on 26.11.16.
//

#include <Equations.hpp>

int main(int argc, char* argv[]) {
    const int n = argc - 2;
    double input = std::atof(argv[1]);
    std::vector<double> finalVector;
    for (int i = 0; i < n; ++i){
        finalVector.push_back(std::atof(argv[i + 2]));
    }
    Equations::polyEquations(input, (const std::vector<double> &) finalVector);
    Equations::polyDerivative(input, (const std::vector<double> &) finalVector);

    return 0;
}

/// Inputs N - Power of Polynomial needs to be given in order. coef of x1^1..x2^2 --> a_0 + a_1 ... etc


double Equations::polyEquations(double x, const std::vector<double> &p) {
    double value;
    for (unsigned int i=0; i<p.size(); ++i){
        value += pow(x, i)*p[i];
        }

    return value;

}
double Equations::polyDerivative(double x, const std::vector<double> &p) {
    double dv;
    for (unsigned int i=1; i<p.size(); ++i){
        dv += pow(x, i)*(i+1)*p[i];
    }

    return dv;

}
