//methods.hpp

#include "matrix.hpp"
#include <iostream>
using namespace std;

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