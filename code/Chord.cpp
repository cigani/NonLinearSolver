/*
 * Chord.cpp
 *
 * DESCRIPTION: Returns the root of an arbitrary nonlinear function using
 *              the secant method
 *
 * INPUTS:
 *          f        function whose root is to be determined
 *                   must take single argument of type double and return
 *                   single value of type double
 *          x0       one initial guess for location of root
 *                   type: double
 *          x1       another initial guess for location of root
 *                   type: double
 *          tol      absolute error convergence tolerance
 *                   type: double
 *          nMax     maximum number of iterations to achieve convergence
 *                   type: int
 *          verbose  print intermediate results (default false)
 *                   type: bool
 *
 * OUTPUT:
 *          root     approximate location of root
 *                   type: double
 *
 *
 * Created on: November 27, 2015
 *
 * AUTHORS:
 * Jaquier, Michael <michael.jaquier@epfl.ch>
 * Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
 */

#include <assert.h>
#include "Equations.hpp"
#include "Chord.hpp"

Chord::Chord() {}

Chord::~Chord() {}

double Chord::chordSolver(const std::vector<double>& coef,
                          double x0, double tol,
                          int nMax, bool verbose) {

    double xnew, dx , fx0, fx1;
    double x1 = x0 + 1;
    int i;

    if ( verbose ) {
        std::cout << std::setw(3) << 0 << "\t" << std::setw(20)
                  << x0 << std::setprecision(15) << std::endl;
        std::cout << std::setw(3) << 1 << "\t" << std::setw(20)
                  << x1 << std::setprecision(15) << std::endl;
    }

    fx0 = Equations::getPolyEquation(coef, x0);
    for ( i = 2; i <= nMax; i++ ) {
        fx1 = Equations::getPolyEquation(coef, x1);
        dx = fx1 * ( x1 - x0 ) / ( fx1 - fx0 );
        xnew = x1 - dx;
        if ( verbose ) {
            std::cout << std::setw(3) << i << "\t" << std::setw(20)
                      << xnew << std::setprecision(15) << std::endl;
        }
        if ( fabs(dx) < tol ) {
            return xnew;
        }
        else {
            x0 = x1;
            fx0 = fx1;
            x1 = xnew;
        }
    }
    std::cout << "Maximum number of iterations exceeded" << std::endl;
    return xnew;
}

double Chord::testChordSolver() {
    std::vector<double> testVector{3.0, -4.0, 10.0, -22.0, 10.0, -2.0};
    double *realValue = new double;
    *realValue = chordSolver((const std::vector<double> &) testVector, 3, 0.001, 1000, false);
    assert((*realValue - 0.66381) < 0.0015);
}