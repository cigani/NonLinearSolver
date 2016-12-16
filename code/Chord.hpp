//! Chord.hpp
/*!
  \brief A class constructing an object capable of solving nonlinear systems with the Chord method.
  \author Jaquier, Michael <michael.jaquier@epfl.ch>
  \author Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
  \version 1.0
  \date  10 December 2016
  \remark Ecole Polytechnic Federal de Lausanne (EPFL)
  \remark MATH-458 Programming Concepts in Scientific Computing
*/

#ifndef CHORD_HPP_
#define CHORD_HPP_

#include <iostream>
#include <iomanip>
#include <vector>
#include <assert.h>
#include "NonlinearSolver.hpp"
#include "Expression.hpp"

class Chord : public NonlinearSolver{
public:
    /*! A constructor to instantiate variables for the Chord method.
     *
     * \param equation An object of the Expression class that contains the mathematical expression for the class to evaluate.
     * \param initial The initial guess of the solution to the equation.
     * \param tolerance The tolerance value.  The method stops once the residual errors fall below this value.
     * \param maxIter The maximum number of iterations.  The method stops once this number is reached.
     * \param verbosity Set to true to print all intermediate and final results onto the console.
     */
    Chord(Expression &equation,
          double initial,
          double tolerance,
          int maxIter,
          bool verbosity);

    //! A virtual destructor for the Chord method.
    virtual ~Chord();

    /*! A function that returns the solution to the Chord method.
     *
     * \return The solution to the Chord Method.
     */
    double solve();

};
    
#endif /* CHORD_HPP_ */
