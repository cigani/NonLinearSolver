/* AUTHORS:
* Jaquier, Michael <michael.jaquier@epfl.ch>
* Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
*/

#ifndef PCSC_NONLINEAR_SYSTEMS_PROJECT_TESTSUIT_H
#define PCSC_NONLINEAR_SYSTEMS_PROJECT_TESTSUIT_H

#include "Equations.hpp"
#include "Chord.hpp"
#include "Newton.hpp"
#include "FixedPoint.hpp"
#include <assert.h>
#include "exprtk.hpp"
#include <vector>

class TestSuit: Chord {
public:
    void testChordSolver(const double tol, const double expected,
                         const int x0, const int max, const bool verbose,
                         const std::vector<double> &vector);

    void testNewtonSolver(const double tol, const double expected,
                          const double x0, const int max, const bool verbose,
                          const std::vector<double> &vector);

    void testFixedPointSolver();

    void testNewtonWithExprtkPoly(const double tol, const double expected,
                                  const double x0, const int max,
                                  const bool verbose,
                                  std::string &coefficient);

    void testNewtonWithExprtTrig(const double tol, const double expected,
                                 const double x0, const int max,
                                 const bool verbose,
                                 std::string &coefficient);

    void testNewtonWithExprtExp(const double tol, const double expected,
                                const double x0, const int max,
                                const bool verbose,
                                std::string &coefficient);


    void testNewtonWithExprtkLog(const double tol, const double expected,
                                 const double x0, const int max,
                                 const bool verbose,
                                 std::string &coefficient);

    void testExprtkJacobian();


private:
    //const std::vector<double> mTestVector{3.0, -4.0, 10.0, -22.0, 10.0, -2.0};
    static void testAsssertion(const double tol, const double expected,
                               double testNewton, std::string name);

    static void testErrorCode(std::string &ErrorType);

    void iterateNestedVectors(const std::vector<double> &assertResults,
                              std::vector<std::vector<double>> &returns,
                              std::vector<std::__1::vector<double>>::iterator &returns_iterator,
                              std::vector<double>::iterator &returns_iterator2);

    void iterateVectors(const std::vector<double> &assertResults,
                        std::vector<std::string> &returns);
};

#endif //PCSC_NONLINEAR_SYSTEMS_PROJECT_TESTSUIT_H
