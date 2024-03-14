#include <methods.hpp>
#include <iostream>
#if  _MSVC_TRADITIONAL
#include <src.hpp>
#else
#include "include/src.hpp"
#endif
using namespace std;

int main(){
    cout << Jacobi(matrix(A),b,x0,0.01) << endl;
}