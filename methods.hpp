#include "matrix.h"
using namespace std;

template<class T>
int fixedPointIter(matrix<T> A, vector<T> b, vector<T> xk0, double tau, double eps) {
	vector<T> xk1(xk0.getLen());
	matrix<T> E(A.getDim());

	do {
		if ((E - A * tau) < 1) { return 0; }
		else { return 1; }

	} while ((xk1 - xk0).getEucleadeanNorm() < eps);
}