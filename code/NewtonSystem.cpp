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
        std::vector<std::vector<double>> fx0Pure = system.evaluate(v0);
        iteratate(fx0, std::string("fx0"));
        iteratate(fx0Pure, std::string("fx0Pure"));
        //printVerbose(0, fx0);
        dfx0 = jac.evaluate(v0);
        iteratate(dfx0, std::string("dfx0"));
        fxNeg = mEquationTools.negateVector(fx0);
        iteratate(fxNeg, std::string("fxNeg"));
        mGauss.GaussPartialPivoting(dfx0, fxNeg);
        dxyz = mGauss.BackwardSolve(dfx0, fxNeg);
        iteratate(dxyz, std::string("dxyz"));
        dx = mEquationTools.addVectors(fx0, dxyz);
        iteratate(dx, std::string("dx"));
        v0 = dx;

        nextNorm = mEquationTools.getNorm(v0);

        if (verbose) { printVerbose(i, v0); }

        if (fabs(prevNorm - nextNorm) < tol) { return v0; }
    }

    std::cout << "Maximum number of iterations exceeded" << std::endl;
    return v0;
}

void
NewtonSystem::iteratate(std::vector<double> &fxNeg, std::string name) const {
    std::__1::vector<double>::const_iterator returns_iterator;

    for (returns_iterator = fxNeg.begin(); returns_iterator != fxNeg.end();
         ++returns_iterator) {
        std::__1::cout << name << " | " << *returns_iterator << "\n";
    }
}

void NewtonSystem::iteratate(std::vector<std::vector<double>> &dfx0,
                             std::string name) const {
    std::__1::vector<std::vector<double>>::const_iterator returns_iterator;
    std::__1::vector<double>::const_iterator returns_iterator2;
    for (returns_iterator = dfx0.begin(); returns_iterator != dfx0.end();
         ++returns_iterator) {
        for (returns_iterator2 = (*returns_iterator).begin();
             returns_iterator2 != (*returns_iterator).end();
             ++returns_iterator2) {
            std::__1::cout << name << " | " << *returns_iterator2 << "\n";
        }
    }
}
