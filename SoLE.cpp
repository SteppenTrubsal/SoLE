#include "methods.hpp"
#include "src.hpp"
using namespace std;

int main(){
    matrix A(createA());
    cout << fixedPointMethod(A, createB(), createX0(), _tau, 0.01) << endl;
}