/*
 * Gauss.cpp
 *
 * DESCRIPTION: Gaussian elimination for systems of equations.
 *
 * Created on: December 10, 2016
 *
 * AUTHORS:
 * Jaquier, Michael <michael.jaquier@epfl.ch>
 * Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
 */

#include <iostream>
#include "Gauss.h"

std::vector<double> Gauss::solveSystem(std::vector<std::vector<double>> &jacobian,
                                       std::vector<double> &funcSolution, int degree) {
    int N=degree+1, i, j, k;
    std::vector< std::vector<double> > A = jacobian;

    std::vector<std::vector<double>>::iterator it;
    i=0;
    for (it = A.begin(); it != A.end(); ++it) {  // Augment the matrix before preceding
        (*it).push_back(funcSolution[i]);
        ++i;
    }

    std::vector<double> a(N);
    for (i = 0; i < N; ++i){                 //First, pivot the Matrix
        for (k = i+1; k < N; ++k){
            if (A[i][i] < A[k][i]){
                for (j=0; j <= N; ++j){
                    double temp = A[i][j];
                    A[i][j] = A[k][j];
                    A[k][j] = temp;
                }
            }
        }
    }

    for (i = 0; i < N - 1; ++i) {  //Loop over elements to perform Gaussian Elimination
        for (k=i+1; k < N; ++k){
            double t=A[k][i]/A[i][i];
            for (j=0; j <= N; ++j){
                A[k][j]=A[k][j]-t*A[i][j];
            }
        }
    }

    for (i=N-1; i >= 0; --i){              //back-substitution
        a[i]=A[i][N];
        for (j=0; j < N; ++j){
            if (j!=i){
                a[i] = a[i]-A[i][j]*a[j];
            }
        }
        a[i]=a[i]/A[i][i];
    }

    return a;
}