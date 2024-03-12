#include "matrix.hpp"
using namespace std;

int fixedPointMethod(matrix A, double* b, double* xk0, double tau, double eps, int bLen = 4, int xk0Len = 4){
    matrix E(A.getDim());
    double *xk1 = new double[xk0Len];
    double *diff = new double[xk0Len];

    do {
        double gg = (E - A * tau).getNorm2();
		if (gg < 1) { return 0; }
		else { return gg; }



        for(int i = 0; i < xk0Len; i++) {
            diff[i] = xk0[i] - xk1[i];
        }
	} while (getEucleadeanNorm(diff) < eps);
}