#include <cmath>
#include "/usr/include/eigen3/Eigen/Eigenvalues"
using namespace std;

double absolut(const double& x){
    double temp;
    temp = (x < 0? -x : x);
    return temp;
}

double max(double* arr, int len = 4){
    double max = arr[0];
    for(int i = 0; i < len; i++){
        max = (max < arr[i] ? arr[i] : max);
    }
    return max;
}

double absMax(double* arr, int len = 4){
    double max = arr[0];
    for(int i = 0; i < len; i++){
        max = (max < absolut(arr[i])? absolut(arr[i]) : max);
    }
    return max;
}

double min(double* arr, int len = 4){
    double min = arr[0];
    for(int i = 0; i < len; i++){
        min = (min > arr[i] ? arr[i] : min);
    }
    return min;
}

double sum(double* arr, int len = 4){
    double sum = 0;
    for(int i = 0; i < len; i++){
        sum += arr[i];
    }
    return sum;
}

double getEucleadeanNorm(double* arr, int len = 4){
    double sum = 0;
    for(int i = 0; i < len; i++){
        sum += arr[i] * arr[i];
    }
    return sqrt(sum);
}

using namespace Eigen;

double* findEigenvalues(double** matrix, int len = 4) {
    MatrixXd m(len, len);
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            m(i, j) = matrix[i][j]; 
        }
    }

    SelfAdjointEigenSolver<MatrixXd> eigensolver(m);
    if (eigensolver.info() != Success) {
        return nullptr;
    }

    double* eigenvalues = new double[len];
    for (int i = 0; i < len; i++) {
        eigenvalues[i] = eigensolver.eigenvalues()[i];

    }

    return eigenvalues;
}