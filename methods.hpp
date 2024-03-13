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
    double* b = new double[A.getDim()];
    double* xk0 = new double[A.getDim()];
    
    for(int i = 0; i < A.getDim(); i++){
        b[i] = _b[i];
    }
    for(int i = 0; i < A.getDim(); i++){
        xk0[i] = x0[i];
    }
    
    matrix L = LUD[0];
    matrix U = LUD[1];
    matrix DRev = LUD[2].getReverse();

    double* diff = new double[A.getDim()];
    int counter = 0;

    do{
        double* xk1 = new double[A.getDim()];
        double* temp1 = (L+U)*xk0;
        double* temp2 = new double[A.getDim()];
        for(int i = 0; i < A.getDim(); i++) {
            temp2[i] = b[i] - temp1[i];
        }
        xk1 = DRev*temp2;
        for(int i = 0; i < A.getDim(); i++) {
            diff[i] = xk1[i] - xk0[i];
        }
        delete[] xk0;
        xk0 = xk1;
        counter++;
    }while(getEucleadeanNorm(diff) > eps);
    for(int i = 0 ; i < A.getDim(); i++) {
            cout << xk0[i] << " ";
        }
        cout << endl;
    return counter;
}

double GaussSeidelMethod(matrix A, double* _b, double* x0, double eps){
    matrix* LUD = A.getLUD();
    double* b = new double[A.getDim()];
    double* xk0 = new double[A.getDim()];
    
    for(int i = 0; i < A.getDim(); i++){
        b[i] = _b[i];
    }
    for(int i = 0; i < A.getDim(); i++){
        xk0[i] = x0[i];
    }
    
    matrix L = LUD[0];
    matrix U = LUD[1];
    matrix D = LUD[2];

    double* diff = new double[A.getDim()];
    int counter = 0;

    do{
        double* xk1 = new double[A.getDim()];
        double* temp1 = (L+D).getReverse()*b;
        double* temp2 = (L+D).getReverse()*U*xk0;
        for(int i = 0; i < A.getDim(); i++) {
            xk1[i] = temp1[i] - temp2[i];
        }
        for(int i = 0; i < A.getDim(); i++) {
            diff[i] = xk1[i] - xk0[i];
        }
        delete[] xk0;
        xk0 = xk1;
        counter++;
    }while(getEucleadeanNorm(diff) > eps);
    for(int i = 0 ; i < A.getDim(); i++) {
            cout << xk0[i] << " ";
        }
        cout << endl;
    return counter;
}