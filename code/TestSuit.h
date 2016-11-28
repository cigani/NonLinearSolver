//
// Created by Michael Jaquier on 28.11.16.
//

#ifndef PCSC_NONLINEAR_SYSTEMS_PROJECT_TESTSUIT_H
#define PCSC_NONLINEAR_SYSTEMS_PROJECT_TESTSUIT_H

#include "Equations.hpp"
#include "Chord.hpp"
#include <assert.h>

class TestSuit: Chord {
public:
    void testChordSolver();
};

#endif //PCSC_NONLINEAR_SYSTEMS_PROJECT_TESTSUIT_H
