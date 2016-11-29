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
    void testChordSolver(const double tol, const double expected);

    void testNewtonSolver(const double tol, const double expected);
    void testFixedPointSolver();

    void testNewtonWithExprtkPoly(const double tol, const double expected);

    void testNewtonWithExprtkLog(const double tol, const double expected);

    void testNewtonWithExprtTrig(const double tol, const double expected);

    void testNewtonWithExprtExp(const double tol, const double expected);


};

#endif //PCSC_NONLINEAR_SYSTEMS_PROJECT_TESTSUIT_H
