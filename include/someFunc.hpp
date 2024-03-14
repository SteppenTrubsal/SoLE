#include <vector>
#if _MSVC_TRADITIONAL
#include <Eigen/Dense>
#else
#include <eigen3/Eigen/Dense>
#endif


using namespace std;

double getEucleadeanNorm(vector<double> v){
    double sum = 0;
    for(int i = 0; i < v.size(); i++){
        sum += v[i] * v[i];
    }
    return sqrt(sum);
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