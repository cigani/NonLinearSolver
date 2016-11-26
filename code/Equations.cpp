//
// Created by Michael Jaquier on 26.11.16.
//

#include <Equations.hpp>

int main(int argc, char* argv[]) {
    const int n = argc - 2;
    double input = std::atof(argv[1]);
    std::vector<double> finalVector;
    for (int i = 0; i < n; ++i){
        std::cout <<  "arg: " << std::atof(argv[i+2]) << std::endl;
        finalVector.push_back(std::atof(argv[i + 2]));
    }
    std::cout <<"input: " << input << std::endl;
    Equations::PolyEquations(input, (const std::vector<double> &) finalVector);
    return 0;
}

/// Inputs N - Power of Polynomial needs to be given in order. coef of x1^1..x2^2 --> a_0 + a_1 ... etc


double Equations::PolyEquations(double x, const std::vector<double>& p) {
    double value;
    double dv;
    for (unsigned int i=0; i<p.size(); ++i){
        //TODO: Remove these outputs once we're done testing. Same for dv.
        //std::cout <<"vals " << pow(x, i)*p[i] << std::endl;
        value += pow(x, i)*p[i];
        }

    for (unsigned int i=1; i<p.size(); ++i){
        dv += pow(x, i)*(i+1)*p[i];
        std ::cout <<"dv o : " << dv << std::endl;
        //std::cout <<"dvs " << pow(x, i-1)*i*p[i] << std::endl;
    }
    std::cout <<"value: " << value << std::endl;
    std::cout <<"dv: " << dv << std::endl;
    return 0.0;

}
