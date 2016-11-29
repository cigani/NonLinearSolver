//
// Created by Michael Jaquier on 28.11.16.
//

#include "TestSuit.h"


int main(int argc, char* argv[]) {
    TestSuit test;
    test.testChordSolver();
    test.testNewtonSolver();
    test.testNewtonWithExprtkPoly();
    test.testNewtonWithExprtkLog();
    test.testNewtonWithExprtTrig();
    test.testNewtonWithExprtExp();
};

void TestSuit::testChordSolver() {
    std::vector<double> testVector{3.0, -4.0, 10.0, -22.0, 10.0, -2.0};
    Chord testChord;
    double *realValue = new double;
    *realValue = testChord.chordSolver((const std::vector<double> &) testVector, 3, 0.001, 1000, false);
    assert((*realValue - 0.66381) < 0.0015);
    printf("Chord Success");

};

void TestSuit::testNewtonSolver() {
    std::vector<double> testVector{3.0, -4.0, 10.0, -22.0, 10.0, -2.0};
    Newton testNewton;
    double *realValue = new double;
    *realValue = testNewton.newtonSolver((const std::vector<double> &) testVector, 3, 0.001, 1000, false);
    assert((*realValue - 0.66381) < 0.0015);
    printf("Newton: Poly Success");
    printf("\n");
}

void TestSuit::testNewtonWithExprtkPoly() {
    double testNewton;
    std::string coefficient;
    coefficient = "x^2 -10";
    double expected = -3.16227766517654;
    //TODO: Refactor this into a constructor along with other parameters we can
    double tol = 0.0015;
    Newton mNewton;
    testNewton = mNewton.newtonExprtkSolver((std::string &) coefficient, 1.1,
                                            0.001, 1000, false);
    assert((expected - testNewton) < tol);
    printf("Newton: Exprtk Poly Success");
    printf("\n");
}

void TestSuit::testNewtonWithExprtkLog() {
    double testNewton;
    std::string coefficient;
    coefficient = "log(x) - 10";
    double expected = 22026.4657948162;
    double tol = 0.0015;
    Newton mNewton;
    testNewton = mNewton.newtonExprtkSolver((std::string &) coefficient, 10,
                                            0.001, 10000, false);
    assert((expected - testNewton) < tol);
    printf("Newton: Exprtk Log Success");
    printf("\n");
}

void TestSuit::testNewtonWithExprtTrig() {
    double testNewton;
    std::string coefficient;
    coefficient = "cos(2*pi*x) + sin(2*pi*x)";
    double expected = -1.62499999969059;
    double tol = 0.0015;
    Newton mNewton;
    //TODO: Testing periodicity so we aren't so hamstrung by starting point
    testNewton = mNewton.newtonExprtkSolver((std::string &) coefficient, 0.1,
                                            0.00001, 1000, false);
    assert((expected - testNewton) < tol);
    printf("Newton: Exprtk Trig Success");
    printf("\n");
}

void TestSuit::testNewtonWithExprtExp() {

    double testNewton;
    std::string coefficient;
    coefficient = "exp(x) - exp(-3x) + exp(9x)";
    double expected = -0.095561;
    double tol = 0.0015;
    Newton mNewton;
    testNewton = mNewton.newtonExprtkSolver((std::string &) coefficient, 0.1,
                                            0.00001, 1000, false);
    assert((expected - testNewton) < tol);
    printf("Newton: Exprtk Exp Success");
    printf("\n");
}

