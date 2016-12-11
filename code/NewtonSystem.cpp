/*
 * AUTHORS:
 * Jaquier, Michael <michael.jaquier@epfl.ch>
 * Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
 */

#include "NewtonSystem.hpp"
#include "Gauss.h"
#include "EquationTools.h"

NewtonSystem::NewtonSystem(ExpressionSystem &equation,
                           ExpressionSystem &derivative,
                           std::vector<double> initial,
                           double tolerance,
                           int maxIter,
                           bool verbosity)
        : NonlinearSystemsSolver(equation, initial, tolerance, maxIter, verbosity)
{
    jac = derivative;
    m = 1;
}

NewtonSystem::~NewtonSystem() {}

std::vector<double> NewtonSystem::solve() {
    std::vector<double> dx, fx0, dxyz, fxNeg;
    std::vector<std::vector<double>> dfx0;
    double prevNorm, nextNorm;
    EquationTools mEquationTools;
    Gauss mGauss;

//    if (verbose) {
//    	printVerbose(0, x0);
//    }

    for (int i = 1; i <= nMax; i++) {
        prevNorm = mEquationTools.getNorm(x0);
        fx0 = eq.evaluate(x0).at(0);
        dfx0 = jac.evaluate(x0);
        fxNeg = mEquationTools.negateVector(fx0);
        mGauss.GaussPartialPivoting(dfx0, fxNeg);
        dxyz = mGauss.BackwardSolve(dfx0, fxNeg);
        dx = mEquationTools.addVectors(fx0, dxyz);
        x0 = dx;
        nextNorm = mEquationTools.getNorm(x0);
        //if (verbose) {
        //	printVerbose(i, x0);
        // }
        if (fabs(prevNorm - nextNorm) < tol) {
            return x0;
        }
    }
    std::cout << "Maximum number of iterations exceeded" << std::endl;
    return x0;
}
