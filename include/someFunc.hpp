#include <vector>
#include <eigen3/Eigen/Dense>
using namespace std;

double getEucleadeanNorm(vector<double> v){
    
}
double power(double x0, double x1){
    double pow = 0;
    for(int i = 0; i < x1; x1++){
        pow *= x0;
    }
}

using namespace Eigen;
vector<double> findEigenvalues(vector<vector<double>> matrix) {
    int len = matrix.size();
    MatrixXd m(len, len);
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            m(i, j) = matrix[i][j]; 
        }
    }

    SelfAdjointEigenSolver<MatrixXd> eigensolver(m);
    if (eigensolver.info() != Success) {
    }
    else{

        vector<double> eigenvalues;
        for (int i = 0; i < len; i++) {
            eigenvalues[i] = eigensolver.eigenvalues()[i];

        }

        return eigenvalues;
    }
}