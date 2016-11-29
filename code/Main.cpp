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
#include "FixedPoint.hpp"
#include "Equations.hpp"
#include "Chord.hpp"
#include "Newton.hpp"
#include "Aitken.hpp"
#include "Bisection.hpp"

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

std::string stringPadding(std::string original, size_t charCount);
static void show_usage(std::string name);
static void show_methods();

int main(int argc, char* argv[]) {

	if (argc < 3) {
	        show_usage(argv[0]);
	        return 1;
	}

	std::string mMethod;
	std::string mExpression = "NULL";
	double x0 = 0.0;
	int nMax = 1000;
	double tol = 0.001;
	bool verbose = false;
	double lowerBound = -1.0;
	double upperBound = 1.0;

	// Parse the command line arguments for flags and values
	for (int i = 1; i < argc; i++) {
		if (i + 1 != argc) {
			if (( strcmp( argv[i], "-m") == 0) || ( strcmp( argv[i], "--method") == 0)) {
				// Method declaration
				if ( strcmp( argv[i + 1], "aitken") == 0 ) {
					mMethod = argv[i + 1];
				} else if ( strcmp( argv[i + 1], "bisection") == 0 ) {
					mMethod = argv[i + 1];
				} else if ( strcmp( argv[i + 1], "chord") == 0 ) {
					mMethod = argv[i + 1];
				} else if ( strcmp( argv[i + 1], "fixedpoint") == 0 ) {
					mMethod = argv[i + 1];
				} else if ( strcmp( argv[i + 1], "newton") == 0 ) {
					mMethod = argv[i + 1];
				} else {
					std::cout << std::endl << "ERROR: Unknown method provided" << std::endl;
					show_methods();
					return 1;
				}
			} else if ( strcmp( argv[i], "-e") == 0) {
				// Mathematical Expression
				mExpression = argv[i + 1];
			} else if ( strcmp( argv[i], "-xi") == 0) {
				// Initial Value
				x0 = std::stod(argv[i + 1]);
			} else if ( strcmp( argv[i], "-nmax") == 0) {
				// Maximum number of iterations.  Default 1000 as defined above.
				nMax = std::stoi(argv[i + 1]);
			} else if ( strcmp( argv[i], "-t") == 0) {
				// Error tolerance.  Default 0.001.
				tol = std::stod(argv[i + 1]);
			} else if ( strcmp( argv[i], "-v") == 0) {
				// Verbose setting.  Default false.
				std::istringstream(argv[i + 1]) >> std::boolalpha >> verbose;
				// Doesn't work. Weird.
				// verbose = true;
			} else if ( strcmp( argv[i], "-l") == 0) {
				// Lower bound of the search interval
				lowerBound = std::stod(argv[i + 1]);
			}else if ( strcmp( argv[i], "-u") == 0) {
				// Upper bound of the search interval
				upperBound = std::stod(argv[i + 1]);
			} else if (( strcmp( argv[i], "-h") == 0) || ( strcmp( argv[i], "--help") == 0)) {
				// Print help dialog
				show_usage(argv[0]);
			} else {
				continue;
			}
		}
	}

	mAssert(mExpression != "NULL", "ERROR: No mathematical expression provided");

	if ( mMethod == "aitken") {
		std::cout << "Calling the Aitken Method" << std::endl;
		Aitken aitken;
		double result = aitken.aitkenExprtkSolver(mExpression, x0, tol, nMax, verbose);
		std::cout << result << std::endl;
	} else if ( mMethod == "bisection") {
		std::cout << "Calling the Bisection Method" << std::endl;
		Bisection bisection;
		double result = bisection.bisectionSolver(mExpression, lowerBound, upperBound, tol, nMax, verbose);
		std::cout << result << std::endl;
	} else if ( mMethod == "chord") {
		std::cout << "Calling the Chord Method" << std::endl;
		Chord chord;
		double result = chord.chordExprtkSolver(mExpression, x0, tol, nMax, verbose);
		std::cout << result << std::endl;
	} else if ( mMethod == "fixedpoint") {
		std::cout << "Calling the Fixed Point Method" << std::endl;
		FixedPoint fixedPoint;
		double result = fixedPoint.fixedPointExprtkSolver(mExpression, x0, tol, nMax, verbose);
		std::cout << result << std::endl;
	} else if ( mMethod == "newton") {
		std::cout << "Calling the Newton Method" << std::endl;
		Newton newton;
		double result = newton.newtonExprtkSolver(mExpression, x0, tol, nMax, verbose);
		std::cout << result << std::endl;
	} else {
		std::cout << std::endl << "ERROR: No method provided" << std::endl;
		show_usage(argv[0]);
		return 1;
	}

	return 0;
}

std::string stringPadding(std::string original, size_t charCount ) {
    original.resize( charCount, ' ' );
    return original;
}

static void show_usage(std::string name) {
	    std::cerr << std::endl
				<< "Usage: "
				<< name
				<< " -m %s"
				<< " -e '%s'"
				<< " -xi %d"
				<< " -nmax %i"
				<< " -t %d"
				<< " -v %b"
				<< " -l %d"
				<< " -u %d"
				<< std::endl
				<< std::endl
				<< "Required:\n"
				<< "\t"
				<< stringPadding("-m,--method", 20)
				<< stringPadding("Specify Non-Linear Solver", 60)
				<< std::endl
				<< "\t"
				<< stringPadding("-e,--expression", 20)
				<< stringPadding("Mathematical expression to solve enclosed in ''", 60)
				<< std::endl
				<< std::endl
	    		<< "Optional:\n"
				<< "\t"
				<< stringPadding("-h,--help", 20)
				<< stringPadding("Show this help message", 60)
				<< std::endl
				<< "\t"
				<< stringPadding("-xi", 20)
				<< stringPadding("Initial guess of the solution [default: 0.0]", 60)
				<< std::endl
				<< "\t"
				<< stringPadding("-nmax", 20)
				<< stringPadding("Maximum number of iterations [default: 1000]", 60)
				<< std::endl
				<< "\t"
				<< stringPadding("-t", 20)
				<< stringPadding("The convergence tolerance [default: 0.001]", 60)
				<< std::endl
				<< "\t"
				<< stringPadding("-v", 20)
				<< stringPadding("true to print all intermediate calculations [default: false]", 60)
				<< std::endl
				<< "\t"
				<< stringPadding("-l", 20)
				<< stringPadding("The lower bound of the search interval [default: -1.0]", 60)
				<< std::endl
				<< "\t"
				<< stringPadding("-u", 20)
				<< stringPadding("The upper bound of the search interval [default: 1.0]", 60)
				<< std::endl;
	    show_methods();
}

static void show_methods() {
	    std::cerr << std::endl
	    		<< "Non-Linear Solvers:"
	    		<< std::endl
				<< "\t"
				<< stringPadding("aitken", 20)
				<< stringPadding("Aitken Method", 40)
				<< std::endl
	    		<< "\t"
	    		<< stringPadding("bisection", 20)
				<< stringPadding("Bisection Method", 40)
				<< std::endl
	    		<< "\t"
	    		<< stringPadding("chord", 20)
				<< stringPadding("Chord Method", 40)
				<< std::endl
				<< "\t"
				<< stringPadding("fixedpoint", 20)
				<< stringPadding("Fixed Point Method", 40)
				<< std::endl
				<< "\t"
				<< stringPadding("newton", 20)
				<< stringPadding("Newton Method", 40)
				<< std::endl
				<< std::endl;
}


