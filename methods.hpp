#include "matrix.hpp"
using namespace std;

double simpleIterationsMethod(matrix A, double* _b, double* x0, double tau, double eps, int bLen = 4, int xk0Len = 4){
    matrix E(A.getDim());
    double *xk0 = new double[xk0Len];
    cout << "xk0: ";
    for(int i = 0; i < xk0Len; i++){
        xk0[i] = x0[i];
        cout << xk0[i] << " ";
    }
    cout << endl;
    
    double *b = new double[xk0Len];
    cout << "b: ";
    for(int i = 0; i < xk0Len; i++){
        b[i] = _b[i];
        cout << b[i] << " ";
    }
    cout << endl;
    double *diff = new double[xk0Len];

    /*double tau = 1;
    cout << "tau: ";
    while(((E - A*tau).getNorm2() > 1) and (tau > 0)){
        tau = tau - 0.0001;
        cout << tau << " " << (E - A*tau).getNorm2() << endl;
    }*/

    double gg = (E - A * tau).getNorm2();
	//if (gg > 1) { return gg; }
    double counter = 0;

    do {
        double *xk1 = new double[xk0Len];
        for(int i = 0; i < xk0Len; i++){
            xk1[i] = gg*xk0[i] + tau*b[i];
        }
        
        cout << "diff: ";
        for(int i = 0; i < xk0Len; i++) {
            diff[i] = xk0[i] - xk1[i];
            cout << diff[i] << " ";
        }
        delete[] xk0;
        xk0 = xk1;
        counter++;
        cout << counter << " " << getEucleadeanNorm(diff) << endl;
	} while (getEucleadeanNorm(diff) > eps);
    for(int i = 0 ; i < bLen; i++) {
            cout << xk0[i] << " ";
        }
        cout << endl;
    return counter;
}

double JacobiMethod(matrix A, double* _b, double* x0, double eps){
    matrix* LUD = A.getLUD();

}