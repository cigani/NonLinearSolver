/* AUTHORS:
* Jaquier, Michael <michael.jaquier@epfl.ch>
* Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
*/

#ifndef PCSC_NONLINEAR_SYSTEMS_PROJECT_TESTSUIT_H
#define PCSC_NONLINEAR_SYSTEMS_PROJECT_TESTSUIT_H


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


    void iterateVectors(std::vector<std::string> &returns);

    void testDeterm();

    void testAsssertion(const double tol, const double expected,
                        const double &testNewton, std::string name);

    void testErrorCode(std::string &ErrorType);

    template<typename T>
    void iterateNestedVectors(const std::vector<T> &assertResults,
                              std::vector<std::vector<T>> &returns,
                              typename std::vector<std::__1::vector<T>>::const_iterator returns_iterator,
                              typename std::vector<T>::const_iterator &returns_iterator2,
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

    template<typename T>
    void iteratate(std::vector<T> &fxNeg, std::string name) const;

    void testNonLinearSystems();

};

#endif //PCSC_NONLINEAR_SYSTEMS_PROJECT_TESTSUIT_H
