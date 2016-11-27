/*
 * Newton.cpp
 *
 * DESCRIPTION: Returns the root of an arbitrary nonlinear function using
 *              Newton's method or the modified Newton's method
 *
 * INPUTS:
 *          f        function whose root is to be determined
 *                   must take single argument of type double and return
 *                   single value of type double
 *          df       derivative of function whose root is to be determined
 *                   must take single argument of type double and return
 *                   single value of type double
 *          x0       initial guess for location of root
 *                   type: double
 *          tol      absolute error convergence tolerance
 *                   type: double
 *          nMax     maximum number of iterations to achieve convergence
 *                   type: int
 *          verbose  print intermediate results (default false)
 *                   type: boolean
 *          m        the multiplicity of the zeros of the function known apriori
 *                   type: int
 *
 * OUTPUT:
 *          root     approximate location of root
 *                   type: double
 *
 * Created on: November 27, 2015
 *
 * AUTHORS:
 * Jaquier, Michael <michael.jaquier@epfl.ch>
 * Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
 */

#include <Newton.hpp>

Newton::Newton() {}

Newton::~Newton() {}

double Newton::newtonSolver ( func1arg f,
			      func1arg df,
			      double x0,
			      double tol, 
			      int nMax,
			      bool verbose )
{
     double dx;
     int i;

     if ( verbose ) {
        std::cout << std::setw(3) << 0 << "\t" << std::setw(20)
             << x0 << std::setprecision(15) << std::endl;
     }

     for ( i = 1; i <= nMax; i++ ) {
         dx = f(x0) / df(x0);
         x0 -= dx;
         if ( verbose ) {
        	 std::cout << std::setw(3) << i << "\t"  << std::setw(20)
                 << x0 << std::setprecision(15) << std::endl;
	 }
         if ( fabs(dx) < tol ) {
	   return x0;
	 }
     }
     std::cout << "Maximum number of iterations exceeded" << std::endl;
     return x0;
}

double Newton::modifiedNewtonSolver ( func1arg f,
				      func1arg df,
				      double x0,
				      double tol, 
				      int nMax,
				      int m,
				      bool verbose )
{
     double dx;
     int i;

     if ( verbose == true ) {
    	 std::cout << std::setw(3) << 0 << "\t" << std::setw(20)
             << x0 << std::setprecision(15) << std::endl;
     }

     for ( i = 1; i <= nMax; i++ ) {
         dx = f(x0) / df(x0);
         x0 -= m*dx;
         if ( verbose ) {
        	 std::cout << std::setw(3) << i << "\t" << std::setw(20)
                 << x0 << std::setprecision(15) << std::endl;
	 }
         if ( fabs(dx) < tol ) {
	   return x0;
	 }
     }
     std::cout << "Maximum number of iterations exceeded" << std::endl;
     return x0;
}

double Newton::adaptiveNewtonSolver ( func1arg f,
				      func1arg df,
				      double x0,
				      double tol, 
				      int nMax,
				      bool verbose ) {}

double Newton::newtonSystemSolver ( func1arg f,
				    func1arg df,
				    double x0,
				    double tol, 
				    int nMax,
				    bool verbose ) {}

double Newton::modifiedNewtonSystemSolver ( func1arg f,
					    func1arg df,
					    double x0,
					    double tol, 
					    int nMax,
					    int m,
					    bool verbose ) {}
