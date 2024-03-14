#include "include/methods.hpp"
#include "include/src.hpp"
#include <iostream>
using namespace std;

int main(){
    cout << Jacobi(matrix(A),b,x0,0.01) << endl;
}