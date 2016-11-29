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

int main(int argc, char* argv[]) {

	std::string coefficient;
	std::vector<double> coefVector;
	double x0;
	Equations mEquation;

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
	    /*
        std::cout << "Enter Equation ";
		getline(std::cin, coefficient);
        std::cout << "Enter Starting Value";
        break;
        */
	}

	// The following loop is for only development purpose
	std::cout << "Enter initial value: ";
	std::cin >> x0;
	std::cout << std::endl;

	/*
	for (std::vector<double>::const_iterator i = coefVector.begin(); i != coefVector.end(); ++i) {
	    std::cout << *i << ' ';
	}
	*/

//	double f = mEquation.getPolyEquation((const std::vector<double> &) coefVector, x0);
//	double df = mEquation.getPolyDerivative((const std::vector<double> &) coefVector, x0);
//    double ff = mEquation.exprtkGenerate2D((std::string &) coefficient, x0);
//    double dff = mEquation.exprtkGenerate2DDerivative(
//            (std::string &) coefficient, x0);
//
//    printf("Result Equation: %10.5f\n", ff);
//    printf("Result Derivative: %10.5f\n", dff);

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
