/*
 * AUTHORS:
 * Jaquier, Michael <michael.jaquier@epfl.ch>
 * Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
 */

#include "NewtonSystem.hpp"
#include "Gauss.h"
#include "EquationTools.h"

NewtonSystem::NewtonSystem(const std::vector<Expression> &equation,
                           const std::vector<std::vector<Expression>> &derivative,
                           std::vector<double> initial,
                           double tolerance,
                           int maxIter,
                           bool verbosity)
        : NonlinearSolver(equation, initial, tolerance, maxIter, verbosity)
{
    jac = derivative;
    m = 1;
}

NewtonSystem::~NewtonSystem() {}

std::vector<double> NewtonSystem::solve() {
    std::vector<double> dx, fx0, dxyz, fxNeg;
    std::vector<std::vector<double>> dfx0;
    double prevNorm, nextNorm;
    Equations mEquation;
    EquationTools mEquationTools;
    Gauss mGauss;

    if (verbose) {
    	printVerbose(0, x0);
    }

    for (int i = 1; i <= nMax; i++) {
        prevNorm = mEquationTools.getNorm(x0);
        fx0 = mEquationTools.getSystemEquations(eq, x0);
        dfx0 = mJacobian.exprtkJacobian(eq, x0, (int) x0.size());
        fxNeg = mEquationTools.negateVector(fx0);
        mGauss.GaussPartialPivoting(dfx0, fxNeg);
        dxyz = mGauss.BackwardSolve(dfx0, fxNeg);
        dx = mEquationTools.addVectors(fx0, dxyz);
        x0 = dx;
        nextNorm = mEquationTools.getNorm(x0);
        //if (verbose) {
        //	printVerbose(i, x0);}
        if (fabs(prevNorm - nextNorm) < tol) {
            return x0;
        }
    }
    std::cout << "Maximum number of iterations exceeded" << std::endl;
    return x0;
}
