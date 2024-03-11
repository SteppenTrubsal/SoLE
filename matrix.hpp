#include "vector.h"
using namespace std;

template<class T>
class matrix {
	vector<vector<T>> data;
	int dim;
public:
	matrix();
	explicit matrix(int);
	explicit matrix(T**, int);
	~matrix();

	matrix<T>& operator-(const matrix<T>&);
	matrix<T>& operator*(const T&);
	vector<T>& operator*(const vector<T>&);

	int getDim();
	T getNorm1();
	T getNorm2();
	T getNorm3();

	void show();
	matrix<T> transpose();
};

template<class T>
matrix<T>::matrix(): data(), dim(0){}

template<class T>
matrix<T>::matrix(int dimensions) : dim(dimensions), data(dim) {
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			if (i == j) {
				data[i][j] = 1;
			}
			else {
				data[i][j] = 0;
			}
		}
	}
}

template<class T>
matrix<T>::matrix(T** initArr, int dimensions) : dim(dimensions), data(dim) {
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			data[i][j] = initArr[i][j];
		}
	}
}

template<class T>
matrix<T>::~matrix() { dim = 0; }

template<class T>
matrix<T>& matrix<T>::operator-(const matrix<T>& rhs) {
	matrix<T> temp(dim);
	temp.data = this.data - rhs.data;
	return temp;
}

template<class T>
matrix<T>& matrix<T>::operator*(const T& mul) {
	matrix<T> temp(dim);
	temp.data = this->data * mul;
	return temp;
}

template<class T>
vector<T>& matrix<T>::operator*(const vector<T>& rhs) {
	vector<T> res(dim);
	for (int i = 0; i < dim; i++) {
		vector<T> temp(dim);
		temp = this->data[i] * rhs[i];

		res[i] = temp.sum();
	}
	return res;
}

template<class T>
int matrix<T>::getDim() { return dim; }

template<class T>
T matrix<T>::getNorm1(){}

template<class T>
T matrix<T>::getNorm2() {
	vector<T> norm(dim);
	for (int i = 0; i < dim; i++) {
		norm[i] = data[i].absSum();
	}
	return norm.max();
}

template<class T>
T matrix<T>::getNorm3(){
	return transpose().getNorm2();
}

template<class T>
void matrix<T>::show() {
	for (int i = 0; i < dim; i++) {
		data[i].show();
	}
}

template<class T>
matrix<T> matrix<T>::transpose() {
	matrix<T> trans(dim);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			trans.data[i][j] = data[j][i];
		}
	}
	return trans;
}