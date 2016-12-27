/* AUTHORS:
* Jaquier, Michael <michael.jaquier@epfl.ch>
* Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
*/

#ifndef PCSC_NONLINEAR_SYSTEMS_PROJECT_TESTSUIT_H
#define PCSC_NONLINEAR_SYSTEMS_PROJECT_TESTSUIT_H


#include "Chord.hpp"
#include "Newton.hpp"
#include "FixedPoint.hpp"
#include "exprtk.hpp"
#include "ExpressionSystem.hpp"
#include "Tests.h"
#include "EquationTools.h"
#include "Bisection.hpp"
#include "Aitken.hpp"
#include "NewtonSystem.hpp"
#include <vector>
#include <cfloat>
#include <assert.h>
#include "string.hpp"


class TestSuit {
private:

    //Tools
    EquationTools convert;

    // Default Parameters
    const double tolerance = 0.0015;
    const int maxIter = 1000;
    const bool verbosity = false;

    // Equations
    Expression mPolyCoefficient = Expression("x^2 -10");
    Expression mZeroDerivativeCheck = Expression("x^2 - x^3 -x^6 +x^7 +22x^3 -33x^6 +20");
    Expression mLogCoefficient = Expression("log(x) - 10");
    Expression mTrigCoefficient = Expression("cos(2*pi*x) + sin(2*pi*x)");
    Expression mExpCoefficient = Expression("exp(x) - 100");
    Expression mNoDerivative = Expression("10");
    Expression mPolyMultiplicity = Expression("sin(x)^2");

    // Derivatives
    Expression mPolyDer = Expression("2x");
    Expression mZeroDer = Expression("2x - 3x^2 -6x^5 + 7x^6 + 22*3x^2 -33*6x^5");
    Expression mLogDer = Expression("1/x");
    Expression mTrigDer = Expression("2*pi(cos(2*pi*x) - sin(2*pi*x))");
    Expression mExpDer = Expression("exp(x)");
    Expression mNoDer = Expression("0.0");
    Expression mPolyMultiplicityDer = Expression("2*sin(x)*cos(x)");

    // Equation Vector
    std::vector<Expression> equations{mPolyCoefficient, mZeroDerivativeCheck,
                                       mLogCoefficient, mTrigCoefficient,
                                       mExpCoefficient, mNoDerivative,
                                      mPolyMultiplicity};

    // Derivative Vector
    std::vector<Expression> derivatives{mPolyDer, mZeroDer, mLogDer, mTrigDer,
                                         mExpDer, mNoDer,
                                        mPolyMultiplicityDer};

    // Expected Results
    const std::vector<double> expectedresult{3.16227766517654, 1.05686,
                                            22026.4657948162, 0.8749999979997,
                                            4.6052, -0.807004, 3.14159265330048};
public:
    std::vector<std::string> mErrors;

    void testChordSolver(const double x0);
    void testNewtonSolver(const double x0);
    void testNewtonWithExprtkPoly(const double x0);
    void testNewtonWithExprtTrig(const double x0);
    void testNewtonWithExprtExp(const double x0);
    void testNewtonWithExprtkLog(const double x0);
    void testDeterm();

    void testAsssertion(const double expected, const double &result,
                        std::string name);

    void testErrorCode(std::string &ErrorType);
    void testSubtract();
    void testBisectionWithExprtPoly(const double x0);
    void testAitkenWithExprtPoly(const double x0);
    void testSystemsLoading();
    void testAsssertion(std::vector<std::string> expected,
                        std::vector<std::string> actual, std::string name);
    void
    testAsssertion(std::vector<double> expected, std::vector<double> actual,
                   std::string name);
    void testNonLinearSystems();
    void iterateVectors(std::vector<std::string> &returns);
    void testLinearSystem();

    void testSystemsJacobian();

    void testFixedPointWithExprtPoly(const double x0);

    void testAitkenWithExprtZeroDerivative(const double x0);

    void testNewtonSolverExprtkZeroDerivative(const double x0);
};

#endif //PCSC_NONLINEAR_SYSTEMS_PROJECT_TESTSUIT_H
