/*
 * AUTHORS:
 * Jaquier, Michael <michael.jaquier@epfl.ch>
 * Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
 */

#include "NewtonSystem.hpp"
#include "Gauss.h"
#include "EquationTools.h"

NewtonSystem::NewtonSystem(ExpressionSystem &sys,
                           ExpressionSystem &jacobian,
                           std::vector<double> initial,
                           double tolerance,
                           int maxIter,
                           bool verbosity)
        : NonlinearSystemsSolver(sys, initial, tolerance, maxIter, verbosity)
{
    jac = jacobian;
    m = 1;
}

NewtonSystem::~NewtonSystem() {}

std::vector<double> NewtonSystem::solve() {

    std::vector<double> dx, fx0, dxyz, fxNeg;
    std::vector<std::vector<double>> dfx0;
    double prevNorm, nextNorm;

    EquationTools mEquationTools;
    Gauss mGauss;

    if (verbose) { printVerbose(0, v0); }

    for (int i = 1; i <= nMax; i++) {
        prevNorm = mEquationTools.getNorm(v0);

        fx0 = system.evaluate(v0).at(0);
        dfx0 = jac.evaluate(v0);

        fxNeg = mEquationTools.negateVector(fx0);
        mGauss.GaussPartialPivoting(dfx0, fxNeg);

        dxyz = mGauss.BackwardSolve(dfx0, fxNeg);
        dx = mEquationTools.addVectors(fx0, dxyz);
        v0 = dx;

        nextNorm = mEquationTools.getNorm(v0);

        if (verbose) { printVerbose(i, v0); }

        if (fabs(prevNorm - nextNorm) < tol) { return v0; }
    }

    std::cout << "Maximum number of iterations exceeded" << std::endl;
    return v0;
}
