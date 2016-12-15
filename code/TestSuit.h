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
private:
    const double tolerance = 0.0015;
    const int maxIter = 1000;
    const bool verbosity = false;
    Expression mPolyCoefficient = Expression("x^2 -10");
    Expression mZeroDerivativeCheck = Expression("x^2 - x^3 -x^6 +x^7 +22x^3 -33x^6 +20");
    Expression mLogCoefficient = Expression("log(x) - 10");
    Expression mTrigCoefficient = Expression("cos(2*pi*x) + sin(2*pi*x)");
    Expression mExpCoefficient = Expression("exp(x) - 100");
    Expression mNoDerivative = Expression("10");

    // Derivatives
    Expression mPolyDer = Expression("2x");
    Expression mZeroDer = Expression("2x - 3x^2 -6x^5 + 7x^6 + 22*3x^2 -33*6x^5");
    Expression mLogDer = Expression("1/x");
    Expression mTrigDer = Expression("2*pi(cos(2*pi*x) - sin(2*pi*x))");
    Expression mExpDer = Expression("exp(x)");
    Expression mNoDer = Expression("0.0");

    // Equation Vector
    std::vector<Expression> equations{mPolyCoefficient, mZeroDerivativeCheck,
                                       mLogCoefficient, mTrigCoefficient,
                                       mExpCoefficient, mNoDerivative};

    // Derivative Vector
    std::vector<Expression> derivatives{mPolyDer, mZeroDer, mLogDer, mTrigDer,
                                         mExpDer, mNoDer};
    const std::vector<double> testVector{3.0, -4.0, 10.0, -22.0, 10.0, -2.0};
    const std::vector<double> neverDerivative{10};
    const std::vector<double> expectedresult{3.16227766517654, 1.05686,
                                            22026.4657948162, 0.8749999979997,
                                            4.6052, -0.807004};
public:
    void testChordSolver(const int x0);

    void testNewtonSolver(const double x0);

    void testNewtonWithExprtkPoly(const double x0);

    void testNewtonWithExprtTrig(const double x0);

    void testNewtonWithExprtExp(const double x0);


    void testNewtonWithExprtkLog(const double x0);


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

    void testBisectionWithExprtPoly(const double x0);

    void testAitkenWithExprtPoly(const double x0);

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
