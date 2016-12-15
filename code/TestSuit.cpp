#include "TestSuit.h"

/* AUTHORS:
* Jaquier, Michael <michael.jaquier@epfl.ch>
* Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
*/


std::vector<std::string> mErrors;
int main(int argc, char* argv[]) {
    TestSuit test;

    // Equations


    // Vector

    // Tests
    test.testChordSolver(3.0);

    test.testNewtonSolver(3.0);

    test.testNewtonWithExprtkPoly(3.0);

    test.testNewtonWithExprtkLog(10.0);

    test.testNewtonWithExprtTrig(1.0);

    test.testNewtonWithExprtExp(0.0);

    test.testBisectionWithExprtPoly(3.0);

    test.testAitkenWithExprtPoly(99.0);

    test.testDeterm();
    test.testSubtract();
    test.testSystemsLoading();
    test.testNonLinearSystems();
    test.testLinearSystem();

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

void TestSuit::testChordSolver(const int x0) {

    Chord testChord(equations.at(0), x0, tolerance, maxIter, verbosity);
    double *chordRealValue = new double;
    *chordRealValue = testChord.solve();
    testAsssertion(tolerance, expectedresult.at(0), *chordRealValue, std::string("Chord"));

    delete (chordRealValue);

};

void TestSuit::testNewtonSolver(const double x0) {
    Newton testNewton(equations.at(0), derivatives.at(0), x0, tolerance, maxIter, verbosity, 1);

    double *newtonRealValue = new double;
    *newtonRealValue = testNewton.solve();

    testAsssertion(tolerance, expectedresult.at(0), *newtonRealValue, std::string("PolyNewton"));

    delete (newtonRealValue);
}

void TestSuit::testNewtonWithExprtkPoly(const double x0) {
    double testNewton;
    Newton mNewton(equations.at(1), derivatives.at(1), x0, tolerance, maxIter, verbosity, 1);

    testNewton = mNewton.solve();

    testAsssertion(tolerance, expectedresult.at(1), testNewton, std::string("ExPolu"));
}

void TestSuit::testNewtonWithExprtkLog(const double x0) {
    double testNewton;

    Newton mNewton(equations.at(2), derivatives.at(2), x0, tolerance, maxIter, verbosity, 1);

    testNewton = mNewton.solve();

    testAsssertion(tolerance, expectedresult.at(2), testNewton, std::string("NewtonExprtkLog"));
}

void TestSuit::testNewtonWithExprtTrig(const double x0) {
    double testNewton;

    Newton mNewton(equations.at(3), derivatives.at(3), x0, tolerance, maxIter, verbosity, 1);
    testNewton = mNewton.solve();

    testAsssertion(tolerance, expectedresult.at(3), testNewton, std::string("NewtonExprtkTrig"));

}

void TestSuit::testNewtonWithExprtExp(const double x0) {
    double testNewton;

    Newton mNewton(equations.at(4), derivatives.at(4), x0, tolerance, maxIter, verbosity, 1);
    testNewton = mNewton.solve();

    testAsssertion(tolerance, expectedresult.at(4), testNewton, std::string("NewtonExprtkExp"));
}

void TestSuit::testBisectionWithExprtPoly(const double x0) {
    double testBisection;
    Bisection mBisection(equations.at(0), x0, tolerance, maxIter, verbosity, 0, 100);
    testBisection = mBisection.solve();

    testAsssertion(tolerance, expectedresult.at(0), testBisection, std::string("Bisection"));
}


void TestSuit::testAitkenWithExprtPoly(const double x0) {
    double testAitken;
    Aitken mAitken(equations.at(3), x0, tolerance, maxIter, verbosity);
    testAitken = mAitken.solve();

    testAsssertion(tolerance, 1.0, testAitken, std::string("Aitken"));
}

void TestSuit::testSystemsLoading() {
    ExpressionSystem expressionSystem("_equations.txt");
    ExpressionSystem derivativeSystem("_derivative.txt");
    std::vector<double> expectedDerivativeValue{1, 0.333333, -1, 2};
    std::vector<std::string> expectedDerivativeFunction{"1", "1/3", "-1", "2"};
    std::vector<std::string> expectedEquationFunction{"x+y/3", "-x+2y"};

    Expression mExp = expressionSystem.getEquation(0, 0);
    Expression mExp2 = expressionSystem.getEquation(1, 0);
    std::vector<std::string> actualEquation{mExp.getEquation(),
                                            mExp2.getEquation()};

    Expression mdExp = derivativeSystem.getEquation(0, 0);
    Expression mdExp2 = derivativeSystem.getEquation(0, 1);
    Expression mdExp3 = derivativeSystem.getEquation(1, 0);
    Expression mdExp4 = derivativeSystem.getEquation(1, 1);
    std::vector<std::string> actualDerivative{mdExp.getEquation(),
                                              mdExp2.getEquation(),
                                              mdExp3.getEquation(),
                                              mdExp4.getEquation()};

    std::vector<double> value{3, 2};
    std::vector<double> evaluatedDer{mdExp.evaluate(value),
                                     mdExp2.evaluate(value),
                                     mdExp3.evaluate(value),
                                     mdExp4.evaluate(value)};


    testAsssertion(expectedEquationFunction, actualEquation,
                   std::string("Test Systems"));
    testAsssertion(expectedDerivativeFunction, actualDerivative,
                   std::string("Derivative Systems"));
    testAsssertion(expectedDerivativeValue, evaluatedDer,
                   std::string("Derivative Return"));
    
}

void TestSuit::testLinearSystem() {
    ExpressionSystem expressionSystem("_equations.txt");
    ExpressionSystem derivativeSystem("_derivative.txt");
    std::vector<double> values{3, 2};
    std::vector<double> expectedArray{0.0, 0.0};
    std::vector<double> resultNewton;
    NewtonSystem newtonSystem(expressionSystem, derivativeSystem, values,
                              tolerance, maxIter, verbosity, 1);

    resultNewton = newtonSystem.solve();

    testAsssertion(expectedArray, resultNewton,
                   std::__1::string("NewtonSystem"));
}

void TestSuit::testNonLinearSystems() {
    std::__1::vector<double> values{10, 6.1};
    std::vector<double> expected{2.44710116609237, 1.83532587456419};
    std::vector<double> resultNewton;

    ExpressionSystem expressionSystem2("_equationNonLinear");
    ExpressionSystem derivativeSystem2("_derivativeNonLinear");

    NewtonSystem newtonSystem2(expressionSystem2, derivativeSystem2, values,
                               tolerance, maxIter, verbosity, 1);
    resultNewton = newtonSystem2.solve();

    testAsssertion(expected, resultNewton, std::string("NonLinear System"));
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

