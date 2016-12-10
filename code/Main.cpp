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
#include "Expression.hpp"
#include "Helper.hpp"
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
    double x0 = 0.0;
    int nMax = 1000;
    double tol = 0.001;
    bool verbose = false;
    double lowerBound = -1.0;
    double upperBound = 1.0;

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
                mExpression.setEquation(argv[i + 1]);
            } else if (strcmp(argv[i], "-d") == 0) {
                // Derivative Expression
                mDerivative.setEquation(argv[i + 1]);
            } else if (strcmp(argv[i], "-xi") == 0) {
                // Initial Value
                x0 = std::stod(argv[i + 1]);
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
            } else if ((strcmp(argv[i], "-h") == 0) ||
                       (strcmp(argv[i], "--help") == 0)) {
                // Print help dialog
                help.show_usage();
            } else {
                continue;
            }
        }
    }

    mAssert(mExpression.getEquation() != "0",
            "ERROR: No mathematical expression provided");

    if (boost::iequals(mMethod, "aitken")) {
        std::cout << std::endl << "AITKEN METHOD" << std::endl;
        Aitken aitken;
        double result = aitken.aitkenExprtkSolver(mExpression, x0, tol, nMax,
                                                  verbose);
        std::cout << std::endl << "RESULT: " << result << std::endl
                  << std::endl;
    } else if (boost::iequals(mMethod, "bisection")) {
        std::cout << std::endl << "BISECTION METHOD" << std::endl;
        Bisection bisection(mExpression, x0, tol, nMax, verbose, lowerBound, upperBound);
        double result = bisection.solve();
        std::cout << std::endl << "RESULT: " << result << std::endl
                  << std::endl;
    } else if (boost::iequals(mMethod, "chord")) {
        std::cout << std::endl << "CHORD METHOD" << std::endl;
        Chord chord(mExpression, x0, tol, nMax, verbose);
        double result = chord.solve();
        std::cout << std::endl << "RESULT: " << result << std::endl
                  << std::endl;
    } else if (boost::iequals(mMethod, "fixedpoint")) {
        std::cout << std::endl << "FIXED POINT METHOD" << std::endl;
        FixedPoint fixedPoint(mExpression, x0, tol, nMax, verbose);
        double result = fixedPoint.solve();
        std::cout << std::endl << "RESULT: " << result << std::endl
                  << std::endl;
    } else if (boost::iequals(mMethod, "newton")) {
        mAssert(mDerivative.getEquation() != "0",
                "ERROR: No mathematical expression provided");
        std::cout << std::endl << "NEWTON METHOD" << std::endl;
        Newton newton(mExpression, mDerivative, x0, tol, nMax, verbose);
        double result = newton.solve();
        std::cout << std::endl << "RESULT: " << result << std::endl
                  << std::endl;
    } else {
        std::cout << std::endl << "ERROR: No method provided" << std::endl;
        help.show_usage();
        return 1;
    }

    return 0;
}


