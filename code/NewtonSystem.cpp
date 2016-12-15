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
                           std::vector<double> &initial,
                           double tolerance,
                           int maxIter,
                           bool verbosity,
                           int mod)
        : NonlinearSystemsSolver(sys, initial, tolerance, maxIter, verbosity)
{
    jac = jacobian;
    m = mod;
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
        std::vector<std::vector<double>> matrixfx0 = system.evaluate(v0);

        fx0 = convertMatrix2Vector(matrixfx0);
        dfx0 = jac.evaluate(v0);
        fxNeg = mEquationTools.negateVector(fx0);
        dxyz = mGauss.solveSystem(dfx0, fxNeg, system.getColumns());

        if (m!=1) {
            applyModifier(dxyz);
        }

        dx = mEquationTools.addVectors(v0, dxyz);

        v0 = dx;

        nextNorm = mEquationTools.getNorm(v0);

        if (verbose) { printVerbose(i, v0); }

        if (fabs(prevNorm - nextNorm) < tol) { return v0; }
    }

    std::cout << "Maximum number of iterations exceeded" << std::endl;
    return v0;
}

std::vector<double> NewtonSystem::convertMatrix2Vector(const std::vector<std::vector<double>> &fx0) const {
    std::vector<std::vector<double>>::const_iterator it;
    std::vector<double>::const_iterator it2;
    std::vector<double> returns;
    for (it = fx0.begin(); it != fx0.end(); ++it) {
        for (it2 = (*it).begin();
             it2 != (*it).end(); ++it2) { returns.push_back(*it2); }
        }
    return returns;
}

void NewtonSystem::applyModifier(std::vector<double> &dxyz) {
    std::vector<double>::iterator it;
    for (it = dxyz.begin(); it != dxyz.end(); ++it) {
        *it = (double)m * (*it);
    }
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
