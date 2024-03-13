#include "methods.hpp"
#include "src.hpp"
using namespace std;

int main(){
    matrix A(createA());
    cout << A.getTau() << endl;
    //cout << simpleIterationsMethod(A, createB(), createX0(), A.getTau(), 0.01) << endl;
    A.show();
    cout << endl;
    A.getLUD();

    cout << JacobiMethod(A, createB(), createX0(), 0.01) << endl;
}