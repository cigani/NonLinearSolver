#ifndef CHORD_HPP_
#define CHORD_HPP_

#include <iostream>
#include <iomanip>
#include <vector>
#include <assert.h>
#include "NonlinearSolver.hpp"
#include "Equations.hpp"

class Chord : public NonlinearSolver{
private:
public:
    // Constructors and destructors
    Chord(const std::vector<std::string> &equation,
          std::vector<double> initial,
          double tolerance,
          int maxIter,
          bool verbosity);
    virtual ~Chord();

    // Public methods
    std::vector<double> solve();
};
    
#endif /* CHORD_HPP_ */
