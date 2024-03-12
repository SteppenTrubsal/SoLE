#include <iostream>
#include "someFunc.hpp"
using namespace std;

class matrix{
    double** data;
    int dim;
public:
    matrix();
    ~matrix();
    explicit matrix(int);
    explicit matrix(double**,int dimensions = 4);
    matrix(const matrix&);

    matrix& operator=(const matrix&);
    matrix operator+(const matrix&);
    matrix operator-(const matrix&);
    double* operator*(const double*);
    matrix operator*(const double);


    int getDim();
    double getNorm1();
    double getNorm2();
    double getNorm3();

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

int matrix::getDim(){
    return dim;
}

double matrix::getNorm1(){}

double matrix::getNorm2(){
    double *sum = new double[dim];
    for(int i = 0; i < dim; i++){
        sum[i] = 0;
        for(int j = 0; j < dim; j++){
            sum[i] += absolut(data[i][j]);
        }
    }
    double max = sum[0];
    for(int i = 1; i < dim; i++){
        if(max < sum[i]){
            max = sum[i];
        }
    }
    return max;
}

double matrix::getNorm3(){
    transpose().getNorm2();
}

void matrix::show(){
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
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

