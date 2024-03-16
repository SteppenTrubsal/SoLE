#pragma once
#if _MSVC_TRADITIONAL
#include <Eigen/Dense>
#else
#include <eigen3/Eigen/Dense>
#endif

using namespace std;
static double getEucleadeanNorm(vector<double> v) {
    double sum = 0;
    for (int i = 0; i < v.size(); i++) {
        sum += v[i] * v[i];
    }
    return std::sqrt(sum);
}
using namespace Eigen;
static vector<double> findEigenvalues(vector<vector<double>> matrix) {
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
    else {

        vector<double> eigenvalues(len);
        for (int i = 0; i < len; i++) {
            eigenvalues[i] = eigensolver.eigenvalues()[i];

        }

        return eigenvalues;
    }
}

class CustomMatrix{
    vector<vector<double>> data;
public:
    CustomMatrix();
    CustomMatrix(const CustomMatrix&);
    CustomMatrix(vector<vector<double>>);
    CustomMatrix(int);
    ~CustomMatrix();

    CustomMatrix& operator=(const CustomMatrix&);
    CustomMatrix operator+(const CustomMatrix&);
    CustomMatrix operator-(const CustomMatrix&);
    CustomMatrix operator*(const double&);
    CustomMatrix operator/(const double&);
    vector<double> operator*(const vector<double>);
    CustomMatrix operator*(const CustomMatrix&);

    vector<double> getLambda();
    double getNorm1();
    double getNorm2();
    double getNorm3();
    double getConditionNumber(int);
    int getDim();

    vector<CustomMatrix> getLUD();    //
    CustomMatrix getReverse();        //For Jacobi and Gauss-Seidel
    double getDet();            //
    CustomMatrix getTranspose();      //

    void EFill();               //
    double getTau();            //For simple iterations
};

