//
// Created by Michael Jaquier on 28.11.16.
//

#ifndef PCSC_NONLINEAR_SYSTEMS_PROJECT_TESTSUIT_H
#define PCSC_NONLINEAR_SYSTEMS_PROJECT_TESTSUIT_H

#include "Equations.hpp"
#include "Chord.hpp"
#include "Newton.hpp"
#include "FixedPoint.hpp"
#include <assert.h>
#include "exprtk.hpp"

class TestSuit: Chord {
public:
    void testChordSolver();
    void testNewtonSolver();
    void testFixedPointSolver();
    void testNewtonWithExprtkPoly();
    void testNewtonWithExprtkLog();
    void testNewtonWithExprtTrig();
    void testNewtonWithExprtExp();


};

#endif //PCSC_NONLINEAR_SYSTEMS_PROJECT_TESTSUIT_H
