/* AUTHORS:
* Jaquier, Michael <michael.jaquier@epfl.ch>
* Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
*/

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
    void testChordSolver(const double tol, const double expected,
                         const int x0, const int max,
                         const bool verbose);

    void testNewtonSolver(const double tol, const double expected,
                          const double x0, const int max,
                          const bool verbose);
    void testFixedPointSolver();

    void testNewtonWithExprtkPoly(const double tol, const double expected,
                                  const double x0, const int max,
                                  const bool verbose);

    void testNewtonWithExprtTrig(const double tol, const double expected,
                                 const double x0, const int max,
                                 const bool verbose);

    void testNewtonWithExprtExp(const double tol, const double expected,
                                const double x0, const int max,
                                const bool verbose);


    void testNewtonWithExprtkLog(const double tol, const double expected,
                                 const double x0, const int max,
                                 const bool verbose);
};

#endif //PCSC_NONLINEAR_SYSTEMS_PROJECT_TESTSUIT_H
