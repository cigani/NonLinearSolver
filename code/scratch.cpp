//
/* AUTHORS:
* Jaquier, Michael <michael.jaquier@epfl.ch>
* Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
*/
//

#include <iostream>
#include "exprtk.hpp"

void ExtractMinor(std::vector<std::vector<double>> &M,
                  const int size,
                  const int col,
                  std::vector<std::vector<double>> &minor) {
    for (int row = 1; row < size; ++row) {
        for (int k = 0; k < col; ++k) {
            minor[row - 1][k] = M[row][k];
        }
        for (int k = col + 1; k < size; ++k) {
            minor[row - 1][k - 1] = M[row][k];
        }
    }
}

int main() {
//    square_wave();
    std::string mPolyCoefficient = "x^2 -10";
    std::vector<std::vector<double> > values(0, std::vector<double>(3));
    std::vector<double> val1{2, 3, 4};
    values.push_back(val1);
    values.push_back(val1);
    //std::cout << values.size() << std::endl;
//    copy(val1.begin(), val1.end(),
//         std::ostream_iterator<double>(std::cout, "\n"));


    //printf(mExpression.results())
    //printf("%19.15f", mExpression.value());

    return 0;
}