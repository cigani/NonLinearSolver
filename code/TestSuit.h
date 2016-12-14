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
#include "ExpressionSystem.hpp"
#include <vector>


class TestSuit {

public:
    void testChordSolver(const double tol, const double expected, const int x0,
                         const int max, const bool verbose, std::string &eq);

    void testNewtonSolver(const double tol, const double expected,
                          const double x0,
                          const int max, const bool verbose, std::string &eq,
                          std::string &der);

    void testFixedPointSolver();

    void testNewtonWithExprtkPoly(const double tol, const double expected,
                                  const double x0, const int max,
                                  const bool verbose, std::string &eq,
                                  std::string &der);

    void testNewtonWithExprtTrig(const double tol, const double expected,
                                 const double x0, const int max,
                                 const bool verbose, std::string &eq,
                                 std::string &der);

    void testNewtonWithExprtExp(const double tol, const double expected,
                                const double x0, const int max,
                                const bool verbose,
                                std::string &eq, std::string &der);


    void testNewtonWithExprtkLog(const double tol, const double expected,
                                 const double x0, const int max,
                                 const bool verbose, std::string &eq,
                                 std::string &der);

    void testExprtkJacobian();


    void iterateVectors(std::vector<std::string> &returns);

    void testDeterm();
    //const std::vector<double> mTestVector{3.0, -4.0, 10.0, -22.0, 10.0, -2.0};
    void testAsssertion(const double tol, const double expected,
                        const double &testNewton, std::string name);

    void testErrorCode(std::string &ErrorType);

    void iterateNestedVectors(const std::vector<double> &assertResults,
                              std::vector<std::vector<double>> &returns,
                              std::vector<std::__1::vector<double>>::const_iterator returns_iterator,
                              std::vector<double>::const_iterator &returns_iterator2,
                              std::string name = std::string("Jacobian"));

    void testSubtract();

    Expression adaptor(std::string &eq);

    double adaptor(double val);

    void testBisectionWithExprtPoly(const double tol, const double expected,
                                    const double x0, const int max,
                                    const bool verbose, std::string &eq);

    void testAitkenWithExprtPoly(const double tol, const double expected,
                                   const double x0, const int max,
                                   const bool verbose, std::string &eq);

    void testSystems();

    void testAsssertion(std::vector<std::string> expected,
                        std::vector<std::string> actual, std::string name);

    void
    testAsssertion(std::vector<double> expected, std::vector<double> actual,
                   std::string name);

    void iteratate(std::vector<double> &fxNeg, std::string name) const;

    void testNonLinearSystems();
};

#endif //PCSC_NONLINEAR_SYSTEMS_PROJECT_TESTSUIT_H
