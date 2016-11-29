#ifndef NEWTON_HPP_
#define NEWTON_HPP_

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

class Newton {
private:
 // Private variables
	void printVerbose(int i, double &x);

public:
    
    // Constructors and destructors
    Newton();
    virtual ~Newton();
    
    // Public variables
    typedef double (*func1arg) (double);

    // Public methods
	double newtonSolver(const std::vector<double> &coef,
						double x0,
						double tol,
						int nMax,
						bool verbose);

	double modifiedNewtonSolver(const std::vector<double> &coef,
								double x0,
								double tol,
								int nMax,
								int m,
								bool verbose);

    double adaptiveNewtonSolver ( func1arg f,
				  func1arg df,
				  double x0,
				  double tol,
				  int nMax,
				  bool verbose );

    double newtonSystemSolver ( func1arg f,
				func1arg df,
				double x0,
				double tol,
				int nMax,
				bool verbose );

    double modifiedNewtonSystemSolver ( func1arg f,
					func1arg df,
					double x0,
					double tol,
					int nMax,
					int m,
					bool verbose );

	double newtonExprtkSolver(const std::string &eq,
							  double x0,
							  double tol,
							  double nMax,
							  bool verbose);
};
    
#endif /* NEWTON_HPP_ */
