#include <methods.hpp>
#include <iostream>
#if  _MSVC_TRADITIONAL
#include <src.hpp>
#include <CWindow.h>
#else
#include "include/src.hpp"
#include "include/CWindow.h"
#endif
using namespace std;

int main(){
    CWindow window;
    //window.start();
    cout << "Jacobi: " << Jacobi(matrix(A), b, x0, 0.01) << endl;
}