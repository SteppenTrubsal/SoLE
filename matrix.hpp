#include "vector.hpp"
#include <iostream>
using namespace std;

template <class T>
class Matrix{
    Vector<Vector<T>>* data;
    int dimensions;
public:
    Matrix();
    explicit Matrix(int);
    explicit Matrix(T**);
    ~Matrix();

    Vector<T>& operator[](int);

    Matrix* getLUD();
    void show();
};

template<class T>
Matrix<T>::Matrix():data(new Vector<Vector<T>>[1]), dimensions(0){}

template<class T>
Matrix<T>::Matrix(int dim) : dimensions(dim), data(new Vector<Vector<T>>(dimensions)){}

template<class T>
Matrix<T>::~Matrix(){delete[] data; dimensions = 0;}

template<class T>
Matrix<T>::Matrix(T** twoDimStatArr){
    dimensions = sizeof(twoDimStatArr)/sizeof(twoDimStatArr[0]);
    data = new Vector<Vector<T>>(dimensions);
    for(int i =0; i < dimensions; i++){
        for(int j = 0; j < sizeof(twoDimStatArr[i])/sizeof(twoDimStatArr[i][0]); j++){
            data[i][j] = twoDimStatArr[i][j];
        }
    }
}

template <class T>
Vector<T>& Matrix<T>::operator[](int idx){
    return data[idx];
}

template <class T>
void Matrix<T>::show(){
    for(int i = 0; i < dimensions; i++){
        for(int j = 0; j < data[i].getLen(); j++){
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}

/*template<class T>
Matrix<T>* Matrix<T>::getLUD(){
    for(int i = 0; i < dimensions; i++){
        for(int )
    }
}*/