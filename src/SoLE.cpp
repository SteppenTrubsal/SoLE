#include "methods.hpp"
#include "src.hpp"
using namespace std;

int main(){
    matrix A(createA());
    //cout << "Simple Iterations: " << simpleIterationsMethod(A, createB(), createX0(), A.getTau(), 0.01) << endl << endl;
    //cout << "Jacobi: " << JacobiMethod(A, createB(), createX0(), 0.01) << endl << endl;
    cout << "GaussSeidel: " << GaussSeidelMethod(A, createB(), createX0(), 0.01) << endl << endl;
}