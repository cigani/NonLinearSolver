//
/* AUTHORS:
* Jaquier, Michael <michael.jaquier@epfl.ch>
* Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
*/
//

#include <iostream>
#include "exprtk.hpp"


std::__1::vector<double> negateVector(
        std::__1::vector<double> &v1) {
    std::__1::vector<double> result;
    transform(v1.begin(), v1.end(), back_inserter(result),
              [](double v1) { return (-v1); });
    return result;
}

void printVec(std::vector<double> &dx) {
    std::vector<double>::const_iterator c;
    for (c = dx.begin(); c != dx.end();
         ++c) {
        std::cout << *c << "\n";
    };
}

int main() {
    std::vector<double> dx{1, 2, 3, 4, 5};
    std::vector<double> mx = negateVector(dx);
    printVec(dx);
    printVec(mx);

    return 0;
}