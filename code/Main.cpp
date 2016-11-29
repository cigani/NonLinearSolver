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

std::string stringPadding(std::string original, size_t charCount);
static void show_usage(std::string name);
static void show_methods();

int main(int argc, char* argv[]) {

	if (argc < 3) {
	        show_usage(argv[0]);
	        return 1;
	}

	std::string mMethod;
	std::string mExpression;
	double x0;
	int nMax = 1000;
	double tol = 0.001;
	bool verbose = true;

	// Parse the command line arguments for flags and values
	for (int i = 1; i < argc; i++) {
		if (i + 1 != argc) {
			if (( strcmp( argv[i], "-m") == 0) || ( strcmp( argv[i], "--method") == 0)) {
				// Method declaration
				if ( strcmp( argv[i + 1], "aitken") == 0 ) {
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
				// Maximum number of iterations.  Default 1000 as defined above.
				tol = std::stod(argv[i + 1]);
			} else if ( strcmp( argv[i], "-v") == 0) {
				// Maximum number of iterations.  Default 1000 as defined above.
				verbose = argv[i + 1];
			} else if (( strcmp( argv[i], "-h") == 0) || ( strcmp( argv[i], "--help") == 0)) {
				// Print help dialog
				show_usage(argv[0]);
			} else {
				continue;
			}
		}
	}

	if ( mMethod == "fixedpoint") {
		std::cout << "Calling the Fixed Point Method" << std::endl;
		FixedPoint fixedPoint;
	} else if ( mMethod == "newton") {
		std::cout << "Calling the Newton Method" << std::endl;
		Newton newton;
		double result = newton.newtonExprtkSolver(mExpression, x0, tol, nMax, verbose);
		std::cout << result << std::endl;
	} else if ( mMethod == "chord") {
		std::cout << "Calling the Chord Method" << std::endl;
		Chord chord;
	} else if ( mMethod == "aitken") {
		std::cout << "Calling the Aitken Method" << std::endl;
		Aitken aitken;
	}
}

	/*
	int i = 0;
	while (true){
		std::cout << "Enter coefficient for " << "x^" << i << " " << "Terminate with a blank line: ";
		getline(std::cin, coefficient);
	    if (coefficient.empty()){
	    	break;

	    } else {
	    	coefVector.push_back(stod(coefficient));
	    }
	    ++i;

        std::cout << "Enter Equation ";
		getline(std::cin, coefficient);
        break;
	}

	double f = mEquation.getPolyEquation((const std::vector<double> &) coefVector, x0);
	double df = mEquation.getPolyDerivative((const std::vector<double> &) coefVector, x0);
    double ff = mEquation.exprtkGenerate2D((std::string &) coefficient, x0);
    double dff = mEquation.exprtkGenerate2DDerivative(
            (std::string &) coefficient, x0);

    printf("Result Equation: %10.5f\n", ff);
    printf("Result Derivative: %10.5f\n", dff);

	// Currently uses cosine as the iteration function
	FixedPoint mFixedPoint;
	double result = mFixedPoint.fixedPointSolver((const std::vector<double> &) coefVector, x0, 0.001, 1000, false );
    Chord mChord;
    //double testChord = mChord.chordSolver((const std::vector<double> &) coefVector, x0, 0.001, 1000, true);
    Newton mNewton;
    //double testNewton = mNewton.newtonExprtkSolver((std::string &) coefficient,
    //                                               x0, 0.001, 100000, true);
	
    std::cout << result << std::endl;
    return 0;
}
*/

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
				<< std::endl
				<< std::endl
	    		<< "Options:\n"
				<< "\t"
				<< stringPadding("-h,--help", 20)
				<< stringPadding("Show this help message", 60)
				<< std::endl
				<< "\t"
				<< stringPadding("-m,--method", 20)
				<< stringPadding("Specify Non-Linear Solver", 60)
				<< std::endl
				<< "\t"
				<< stringPadding("-e,--expression", 20)
				<< stringPadding("Mathematical expression to solve enclosed in ''", 60)
				<< std::endl
				<< "\t"
				<< stringPadding("-xi", 20)
				<< stringPadding("Initial guess of the solution", 60)
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
				<< stringPadding("True to print all intermediate calculations [default: false]", 60)
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
