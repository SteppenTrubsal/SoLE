#include <iostream>
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

int matrix::getDim(){
    return dim;
}

double matrix::getNorm1(){}

double matrix::getNorm2(){
    double *sum = new double[dim];
    for(int i = 0; i < dim; i++){
        sum[i] = 0;
        for(int j = 0; j < dim; j++){
            if(data[i][j]<0){
                sum[i] += (-data[i][j]);
            }
            else{
                sum[i] += data[i][j];
            }
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

