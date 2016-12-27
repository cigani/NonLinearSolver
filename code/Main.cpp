/*                                                                                       
 * Main.cpp
 *
 * DESCRIPTION: Handles all classes related to methods for non linear equations.
 *
 * Created on: November 26, 2015
 * 
 * AUTHORS: 
 * Jaquier, Michael <michael.jaquier@epfl.ch>
 * Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "string.hpp"
#include "FixedPoint.hpp"
#include "Chord.hpp"
#include "Newton.hpp"
#include "Aitken.hpp"
#include "Bisection.hpp"
#include "Helper.hpp"
#include "ExpressionSystem.hpp"
#include "NewtonSystem.hpp"
#include "InitialVector.hpp"
//#include "Eigen/Eigen"

#ifndef NDEBUG
#define mAssert(condition, message) \
        do { \
            if (! (condition)) { \
                std::cerr << message << std::endl; \
                std::exit(1); \
            } \
        } while (false)
#else
#define mAssert(condition, message) do { } while (false)
#endif

int main(int argc, char *argv[]) {

	Helper help(argv[0]);

    if (argc < 3) {
    	help.show_usage();
        return 1;
    }

    std::string mMethod;
    Expression mExpression;
    Expression mDerivative;
    ExpressionSystem mSystem;
    ExpressionSystem mJacobian;
    InitialVector mInitialVector;
    double x0 = 1.0;
    int nMax = 1000;
    double tol = 0.001;
    bool verbose = false;
    double lowerBound = -1.0;
    double upperBound = 1.0;
    int mod = 1;

    bool systemFlag = false;
    bool jacobianFlag = false;
    bool vectorFlag = false;

    // Parse the command line arguments for flags and values
    for (int i = 1; i < argc; i++) {
        if (i + 1 != argc) {
            if ((strcmp(argv[i], "-m") == 0) ||
                (strcmp(argv[i], "--method") == 0)) {
                // Method declaration
                if (boost::iequals(argv[i + 1], "aitken")) {
                    mMethod = argv[i + 1];
                } else if (boost::iequals(argv[i + 1], "bisection")) {
                    mMethod = argv[i + 1];
                } else if (boost::iequals(argv[i + 1], "chord")) {
                    mMethod = argv[i + 1];
                } else if (boost::iequals(argv[i + 1], "fixedpoint")) {
                    mMethod = argv[i + 1];
                } else if (boost::iequals(argv[i + 1], "newton")) {
                    mMethod = argv[i + 1];
                } else {
                    std::cout << std::endl << "ERROR: Unknown method provided"
                              << std::endl;
                    help.show_methods();
                    return 1;
                }
            } else if (strcmp(argv[i], "-e") == 0) {
                // Mathematical Expression
                Expression mExpression(argv[i + 1]);
            } else if (strcmp(argv[i], "-d") == 0) {
                // Derivative Expression
                Expression mDerivative(argv[i + 1]);
            } else if (strcmp(argv[i], "-xi") == 0) {
                // Initial Value
                x0 = std::stod(argv[i + 1]);
            } else if (strcmp(argv[i], "-f") == 0) {
                // System of Equations
                mSystem = ExpressionSystem(argv[i + 1]);
                systemFlag = true;
            } else if (strcmp(argv[i], "-j") == 0) {
                // Jacobian
                mJacobian = ExpressionSystem(argv[i + 1]);
                jacobianFlag = true;
            } else if (strcmp(argv[i], "-xv") == 0) {
                // Initial Value
                mInitialVector = InitialVector(argv[i + 1]);
                vectorFlag = true;
            } else if (strcmp(argv[i], "-nmax") == 0) {
                // Maximum number of iterations. Default 1000
                nMax = std::stoi(argv[i + 1]);
            } else if (strcmp(argv[i], "-t") == 0) {
                // Error tolerance.  Default 0.001.
                tol = std::stod(argv[i + 1]);
            } else if (strcmp(argv[i], "-v") == 0) {
                // Verbose setting.  Default false.
                std::istringstream(argv[i + 1]) >> std::boolalpha >> verbose;
                // Doesn't work. Weird.
                // verbose = true;
            } else if (strcmp(argv[i], "-l") == 0) {
                // Lower bound of the search interval
                lowerBound = std::stod(argv[i + 1]);
            } else if (strcmp(argv[i], "-u") == 0) {
                // Upper bound of the search interval
                upperBound = std::stod(argv[i + 1]);
            } else if (strcmp(argv[i], "-mod") == 0) {
                // Newton modifier
                mod = std::stoi(argv[i + 1]);
            } else if ((strcmp(argv[i], "-h") == 0) ||
                       (strcmp(argv[i], "--help") == 0)) {
                // Print help dialog
                help.show_usage();
            } else {
                continue;
            }
        }
    }

    if (!systemFlag) {
        mAssert(mExpression.getEquation() != "0",
                "ERROR: No mathematical expression provided");
    } else {
        mAssert(boost::iequals(mMethod, "newton"),
                "ERROR: Only the Newton method is available for evaluating systems of equations.");
    }

    if (boost::iequals(mMethod, "aitken")) {
        std::cout << std::endl << "AITKEN METHOD" << std::endl;

        Aitken aitken(mExpression,
                      x0,
                      tol,
                      nMax,
                      verbose);

        double result = aitken.solve();

        std::cout << std::endl << "RESULT" << std::endl;
        std::cout << result << std::endl;
        std::cout << std::endl;
    } else if (boost::iequals(mMethod, "bisection")) {
        std::cout << std::endl << "BISECTION METHOD" << std::endl;

        Bisection bisection(mExpression,
                            x0,
                            tol,
                            nMax,
                            verbose,
                            lowerBound,
                            upperBound);

        double result = bisection.solve();

        std::cout << std::endl << "RESULT" << std::endl;
        std::cout << result << std::endl;
        std::cout << std::endl;
    } else if (boost::iequals(mMethod, "chord")) {
        std::cout << std::endl << "CHORD METHOD" << std::endl;

        Chord chord(mExpression,
                    x0,
                    tol,
                    nMax,
                    verbose);

        double result = chord.solve();

        std::cout << std::endl << "RESULT" << std::endl;
        std::cout << result << std::endl;
        std::cout << std::endl;
    } else if (boost::iequals(mMethod, "fixedpoint")) {
        std::cout << std::endl << "FIXED POINT METHOD" << std::endl;

        FixedPoint fixedPoint(mExpression,
                              x0,
                              tol,
                              nMax,
                              verbose);

        double result = fixedPoint.solve();

        std::cout << std::endl << "RESULT" << std::endl;
        std::cout << result << std::endl;
        std::cout << std::endl;
    } else if ((boost::iequals(mMethod, "newton"))&&(!systemFlag)) {
        mAssert(mDerivative.getEquation() != "0",
                "ERROR: No derivative provided");
        std::cout << std::endl << "NEWTON METHOD" << std::endl;

        Newton newton(mExpression,
                      mDerivative,
                      x0,
                      tol,
                      nMax,
                      verbose,
                      mod);

        double result = newton.solve();

        std::cout << std::endl << "RESULT" << std::endl;
        std::cout << result << std::endl;
        std::cout << std::endl;
    } else if ((boost::iequals(mMethod, "newton"))&&(systemFlag)) {
        mAssert(jacobianFlag,
                "ERROR: No jacobian provided");
        mAssert(vectorFlag,
                "ERROR: No initial vector provided");

        std::cout << std::endl << "NEWTON METHOD" << std::endl;

        std::vector<double> initial = mInitialVector.getValues();

        NewtonSystem newtonSystem(mSystem,
                                  mJacobian,
                                  initial,
                                  tol,
                                  nMax,
                                  verbose,
                                  mod);

        std::vector<double> result = newtonSystem.solve();

        std::cout << std::endl << "RESULT" << std::endl;
        std::vector<double>::const_iterator it;
        for (it = result.begin(); it != result.end(); ++it) {
            std::cout << std::setprecision(15) << *it << "\n";
        };
        std::cout << std::endl;
    } else {
        std::cout << std::endl << "ERROR: No method provided" << std::endl;
        help.show_usage();
        return 1;
    }

    return 0;
}


