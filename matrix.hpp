#include <iostream>
#include "someFunc.hpp"
using namespace std;

class matrix{
    double** data;
    int dim;

    matrix(const matrix&);
    void nullExpand(int nDim = 4);
public:
    matrix();
    ~matrix();
    explicit matrix(int);
    explicit matrix(double**,int dimensions = 4);

    matrix& operator=(const matrix&);
    matrix operator+(const matrix&);
    matrix operator-(const matrix&);
    double* operator*(const double*);
    matrix operator*(const double);
    matrix operator*(const matrix&);


    int getDim();
    double* getLambda();
    double getNorm1();
    double getNorm2();
    double getNorm3();
    double getTau();

    matrix* getLUD();

    void show();
    matrix transpose();
};

matrix::matrix():data(nullptr),dim(0){}
matrix::~matrix(){
    for(int i = 0; i < dim; i++){
        delete[] data[i];
    }
    delete[] data;
}

matrix::matrix(int dimensions): dim(dimensions), data(new double*[dimensions]) {
    for(int i = 0; i < dim; i++){
        data[i] = new double[dimensions];
        for(int j = 0; j < dimensions; j++){
            if(i == j){
                data[i][j] = 1;
            }else{
                data[i][j] = 0;
            }
        }
    }
}

matrix::matrix(double** dynamicArr, int dimensions): dim(dimensions), data(new double*[dimensions]) {
    for(int i = 0; i < dim; i++){
        data[i] = new double[dimensions];
        for(int j = 0; j < dimensions; j++){
            data[i][j] = dynamicArr[j][i];
        }
    }
}

matrix::matrix(const matrix& m){
    dim = m.dim;
    data = new double*[dim];
    for(int i = 0; i < dim; i++){
        data[i] = new double[dim];
        for(int j = 0; j < dim; j++){
            data[i][j] = m.data[i][j];
        }
    }
}

matrix& matrix::operator=(const matrix& m){
    if(this!= &m){
        for(int i = 0; i < dim; i++){
            delete[] data[i];
        }
        delete[] data;
        dim = m.dim;
        data = new double*[dim];
        for(int i = 0; i < dim; i++){
            data[i] = new double[dim];
            for(int j = 0; j < dim; j++){
                data[i][j] = m.data[i][j];
            }
        }
    }
    return *this;
}

matrix matrix::operator+(const matrix& m){
    if(dim!= m.dim){
        exit(1);
    }
    matrix result(dim);
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            result.data[i][j] = data[i][j] + m.data[i][j];
        }
    }
    return result;
}

matrix matrix::operator-(const matrix& m){
    if(dim!= m.dim){
        exit(1);
    }
    matrix result(dim);
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            result.data[i][j] = data[i][j] - m.data[i][j];
        }
    }
    return result;
}

double* matrix::operator*(const double* m){
    double *result = new double[dim];
    for(int i = 0; i < dim; i++){
        result[i] = 0;
        for(int j = 0; j < dim; j++){
            result[i] += data[i][j] * m[j];
        }
    }
    return result;
}

matrix matrix::operator*(const double mul){
    matrix result(dim);
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            result.data[i][j] = data[i][j] * mul;
        }
    }
    return result;
}

matrix matrix::operator*(const matrix& m){
    matrix result(dim);
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            result.data[i][j] = 0;
            for(int k = 0; k < dim; k++){
                result.data[i][j]+=this->data[i][k] * m.data[k][j];
            }
        }
    }
}

int matrix::getDim(){
    return dim;
}

double* matrix::getLambda(){
    return findEigenvalues(data);
}

double matrix::getNorm1(){
    matrix temp(*this);
    return sqrt(max((temp*temp.transpose()).getLambda()));
}

double matrix::getNorm2(){
    double *sum = new double[dim];
    for(int i = 0; i < dim; i++){
        sum[i] = 0;
        for(int j = 0; j < dim; j++){
            sum[i] += absolut(data[i][j]);
        }
    }
    return max(sum);
}

double matrix::getNorm3(){
    transpose().getNorm2();
}

double matrix::getTau(){
    return 2/(1+absMax(getLambda()));
}
matrix* matrix::getLUD(){
    matrix* res = new matrix[3];
    for(int i = 0; i < 3; i++){
        res[i].nullExpand();
    }
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            if(j < i){
                res[0].data[i][j] = data[i][j];
                res[1].data[i][j] = 0;
                res[2].data[i][j] = 0;
            }
            else if (j == i) {
                res[0].data[i][j] = 0;
                res[1].data[i][j] = data[i][j];
                res[2].data[i][j] = 0;
            }
            else if (j > i) {
                res[0].data[i][j] = 0;
                res[1].data[i][j] = 0;
                res[2].data[i][j] = data[i][j];
            }
        }
    }
    for(int i = 0; i < 3; i++){
        res[i].show();
    }
    return res;
}


void matrix::show(){
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}

void matrix::nullExpand(int nDim){
    data = new double*[nDim];
    for(int i = dim; i < nDim; i++){
        data[i] = new double[nDim];
        for(int j = 0; j < nDim; j++){
            data[i][j] = 0;
        }
    }
    dim = nDim;
}

matrix matrix::transpose(){
    matrix trans(dim);
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            trans.data[j][i] = data[i][j];
        }
    }
    return trans;
}

