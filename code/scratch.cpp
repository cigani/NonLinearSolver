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

std::vector<std::vector<double>>
createMinor(unsigned long size) {
    std::vector<std::vector<double>> minor(size, std::vector<double>(size));
    return minor;
}

double Determinant(std::vector<std::vector<double>> &M, const int size) {
    if (size == 2) {
        return M[0][0] * M[1][1] - M[0][1] * M[1][0];
    } else {
        double det = 0;
        for (int col = 0; col < size; ++col) {
            std::vector<std::vector<double>> minor = createMinor(
                    (unsigned long) size);
            ExtractMinor(M, size, col, minor);
            det += M[0][col] * std::pow(-1.0, col)
                   * Determinant(minor, size - 1);
        }
        return det;
    }
}



int main() {
    std::vector<std::vector<double> > values(0, std::vector<double>(4));
    std::vector<double> val1{4, 3, 2, 1};
    std::vector<double> val2{1, 2, 3, 4};
    std::vector<double> val3{3, 2, 1, 4};
    std::vector<double> val4{4, 2, 1, 3};
    // {{4,3,2,1},{1,2,3,4},{3,2,1,4},{4,2,1,3}}
    values.push_back(val1);
    values.push_back(val2);
    values.push_back(val3);
    values.push_back(val4);
//    std::cout << values[0][1] << std::endl;
//    std::cout << values.size() << std::endl;
    std::vector<double>::iterator myIterator;
    std::vector<std::vector<double>>::iterator i;
//    for (i = values.begin(); i != values.end(); ++i) {
//        for (myIterator = (*i).begin();
//             myIterator !=
//             (*i).end(); ++myIterator) {
//            std::cout << *myIterator << std::endl;
//        }
//    }
    //std::vector<std::vector<double>>mMinor = createMinor(values.size()-1);

    //ExtractMinor(values, (const int) values.size(), 1, mMinor);
    double det = Determinant(values, (const int) values.size());
    std::cout << det << "    " << "Det" << std::endl;
//    for (i = values.begin(); i != values.end(); ++i) {
//        for (myIterator = (*i).begin();
//             myIterator !=
//             (*i).end(); ++myIterator) {
//            std::cout << *myIterator << std::endl;
//        }
//    }
    return 0;
}