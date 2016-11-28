//
// Created by Michael Jaquier on 28.11.16.
//

#include "TestSuit.h"


int main(int argc, char* argv[]) {
    TestSuit test;
    test.testChordSolver();
};

void TestSuit::testChordSolver() {
    std::vector<double> testVector{3.0, -4.0, 10.0, -22.0, 10.0, -2.0};
    Chord testChord;
    double *realValue = new double;
    *realValue = testChord.chordSolver((const std::vector<double> &) testVector, 3, 0.001, 1000, false);
    assert((*realValue - 0.66381) < 0.0015);

};

void TestSuit::testNewtonSolver() {
    std::vector<double> testVector{3.0, -4.0, 10.0, -22.0, 10.0, -2.0};
    Newton testNewton;
    double *realValue = new double;
    *realValue = testNewton.newtonSolver((const std::vector<double> &) testVector, 3, 0.001, 1000, false);
    assert((*realValue - 0.66381) < 0.0015);
}

