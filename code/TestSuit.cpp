/* AUTHORS:
* Jaquier, Michael <michael.jaquier@epfl.ch>
* Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
*/

#include <cfloat>
#include "TestSuit.h"
#include "EquationTools.h"
#include "Bisection.hpp"
#include "Aitken.hpp"
#include "NewtonSystem.hpp"

std::vector<std::string> mErrors;

int main(int argc, char* argv[]) {
    TestSuit test;

    // Equations
    std::string mPolyCoefficient = "x^2 -10";
    std::string mZeroDerivativeCheck = "x^2 - x^3 -x^6 +x^7 +22x^3 -33x^6 +20";
    std::string mLogCoefficient = "log(x) - 10";
    std::string mTrigCoefficient = "cos(2*pi*x) + sin(2*pi*x)";
    std::string mExpCoefficient = "exp(x) - 100";
    std::string mNoDerivative = "10";

    // Derivatives
    std::string mPolyDer = "2x";
    std::string mZeroDer = "2x - 3x^2 -6x^5 + 7x^6 + 22*3x^2 -33*6x^5";
    std::string mLogDer = "1/x";
    std::string mTrigDer = "2*pi(cos(2*pi*x) - sin(2*pi*x))";
    std::string mExpDer = "exp(x)";
    std::string mNoDer = "0.0";

    // Equation Vector
    std::vector<std::string> equations{mPolyCoefficient, mZeroDerivativeCheck,
                                       mLogCoefficient, mTrigCoefficient,
                                       mExpCoefficient, mNoDerivative};

    // Derivative Vector
    std::vector<std::string> derivatives{mPolyDer, mZeroDer, mLogDer, mTrigDer,
                                         mExpDer, mNoDer};

    // Vectors
    const std::vector<double> mTestVector{3.0, -4.0, 10.0, -22.0, 10.0, -2.0};
    const std::vector<double> mNeverDerivative{10};
    const std::vector<double> mAnswerVector{3.16227766517654, 1.05686,
                                            22026.4657948162, 0.8749999979997,
                                            4.6052, -0.807004};

    // Tests
    test.testChordSolver(0.0015, mAnswerVector.at(0), 3, 1000, false,
                         equations.at(0));

    test.testNewtonSolver(0.0015, mAnswerVector.at(0), 3, 1000, false,
                          equations.at(0), derivatives.at(0));

    test.testNewtonWithExprtkPoly(0.0015, mAnswerVector.at(1), 1.1, 1000,
                                  false, equations.at(1), derivatives.at(1));

    test.testNewtonWithExprtkLog(0.0015, mAnswerVector.at(2), 10.0, 1000,
                                 false, equations.at(2), derivatives.at(2));

    test.testNewtonWithExprtTrig(0.0015, mAnswerVector.at(3), 1, 1000, false,
                                 equations.at(3), derivatives.at(3));

    test.testNewtonWithExprtExp(0.0015, mAnswerVector.at(4), 0, 1000, false,
                                equations.at(4), derivatives.at(4));

    test.testBisectionWithExprtPoly(0.0015, mAnswerVector.at(0), 3, 1000,
                                    false,
                                    equations.at(0));

    test.testAitkenWithExprtPoly(0.0015, 1.0, 99, 1000, false,
                                 equations.at(3));

    test.testDeterm();
    test.testSubtract();
    test.testSystems();
    test.testNonLinearSystems();

    // Error Logging
    test.iterateVectors(mErrors);

    return 0;

};

void TestSuit::testAsssertion(const double tol, const double expected,
                              const double &testNewton,
                              std::string name) {

    double test = testNewton;
    if (isnan(test)) { testErrorCode(name); }
    if (isinf(test)) { testErrorCode(name); }
    if (fabs(expected - test) >= tol) { testErrorCode(name); }
}

void TestSuit::testAsssertion(std::vector<std::string> expected,
                              std::vector<std::string> actual,
                              std::string name) {
    for (int i = 0; i < actual.size(); i++) {
        if (expected[i] != actual[i]) {
            testErrorCode(name);
            std::cout << expected[i] << " | " << actual[i] << "\n";
        }
    }
}

void TestSuit::testAsssertion(std::vector<double> expected,
                              std::vector<double> actual,
                              std::string name) {
    for (unsigned long i = 0; i < actual.size(); i++) {
        double evaluate = expected.at(i) - actual.at(i);
        if (fabs(evaluate) > 0.0015) {
            testErrorCode(name);
            std::cout << "Expected: " << expected[i] << " | "
                      << "Actual: " << actual[i] << "\n";
        }
    }
}

void
TestSuit::testChordSolver(const double tol, const double expected,
                          const int x0,
                          const int max, const bool verbose, std::string &eq) {

    Expression equation = adaptor(eq);
    double value = adaptor(x0);
    Chord testChord(equation, value, tol, max, verbose);
    double *chordRealValue = new double;
    *chordRealValue = testChord.solve();
    testAsssertion(tol, expected, *chordRealValue, std::string("Chord"));

    delete (chordRealValue);

};

void
TestSuit::testNewtonSolver(const double tol, const double expected,
                           const double x0,
                           const int max, const bool verbose, std::string &eq,
                           std::string &der) {
    Expression equation = adaptor(eq);
    Expression derivative = adaptor(der);
    double value = adaptor(x0);
    Newton testNewton(equation, derivative, value, tol, max, verbose);
    double *newtonRealValue = new double;
    *newtonRealValue = testNewton.solve();

    testAsssertion(tol, expected, *newtonRealValue, std::string("PolyNewton"));

    delete (newtonRealValue);
}

void
TestSuit::testNewtonWithExprtkPoly(const double tol, const double expected,
                                   const double x0, const int max,
                                   const bool verbose, std::string &eq,
                                   std::string &der) {
    Expression equation = adaptor(eq);
    Expression derivative = adaptor(der);
    double value = adaptor(x0);
    double testNewton;
    Newton mNewton(equation, derivative, value, tol, max, verbose);
    testNewton = mNewton.solve();

    testAsssertion(tol, expected, testNewton, eq);
}

void
TestSuit::testNewtonWithExprtkLog(const double tol, const double expected,
                                  const double x0, const int max,
                                  const bool verbose, std::string &eq,
                                  std::string &der) {
    double testNewton;
    Expression derivative = adaptor(der);
    Expression equation = adaptor(eq);
    double value = adaptor(x0);
    Newton mNewton(equation, derivative, value, tol, max, verbose);
    testNewton = mNewton.solve();

    testAsssertion(tol, expected, testNewton, std::string("NewtonExprtkLog"));
}

void
TestSuit::testNewtonWithExprtTrig(const double tol, const double expected,
                                  const double x0, const int max,
                                  const bool verbose, std::string &eq,
                                  std::string &der) {
    double testNewton;
    Expression equation = adaptor(eq);
    Expression derivative = adaptor(der);
    double value = adaptor(x0);
    Newton mNewton(equation, derivative, value, tol, max, verbose);
    testNewton = mNewton.solve();

    testAsssertion(tol, expected, testNewton, std::string("NewtonExprtkTrig"));

}

void
TestSuit::testNewtonWithExprtExp(const double tol, const double expected,
                                 const double x0, const int max,
                                 const bool verbose,
                                 std::string &eq, std::string &der) {
    double testNewton;
    Expression equation = adaptor(eq);
    Expression derivative = adaptor(der);
    double value = adaptor(x0);
    Newton mNewton(equation, derivative, value, tol, max, verbose);
    testNewton = mNewton.solve();

    testAsssertion(tol, expected, testNewton, std::string("NewtonExprtkExp"));
}

void
TestSuit::testBisectionWithExprtPoly(const double tol, const double expected,
                                     const double x0, const int max,
                                     const bool verbose, std::string &eq) {
    double testBisection;
    Expression equation = adaptor(eq);
    double value = adaptor(x0);
    Bisection mBisection(equation, value, tol, max, verbose, 0, 100);
    testBisection = mBisection.solve();

    testAsssertion(tol, expected, testBisection, std::string("Bisection"));
}


void TestSuit::testAitkenWithExprtPoly(const double tol, const double expected,
                                       const double x0, const int max,
                                       const bool verbose, std::string &eq) {
    double testAitken;
    Expression equation = adaptor(eq);
    double value = adaptor(x0);
    Aitken mAitken(equation, value, tol, max, verbose);
    testAitken = mAitken.solve();

    testAsssertion(tol, expected, testAitken, std::string("Aitken"));
}

void TestSuit::testSystems() {
    ExpressionSystem expressionSystem("_equations.txt");
    ExpressionSystem derivativeSystem("_derivative.txt");
    std::vector<double> expectedVals{2, 5};
    std::vector<double> expectedDerdouble{1, 0.333333, -1, 2};
    std::vector<std::string> expectedDer{"1", "1/3", "-1", "2"};
    std::vector<double> valz{3, 2};
    std::vector<std::string> expected{"x+y/3", "-x+2y"};
    std::vector<double> resultNewton;
    std::vector<double> expectedArray{0.0, 0.0};

    Expression mExp = expressionSystem.getEquation(0, 0);
    Expression mExp2 = expressionSystem.getEquation(1, 0);
    std::vector<std::string> actual{mExp.getEquation(), mExp2.getEquation()};
    testAsssertion(expected, actual, std::string("Test Systems"));

    Expression mdExp = derivativeSystem.getEquation(0, 0);
    Expression mdExp2 = derivativeSystem.getEquation(0, 1);
    Expression mdExp3 = derivativeSystem.getEquation(1, 0);
    Expression mdExp4 = derivativeSystem.getEquation(1, 1);
    std::vector<std::string> actualDer{mdExp.getEquation(),
                                       mdExp2.getEquation(),
                                       mdExp3.getEquation(),
                                       mdExp4.getEquation()};
    testAsssertion(expectedDer, actualDer, std::string("Derivative Systems"));

    std::vector<double> evaluatedDer{mdExp.evaluate(valz),
                                     mdExp2.evaluate(valz),
                                     mdExp3.evaluate(valz),
                                     mdExp4.evaluate(valz)};
    testAsssertion(expectedDerdouble, evaluatedDer,
                   std::string("Derivative Return"));

    NewtonSystem newtonSystem(expressionSystem, derivativeSystem, valz,
                              0.0001, 500, false);

    resultNewton = newtonSystem.solve();

    testAsssertion(expectedArray, resultNewton, std::string("NewtonSystem"));

}

void TestSuit::testNonLinearSystems() {
    std::__1::vector<double> val2{10, 6.1};
    std::vector<double> expected{2.44710116609237, 1.83532587456419};
    std::vector<double> resultNewton;

    ExpressionSystem expressionSystem2("_equationNonLinear");
    ExpressionSystem derivativeSystem2("_derivativeNonLinear");
    NewtonSystem newtonSystem2(expressionSystem2, derivativeSystem2, val2,
                               0.0001, 500, false);
    resultNewton = newtonSystem2.solve();

    testAsssertion(expected, resultNewton, std::string("NonLinear System"));
}

void TestSuit::testErrorCode(std::string &ErrorType) {
    mErrors.push_back(ErrorType);
}

void TestSuit::testDeterm() {
    std::vector<std::vector<double> > values(0, std::vector<double>());
    std::vector<double> val1{4, 3, 2, 1};
    std::vector<double> val2{1, 2, 3, 4};
    std::vector<double> val3{3, 2, 1, 4};
    std::vector<double> val4{4, 2, 1, 3};
    values.push_back(val1);
    values.push_back(val2);
    values.push_back(val3);
    values.push_back(val4);
    EquationTools mEquations;
    double det = mEquations.Determinant(values, (const int) values.size());
//    std::cout<<"det" << det << std::endl;
    testAsssertion(0.0015, -20, det, std::string("Determinant"));
}

void TestSuit::testSubtract() {
    std::vector<double> v1{1, 2, 3, 4};
    std::vector<double> v2{4, 3, 2, 1};
    std::vector<double> assertVector{-3, -1, 1, 3};
    EquationTools mEquations;
    std::vector<double> testVector = mEquations.subtractVectors(v1, v2);
    for (int n = 0; n != v1.size(); n++) {
        testAsssertion(0.1, assertVector[n], testVector[n],
                       std::string("subtract))"));
    }
}

template<typename T>
void
TestSuit::iteratate(std::vector<T> &fxNeg, std::string name) const {
    typename std::__1::vector<T>::const_iterator returns_iterator;

    for (returns_iterator = fxNeg.begin(); returns_iterator != fxNeg.end();
         ++returns_iterator) {
        std::__1::cout << name << " | " << *returns_iterator << "\n";
    }
}

template<typename T>
void TestSuit::iterateNestedVectors(
        const std::vector<T> &assertResults,
        std::vector<std::vector<T>> &returns,
        typename std::vector<std::vector<T>>::const_iterator returns_iterator,
        typename std::vector<T>::const_iterator &returns_iterator2,
        std::string name) {

    int n = 0;
    for (returns_iterator = returns.begin(); returns_iterator != returns.end();
         ++returns_iterator) {
        for (returns_iterator2 = (*returns_iterator).begin();
             returns_iterator2 != (*returns_iterator).end();
             ++returns_iterator2) {
            // This is an interesting trick to inc while still evaluating
            // Prefix vs Postfix ++;
            testAsssertion(0.015, assertResults[n++],
                           *returns_iterator2,
                           name);
            //std::cout << *returns_iterator2 << "\n";
        }
    }
}

void TestSuit::iterateVectors(std::vector<std::string> &returns) {

    if (returns.size() != 0) {
        copy(returns.begin(), returns.end(),
             std::ostream_iterator<std::string>(std::cout, "\n"));
        std::cout << std::endl;
    } else std::cout << "~~~ No Errors ~~~" << std::endl;
}

double TestSuit::adaptor(double val) {
    //std::vector<double> values;
    //values.push_back(val);
    double values = val;
    return values;
}

Expression TestSuit::adaptor(std::string &eq) {
    //std::vector<Expression> equation;
    Expression mEquation = eq;
    //equation.push_back(mEquation);
    return mEquation;
}
