//methods.hpp

#include "matrix.hpp"
#include <iostream>
using namespace std;

int SimpleIterations(matrix A, vector<double> b, vector<double> x, double eps) {
    int counter = 0;
    double tau = A.getTau();
    matrix E(x.size());
    E.EFill();
    matrix temp = E - A * tau;
    vector<double> x1(x.size());
    vector<double> diff;

    do {
        vector<double> xtemp = temp * x;
        for (int i = 0; i < b.size(); i++) {
            x1[i] = xtemp[i] + b[i] * tau;
        }
        diff.clear();
        for (int i = 0; i < x1.size(); i++) {
            diff.push_back(x[i] - x1[i]);
        }
        x.clear();
        x = x1;
        counter++;
    } while (getEucleadeanNorm(diff) > eps);
    for (int i = 0; i < x.size(); i++) {
        cout << x[i] << " ";
    }
    cout << endl;
    return counter;
}

int Jacobi(matrix A, vector<double> b,vector<double> x, double eps){
    vector<matrix> LUD = A.getLUD();
    vector<double> diff;
    int counter = 0;
    do{
        vector<double> temp1((LUD[0]+LUD[1])*x);
        vector<double> temp2(x.size());
        for(int i = 0; i < x.size(); i++){
            temp2[i] = b[i] - temp1[i];
        }
        vector<double> x1 = LUD[2].getReverse() * temp2;
        diff.clear();
        for(int i = 0; i < x1.size(); i++){
            diff.push_back(x[i] - x1[i]);
        }
        x.clear();
        x= x1;
        counter++;
    }while(getEucleadeanNorm(diff) > eps);
    for (int i = 0; i < x.size(); i++) {
        cout << x[i] << " ";
    }
    cout << endl;
    return counter;
}

int GaussSeidel(matrix A, vector<double> b, vector<double> x, double eps) {
    vector<matrix> LUD = A.getLUD();
    vector<double> diff;
    int counter = 0;

    matrix temp1 = (LUD[0] + LUD[2]).getReverse();
    matrix temp2 = temp1 * LUD[1];
    do {
        vector<double> temp3 = temp1 * b;
        vector<double> temp4 = temp2 * x;
        vector<double> x1(b.size());
        for (int i = 0; i < b.size(); i++) {
            x1[i] = temp3[i] - temp4[i];
        }
        diff.clear();
        for (int i = 0; i < x1.size(); i++) {
            diff.push_back(x[i] - x1[i]);
        }
        x.clear();
        x = x1;
        counter++;
    }while (getEucleadeanNorm(diff) > eps);
    for (int i = 0; i < x.size(); i++) {
        cout << x[i] << " ";
    }
    cout << endl;
    return counter;
}