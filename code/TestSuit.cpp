/* AUTHORS:
* Jaquier, Michael <michael.jaquier@epfl.ch>
* Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
*/

#include <cfloat>
#include "TestSuit.h"
#include "Jacobian.h"
#include "EquationTools.h"

std::vector<std::string> mErrors;

int main(int argc, char* argv[]) {
    TestSuit test;

    // Equations
    std::string mPolyCoefficient = "x^2 -10";
    std::string mZeroDerivativeCheck = "x^2 - x^3 -x^6 +x^7 +22x^3 -33x^6 +20";
    std::string mLogCoefficient = "log(x) - 10";
    std::string mTrigCoefficient = "cos(2*pi*x) + sin(2*pi*x)";
    std::string mExpCoefficient = "exp(x) - exp(-3x) + exp(9x)";
    std::string mNoDerivative = "10";

    std::vector<std::string> equations;
    equations.push_back(mPolyCoefficient);
    equations.push_back(mZeroDerivativeCheck);
    equations.push_back(mLogCoefficient);
    equations.push_back(mTrigCoefficient);
    equations.push_back(mExpCoefficient);
    equations.push_back(mNoDerivative);

    // Vectors
    const std::vector<double> mTestVector{3.0, -4.0, 10.0, -22.0, 10.0, -2.0};
    const std::vector<double> mNeverDerivative{10};
    const std::vector<double> mAnswerVector{3.16227766517654, 3.16227766517654,
                                            22026.4657948162, 0.8749999979997,
                                            -0.095561, -0.807004,};


    // Tests
    test.testChordSolver(0.0015, mAnswerVector.at(0), 3, 1000, false,
                         equations.at(0));
//    test.testNewtonSolver(0.0015, mAnswerVector.at(0), 3, 1000, false,
//                          equations.at(0));
//    test.testNewtonWithExprtkPoly(0.0015, mAnswerVector.at(1), 1.1, 1000,
//                                  false,
//                                  equations.at(0));
//    test.testNewtonWithExprtkLog(0.0015, mAnswerVector.at(2), 10.0, 1000,
//                                 false,
//                                 equations.at(2));
//    test.testNewtonWithExprtTrig(0.0015, mAnswerVector.at(3), 1, 1000, false,
//                                 equations.at(3));
//    test.testNewtonWithExprtExp(0.0015, mAnswerVector.at(4), 0.1, 1000, false,
//                                equations.at(4));
//    test.testNewtonWithExprtkPoly(0.00015, mAnswerVector.at(5), 0.0, 1000,
//                                  false,
//                                  equations.at(1));
    test.testExprtkJacobian();
    test.testDeterm();
    test.testSubtract();
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

void TestSuit::testAsssertion(const double tol, const double expected,
                              std::vector<double> testNewton,
                              std::string name) {
    double test = testNewton.at(0);

    if (isnan(test)) { testErrorCode(name); }
    if (isinf(test)) { testErrorCode(name); }
    if (fabs(expected - test) >= tol) { testErrorCode(name); }
}

void
TestSuit::testChordSolver(const double tol, const double expected,
                          const int x0, const int max, const bool verbose,
                          std::string &eq) {

    std::vector<std::string> equation = adaptor(eq);
    std::vector<double> value = adaptor(x0);
    Chord testChord(equation, value, tol, max, verbose);
    std::vector<double> *chordRealValue = new std::vector<double>;
    *chordRealValue = testChord.solve();
    testAsssertion(tol, expected, *chordRealValue, std::string("Chord"));

    delete (chordRealValue);

};

void
TestSuit::testNewtonSolver(const double tol, const double expected,
                           const double x0, const int max,
                           const bool verbose,
                           std::string &eq) {
    std::vector<std::string> equation = adaptor(eq);
    std::vector<double> value = adaptor(x0);
    Newton testNewton(equation, value, tol, max, verbose);
    std::vector<double> *newtonRealValue = new std::vector<double>;
    *newtonRealValue = testNewton.solve();

    testAsssertion(tol, expected, *newtonRealValue, std::string("PolyNewton"));

    delete (newtonRealValue);
}

void
TestSuit::testNewtonWithExprtkPoly(const double tol, const double expected,
                                   const double x0, const int max,
                                   const bool verbose,
                                   std::string &eq) {
    std::vector<std::string> equation = adaptor(eq);
    std::vector<double> value = adaptor(x0);
    std::vector<double> testNewton;
    Newton mNewton(equation, value, tol, max, verbose);
    testNewton = mNewton.solve();

    testAsssertion(tol, expected, testNewton, std::string("NewtonExprtkPoly"));
}

void
TestSuit::testNewtonWithExprtkLog(const double tol, const double expected,
                                  const double x0, const int max,
                                  const bool verbose,
                                  std::string &eq) {
    std::vector<double> testNewton;
    std::vector<std::string> equation = adaptor(eq);
    std::vector<double> value = adaptor(x0);
    Newton mNewton(equation, value, tol, max, verbose);
    testNewton = mNewton.solve();

    testAsssertion(tol, expected, testNewton, std::string("NewtonExprtkLog"));
}

void
TestSuit::testNewtonWithExprtTrig(const double tol, const double expected,
                                  const double x0, const int max,
                                  const bool verbose,
                                  std::string &eq) {
    std::vector<double> testNewton;
    std::vector<std::string> equation = adaptor(eq);
    std::vector<double> value = adaptor(x0);
    Newton mNewton(equation, value, tol, max, verbose);
    testNewton = mNewton.solve();

    testAsssertion(tol, expected, testNewton, std::string("NewtonExprtkTrig"));

}

void
TestSuit::testNewtonWithExprtExp(const double tol, const double expected,
                                 const double x0, const int max,
                                 const bool verbose,
                                 std::string &eq) {
    std::vector<double> testNewton;
    std::vector<std::string> equation = adaptor(eq);
    std::vector<double> value = adaptor(x0);
    Newton mNewton(equation, value, tol, max, verbose);
    testNewton = mNewton.solve();

    testAsssertion(tol, expected, testNewton, std::string("NewtonExprtkExp"));
}

void TestSuit::testExprtkJacobian() {
    std::vector<std::string> equations;
    Jacobian mEquations;
    equations.push_back("x^2 + y^4 - z^5 + 10");
    equations.push_back("x^3 + y^2 - z^5 - 10");
    equations.push_back("x^5 + y^3 - z^10 -100");
    std::vector<double> val1{2, 3, 4};
    std::vector<double> assertResults{4, 108, -1280,
                                      12, 6, -1280,
                                      80, 27, -2.62144e06};
    int var = 3;

    std::vector<std::vector<double>> returns = mEquations.exprtkJacobian(
            equations, val1,
            var);

    std::vector<std::vector<double> >::const_iterator returns_iterator;
    std::vector<double>::const_iterator returns_iterator2;

    iterateNestedVectors(assertResults, returns, returns_iterator,
                         returns_iterator2);
    std::vector<std::vector<double>> testEquation;
    testEquation = mEquations.exprtkJacobian(equations, val1, var);
}

void TestSuit::iterateNestedVectors(const std::vector<double> &assertResults,
                                    std::vector<std::vector<double>> &returns,
                                    std::vector<std::__1::vector<double>>::const_iterator returns_iterator,
                                    std::vector<double>::const_iterator &returns_iterator2) {
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
                           std::string("Jacobian"));
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

std::vector<std::string> TestSuit::adaptor(std::string &eq) {
    std::vector<std::string> equation;
    equation.push_back(eq);
    return equation;
}

std::vector<double> TestSuit::adaptor(double val) {
    std::vector<double> values;
    values.push_back(val);
    return values;
}

