//! Gauss.hpp
/*!
  \brief A class containing the routine for Gaussian elimination.
  \author Jaquier, Michael <michael.jaquier@epfl.ch>
  \author Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
  \version 1.0
  \date  10 December 2016
  \remark Ecole Polytechnic Federal de Lausanne (EPFL)
  \remark MATH-458 Programming Concepts in Scientific Computing
*/

//
/* AUTHORS:
* Jaquier, Michael <michael.jaquier@epfl.ch>
* Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
*/
//

#ifndef PCSC_NONLINEAR_SYSTEMS_PROJECT_GAUSS_H
#define PCSC_NONLINEAR_SYSTEMS_PROJECT_GAUSS_H

#import <vector>

class Gauss {

public:
    /// \brief Generates a solution to Av = b. For vector (v).
    /// \param jacobian  The Jacobian (A)
    /// \param funcSolution The vector of solutions (b)
    /// \param degree Size of the vectors
    /// \return The Vector (v) solved
    std::vector<double> solveSystem(std::vector<std::vector<double>> &jacobian,
                                    std::vector<double> &funcSolution, int degree);
};


#endif //PCSC_NONLINEAR_SYSTEMS_PROJECT_GAUSS_H
