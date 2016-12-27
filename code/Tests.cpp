#include "Tests.h"

/* AUTHORS:
* Jaquier, Michael <michael.jaquier@epfl.ch>
* Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
*/



int main(int argc, char* argv[]) {
    TestSuit test;

    // Tests
    test.testChordSolver(3.0);
    test.testNewtonSolver(3.0);
    test.testNewtonWithExprtkPoly(3.0);
    test.testNewtonWithExprtkLog(10.0);
    test.testNewtonWithExprtTrig(1.0);
    test.testNewtonWithExprtExp(0.0);
    test.testNewtonSolverExprtkZeroDerivative(0.0);
    test.testBisectionWithExprtPoly(3.0);
    test.testAitkenWithExprtPoly(99.0);
    test.testAitkenWithExprtZeroDerivative(99.0);
    test.testFixedPointWithExprtPoly(99.0);
    test.testDeterm();
    test.testSubtract();
    test.testSystemsLoading();
    test.testNonLinearSystems();
    test.testLinearSystem();
    test.testSystemsJacobian();

    // Error Logging
    test.iterateVectors(test.mErrors);

    return 0;

};

void TestSuit::testAsssertion(const double expected, const double &result,
                              std::string name) {

    double test = result;
    if (std::isnan(test)) { testErrorCode(name); }
    if (std::isinf(test)) { testErrorCode(name); }
    if (fabs(expected - test) >= tolerance) { testErrorCode(name); }
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
        if (fabs(evaluate) > tolerance) {
            testErrorCode(name);
            std::cout << "Expected: " << expected[i] << " | "
                      << "Actual: " << actual[i] << "\n";
        }
    }
}

void TestSuit::testChordSolver(const double x0) {

    Chord testChord(equations.at(0), x0, tolerance, maxIter, verbosity);
    double *chordRealValue = new double;
    *chordRealValue = testChord.solve();
    testAsssertion(expectedresult.at(0), *chordRealValue,
                   std::string("Chord"));
    delete (chordRealValue);

};

void TestSuit::testNewtonSolver(const double x0) {
    Newton testNewton(equations.at(0), derivatives.at(0), x0, tolerance, maxIter, verbosity);
    double *newtonRealValue = new double;
    *newtonRealValue = testNewton.solve();
    testAsssertion(expectedresult.at(0), *newtonRealValue,
                   std::string("PolyNewton"));
    delete (newtonRealValue);

    Newton testNewtonModified(equations.at(6), derivatives.at(6), x0,
                              tolerance, maxIter, verbosity, 2);
    double *testNewtonModifiedValue = new double;
    *testNewtonModifiedValue = testNewtonModified.solve();
    testAsssertion(expectedresult.at(6), *testNewtonModifiedValue,
                   std::string("PolyNewtonModified"));
    delete testNewtonModifiedValue;
}

void TestSuit::testNewtonSolverExprtkZeroDerivative(const double x0) {
    Newton testNewton(equations.at(2), derivatives.at(2), x0, tolerance,
                      maxIter, verbosity);
    double *newtonRealValue = new double;
    *newtonRealValue = testNewton.solve();
    testAsssertion(expectedresult.at(2), *newtonRealValue,
                   std::string("PolyNewton"));
    delete (newtonRealValue);
}

void TestSuit::testNewtonWithExprtkPoly(const double x0) {
    double testNewton;
    Newton mNewton(equations.at(0), derivatives.at(0), x0, tolerance, maxIter,
                   verbosity);
    testNewton = mNewton.solve();
    testAsssertion(expectedresult.at(0), testNewton, std::string("ExPoly"));
}

void TestSuit::testNewtonWithExprtkLog(const double x0) {
    double testNewton;
    Newton mNewton(equations.at(2), derivatives.at(2), x0, tolerance, maxIter, verbosity);
    testNewton = mNewton.solve();
    testAsssertion(expectedresult.at(2), testNewton,
                   std::string("NewtonExprtkLog"));
}

void TestSuit::testNewtonWithExprtTrig(const double x0) {
    double testNewton;
    Newton mNewton(equations.at(3), derivatives.at(3), x0, tolerance, maxIter, verbosity);
    testNewton = mNewton.solve();
    testAsssertion(expectedresult.at(3), testNewton,
                   std::string("NewtonExprtkTrig"));

}

void TestSuit::testNewtonWithExprtExp(const double x0) {
    double testNewton;
    Newton mNewton(equations.at(4), derivatives.at(4), x0, tolerance, maxIter, verbosity);
    testNewton = mNewton.solve();
    testAsssertion(expectedresult.at(4), testNewton,
                   std::string("NewtonExprtkExp"));
}

void TestSuit::testBisectionWithExprtPoly(const double x0) {
    double testBisection;
    Bisection mBisection(equations.at(0), x0, tolerance, maxIter, verbosity, 0, 100);
    testBisection = mBisection.solve();
    testAsssertion(expectedresult.at(0), testBisection,
                   std::string("Bisection"));
}


void TestSuit::testAitkenWithExprtPoly(const double x0) {
    double testAitken;
    Aitken mAitken(equations.at(3), x0, tolerance, maxIter, verbosity);
    testAitken = mAitken.solve();
    testAsssertion(1.0, testAitken, std::string("Aitken"));
}

void TestSuit::testAitkenWithExprtZeroDerivative(const double x0) {
    double testAitken;
    Aitken mAitken(equations.at(2), x0, tolerance, maxIter, verbosity);
    testAitken = mAitken.solve();
    testAsssertion(99.0, testAitken, std::string("Aitken"));
}

void TestSuit::testFixedPointWithExprtPoly(const double x0) {
    double testFixedPoint;
    FixedPoint mFixedPoint(equations.at(3), x0, tolerance, maxIter, verbosity);
    testFixedPoint = mFixedPoint.solve();
    testAsssertion(1.0, testFixedPoint, std::string("Aitken"));
}

void TestSuit::testSystemsLoading() {
    ExpressionSystem expressionSystem("testfiles/_equations.txt");
    ExpressionSystem derivativeSystem("testfiles/_derivative.txt");
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
    std::vector<double> evaluatedDerivative{mdExp.evaluate(value),
                                            mdExp2.evaluate(value),
                                            mdExp3.evaluate(value),
                                            mdExp4.evaluate(value)};


    testAsssertion(expectedEquationFunction, actualEquation,
                   std::string("Test Systems"));
    testAsssertion(expectedDerivativeFunction, actualDerivative,
                   std::string("Derivative Systems"));
    testAsssertion(expectedDerivativeValue, evaluatedDerivative,
                   std::string("Derivative Return"));

}

void TestSuit::testLinearSystem() {
    ExpressionSystem expressionSystem("testfiles/_equations.txt");
    ExpressionSystem derivativeSystem("testfiles/_derivative.txt");
    std::vector<double> values{3, 2};
    std::vector<double> expected{0.0, 0.0};
    std::vector<double> result;
    NewtonSystem newtonSystem(expressionSystem, derivativeSystem, values,
                              tolerance, maxIter, verbosity, 1);
    result = newtonSystem.solve();
    testAsssertion(expected, result, std::__1::string("NewtonSystem"));
}

void TestSuit::testNonLinearSystems() {
    ExpressionSystem expressionSystem2("testfiles/_equationNonLinear");
    ExpressionSystem derivativeSystem2("testfiles/_derivativeNonLinear");
    std::__1::vector<double> values{270.8, 270.1};
    std::vector<double> expected{2.44710116609237, 1.83532587456419};
    std::vector<double> expectedModified{0.0, 0.0};
    std::vector<double> result, modifiedResult;

    NewtonSystem newtonSystem(expressionSystem2, derivativeSystem2, values,
                              tolerance, maxIter, verbosity, 1);
    NewtonSystem newtonSystemModified(expressionSystem2, derivativeSystem2,
                                      values,
                                      tolerance, maxIter, verbosity, 4);

    result = newtonSystem.solve();
    modifiedResult = newtonSystemModified.solve();

    testAsssertion(expected, result, std::string("NonLinear System"));
    // With a high mod it skips to the next zero of the function.
    testAsssertion(expectedModified, modifiedResult,
                   std::string("NonLinear System Modified"));

}

void TestSuit::testSystemsJacobian() {
    ExpressionSystem expressionSystem2("testfiles/_equationNonLinear");
    ExpressionSystem derivativeSystem2("testfiles/_derivativeNonLinear");
    std::vector<double> values{1, 1};
    auto numericjacobian = expressionSystem2.jacobian(values);
    auto truejacobian = derivativeSystem2.evaluate(values);
    std::vector<double> vectornumericjacobian = convert.convertMatrix2Vector(
            numericjacobian);
    std::vector<double> vectortruejacobian = convert.convertMatrix2Vector(
            truejacobian);
    testAsssertion(vectortruejacobian, vectornumericjacobian,
                   std::string("Jacobian Systems"));

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
    testAsssertion(-20, det, std::string("Determinant"));
}

void TestSuit::testSubtract() {
    std::vector<double> v1{1, 2, 3, 4};
    std::vector<double> v2{4, 3, 2, 1};
    std::vector<double> assertVector{-3, -1, 1, 3};
    EquationTools mEquations;
    std::vector<double> testVector = mEquations.subtractVectors(v1, v2);
    for (int n = 0; n != v1.size(); n++) {
        testAsssertion(assertVector[n], testVector[n],
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

