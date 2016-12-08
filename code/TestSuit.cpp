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

    // Vectors
    const std::vector<double> mTestVector{3.0, -4.0, 10.0, -22.0, 10.0, -2.0};
    const std::vector<double> mNeverDerivative{10};


    // Tests
    test.testChordSolver(0.0015, 3.16227766517654, 3, 1000, false,
                         mPolyCoefficient);
    test.testNewtonSolver(0.0015, 3.16227766517654, 3, 1000, false,
                          mPolyCoefficient);
    test.testNewtonWithExprtkPoly(0.0015, 3.16227766517654, 1.1, 1000, false,
                                  mPolyCoefficient);
    test.testNewtonWithExprtkLog(0.0015, 22026.4657948162, 10.0, 1000, false,
                                 mLogCoefficient);
    test.testNewtonWithExprtTrig(0.0015, 0.8749999979997, 1, 1000, false,
                                 mTrigCoefficient);
    test.testNewtonWithExprtExp(0.0015, -0.095561, 0.1, 1000, false,
                                mExpCoefficient);
    test.testNewtonWithExprtkPoly(0.00015, -0.807004, 0.0, 1000, false,
                                  mZeroDerivativeCheck);
    test.testExprtkJacobian();
    test.testDeterm();
    test.testSubtract();
    // Error Logging
    test.iterateVectors(mErrors);

};

void TestSuit::testAsssertion(const double tol, const double expected,
                              double testNewton, std::string name) {
    if (isnan(testNewton)) { testErrorCode(name); }
    if (isinf(testNewton)) { testErrorCode(name); }
    if (fabs(expected - testNewton) >= tol) { testErrorCode(name); }
}

void
TestSuit::testChordSolver(const double tol, const double expected,
                          const int x0, const int max, const bool verbose,
                          std::string &eq) {

    Chord testChord(eq, x0, tol, max, verbose);
    double *chordRealValue = new double;
    *chordRealValue = testChord.solve();
    testAsssertion(tol, expected, *chordRealValue, std::string("Chord"));

    delete (chordRealValue);

};

void
TestSuit::testNewtonSolver(const double tol, const double expected,
                           const double x0, const int max,
                           const bool verbose,
                           std::string &eq) {
    Newton testNewton(eq, x0, tol, max, verbose);
    double *newtonRealValue = new double;
    *newtonRealValue = testNewton.solve();

    testAsssertion(tol, expected, *newtonRealValue, std::string("PolyNewton"));

    delete (newtonRealValue);
}

void
TestSuit::testNewtonWithExprtkPoly(const double tol, const double expected,
                                   const double x0, const int max,
                                   const bool verbose,
                                   std::string &eq) {
    double testNewton;
    Newton mNewton(eq, x0, tol, max, verbose);
    testNewton = mNewton.solve();

    testAsssertion(tol, expected, testNewton, std::string("NewtonExprtkPoly"));
}

void
TestSuit::testNewtonWithExprtkLog(const double tol, const double expected,
                                  const double x0, const int max,
                                  const bool verbose,
                                  std::string &eq) {
    double testNewton;
    Newton mNewton(eq, x0, tol, max, verbose);
    testNewton = mNewton.solve();

    testAsssertion(tol, expected, testNewton, std::string("NewtonExprtkLog"));
}

void
TestSuit::testNewtonWithExprtTrig(const double tol, const double expected,
                                  const double x0, const int max,
                                  const bool verbose,
                                  std::string &eq) {
    double testNewton;
    Newton mNewton(eq, x0, tol, max, verbose);
    testNewton = mNewton.solve();

    testAsssertion(tol, expected, testNewton, std::string("NewtonExprtkTrig"));

}

void
TestSuit::testNewtonWithExprtExp(const double tol, const double expected,
                                 const double x0, const int max,
                                 const bool verbose,
                                 std::string &eq) {
    double testNewton;
    Newton mNewton(eq, x0, tol, max, verbose);
    testNewton = mNewton.solve();

    testAsssertion(tol, expected, testNewton, std::string("NewtonExprtkExp"));
}

void TestSuit::testExprtkJacobian() {
    std::vector<std::string> equations;
    Jacobian mEquations;
    equations.push_back("x^2 + y^4 - z^3 + 10");
    std::vector<std::vector<double> > values(0, std::vector<double>(3));
    std::vector<double> val1{2, 3, 4};
    values.push_back(val1);
    std::vector<double> assertResults{4, 108, -48, 75, 2, -1};
    int var = 3;

    std::vector<std::vector<double>> returns = mEquations.exprtkJacobian(
            equations, values,
            var);

    std::vector<std::vector<double> >::const_iterator returns_iterator;
    std::vector<double>::const_iterator returns_iterator2;

    iterateNestedVectors(assertResults, returns, returns_iterator,
                         returns_iterator2);

    equations.push_back("x^3 + y^2 - z^1 + 10");
    std::vector<double> val2{5, 1, 2};
    values.push_back(val2);
    std::vector<std::vector<double>> testEquation;
    testEquation = mEquations.exprtkJacobian(equations, values, var);

    std::vector<std::vector<double> >::const_iterator mReturnsIterator;
    std::vector<double>::const_iterator mReturnsIterator2;

    iterateNestedVectors(assertResults, testEquation, mReturnsIterator,
                         mReturnsIterator2);
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
