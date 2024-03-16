#if  _MSVC_TRADITIONAL
#include <CWindow.h>
#else
#include "include/CWindow.h"
#endif

int main() {
    CWindow window;
    window.start();
    //cout << "Simple Iterations: " << SimpleIterations(matrix(A), b, x0, 0.01) << endl;
    //cout << "Jacobi: " << Jacobi(matrix(A), b, x0, 0.01) << endl;
    //cout << "GaussSeidel: " << GaussSeidel(matrix(A), b, x0, 0.01) << endl;
}



