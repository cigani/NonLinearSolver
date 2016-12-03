/* AUTHORS:
* Jaquier, Michael <michael.jaquier@epfl.ch>
* Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
*/

#include <cfloat>
#include "TestSuit.h"


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
    test.testChordSolver(0.0015, 0.66381, 3, 1000, false, mTestVector);
    test.testNewtonSolver(0.0015, 0.66381, 3, 1000, false, mTestVector);
    test.testNewtonWithExprtkPoly(0.0015, -3.16227766517654, 1.1, 1000, false,
                                  mPolyCoefficient);
    test.testNewtonWithExprtkLog(0.0015, 22026.4657948162, 10.0, 1000, false,
                                 mLogCoefficient);
    test.testNewtonWithExprtTrig(0.0015, -1.62499999969059, 1, 1000, false,
                                 mTrigCoefficient);
    test.testNewtonWithExprtExp(0.0015, -0.095561, 0.1, 1000, false,
                                mExpCoefficient);
    test.testNewtonWithExprtkPoly(0.0015, -0.807004, 0.0, 1000, false,
                                  mZeroDerivativeCheck);
    test.testExprtkJacobian();
};

void TestSuit::testAsssertion(const double tol, const double expected,
                              double testNewton, std::string name) const {
    if ((expected - testNewton) <= tol) {
        std::cout << name << " Success";
        printf("\n");
    } else {
        std::cout << name << " --- Failure --- ";
        printf("\n");
    }
}

void
TestSuit::testChordSolver(const double tol, const double expected,
                          const int x0, const int max, const bool verbose,
                          const std::vector<double> &vector) {
    Chord testChord;
    double *chordRealValue = new double;
    *chordRealValue = testChord.chordSolver(
            vector, x0, tol, max, verbose);

    testAsssertion(tol, expected, *chordRealValue, std::string("Chord"));

    delete (chordRealValue);

};

void
TestSuit::testNewtonSolver(const double tol, const double expected,
                           const double x0, const int max,
                           const bool verbose,
                           const std::vector<double> &vector) {
    Newton testNewton;
    double *newtonRealValue = new double;
    *newtonRealValue = testNewton.newtonSolver(
            vector, x0, tol, max, verbose);

    testAsssertion(tol, expected, *newtonRealValue, std::string("PolyNewton"));

    delete (newtonRealValue);
}

void
TestSuit::testNewtonWithExprtkPoly(const double tol, const double expected,
                                   const double x0, const int max,
                                   const bool verbose,
                                   std::string &coefficient) {
    double testNewton;
    Newton mNewton;
    testNewton = mNewton.newtonExprtkSolver(coefficient, x0,
                                            tol, max, verbose);

    testAsssertion(tol, expected, testNewton, std::string("NewtonExprtkPoly"));
}

void
TestSuit::testNewtonWithExprtkLog(const double tol, const double expected,
                                  const double x0, const int max,
                                  const bool verbose,
                                  std::string &coefficient) {
    double testNewton;
    Newton mNewton;
    testNewton = mNewton.newtonExprtkSolver(coefficient, x0,
                                            tol, max, verbose);

    testAsssertion(tol, expected, testNewton, std::string("NewtonExprtkLog"));
}

void
TestSuit::testNewtonWithExprtTrig(const double tol, const double expected,
                                  const double x0, const int max,
                                  const bool verbose,
                                  std::string &coefficient) {
    double testNewton;
    Newton mNewton;
    //TODO: Testing periodicity so we aren't so hamstrung by starting point
    testNewton = mNewton.newtonExprtkSolver(coefficient, x0,
                                            tol, max, verbose);

    testAsssertion(tol, expected, testNewton, std::string("NewtonExprtkTrig"));

}

void
TestSuit::testNewtonWithExprtExp(const double tol, const double expected,
                                 const double x0, const int max,
                                 const bool verbose,
                                 std::string &coefficient) {
    double testNewton;
    Newton mNewton;
    testNewton = mNewton.newtonExprtkSolver(coefficient, x0,
                                            tol, max, verbose);

    testAsssertion(tol, expected, testNewton, std::string("NewtonExprtkExp"));
}

void TestSuit::testExprtkJacobian() {
    std::vector<std::string> equations;
    equations.push_back("x^2 + y^4 - z^3 + 10");
    std::vector<std::vector<double> > values(0, std::vector<double>(3));
    std::vector<double> val1{2, 3, 4};
    values.push_back(val1);
    std::vector<double> assertResults{4, 108, -48, 75, 2, -1};
    int var = 3;

    std::vector<std::vector<double>> returns = Equations::exprtkJacobian(
            equations, values,
            var);

    std::vector<std::vector<double> >::iterator returns_iterator;
    std::vector<double>::iterator returns_iterator2;

    // Ridiculous PITA to print this stuff out. But this is probably the cleanest way
    int n = 0;
    for (returns_iterator = returns.begin();
         returns_iterator != returns.end(); ++returns_iterator) {
        for (returns_iterator2 = (*returns_iterator).begin();
             returns_iterator2 !=
             (*returns_iterator).end(); ++returns_iterator2) {
            testAsssertion(0.015, assertResults[n], *returns_iterator2,
                           std::string("Jacobian_1"));
            n++;


        }
    }

    equations.push_back("x^3 + y^2 - z^1 + 10");
    std::vector<double> val2{5, 1, 2};
    values.push_back(val2);
    std::vector<std::vector<double>> testEquation;
    Equations mEquations;
    testEquation = mEquations.exprtkJacobian(equations, values, var);

    std::vector<std::vector<double> >::iterator mReturnsIterator;
    std::vector<double>::iterator mReturnsIterator2;

    int k = 0;
    for (mReturnsIterator = testEquation.begin();
         mReturnsIterator != testEquation.end(); ++mReturnsIterator) {

        for (mReturnsIterator2 = (*mReturnsIterator).begin();
             mReturnsIterator2 !=
             (*mReturnsIterator).end(); ++mReturnsIterator2) {
            testAsssertion(0.015, assertResults[k], *mReturnsIterator2,
                           std::string("Jacobian_2"));
            k++;
        }
    }
}


