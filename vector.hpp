#include <iostream>
#include <cmath>
#include "someFunc.hpp"
using namespace std;

template <class T>
class vector {
	T* arr;
	int len;
public:
	vector();
	explicit vector(T*);
	explicit vector(int);
	vector(const vector<T>&);
	~vector();

	T& operator[](int);
	vector<T>& operator=(const T&);
	vector<T>& operator=(const vector<T>&);
	vector<T> operator-(const vector<T>&);
	vector<T> operator+(const vector<T>&);
	vector<T> operator*(const T&)const;
	//vector<T>& operator*(const matrix<T>&);

	int getLen();
	T getEucleadeanNorm();

	void show();
	void expand(int addLen = 1);
	T max();
	T absSum();
	T sum();
};

template<class T>
vector<T>::vector() : arr(nullptr), len(0) {}

template<class T>
vector<T>::vector(T* staticArr) : len(sizeof(staticArr) / sizeof(staticArr[0])), arr(new T[len]) {
	for (int i = 0; i < len; i++) {
		arr[i] = staticArr[i];
	}
}

template<class T>
vector<T>::vector(int lenght) : len(lenght), arr(new T[len]) {}

template<class T>
vector<T>::vector(const vector<T>& old) : len(old.len), arr(new T[len]) {
	for (int i = 0; i < len; i++) {
		this->arr[i] = old.arr[i];
	}
}

template<class T>
vector<T>::~vector() { delete[] arr; len = 0; }

template<class T>
vector<T>& vector<T>::operator=(const T& rhs) {
	for (int i = 0; i < len; i++) {
		arr[i] = rhs;
	}
	return *this;
}

template<class T>
vector<T>& vector<T>::operator=(const vector<T>& rhs) {
	if (this == &rhs) {
		return *this;
	}

	delete[] arr;
	len = rhs.len;
	arr = new T[len];
	for (int i = 0; i < len; i++) {
		arr[i] = rhs.arr[i];
	}
	return *this;
}

template<class T>
T& vector<T>::operator[](int idx) {
	while (idx >= len) {
		this->expand();
	}
	return arr[idx];
}

template<class T>
vector<T> vector<T>::operator-(const vector<T>& rhs) {
	vector<T> temp(len);
	for (int i = 0; i < len; i++) {
		temp.arr[i] = this->arr[i] - rhs.arr[i];
	}
	return temp;
}

template<class T>
vector<T> vector<T>::operator+(const vector<T>& rhs) {
	vector<T> temp(len);
	for (int i = 0; i < len; i++) {
		temp.arr[i] = this->arr[i] + rhs.arr[i];
	}
	return temp;
}

template<class T>
vector<T> vector<T>::operator*(const T& mul)const {
	vector<T> temp(len);
	for (int i = 0; i < len; i++) {
		temp.arr[i] = this->arr[i] * mul;
	}
	return temp;
}

template<class T>
int vector<T>::getLen() { return len; }

template<class T>
T vector<T>::getEucleadeanNorm() {
	T quadroSum = 0;
	for (int i = 0; i < len; i++) {
		quadroSum += arr[i] * arr[i];
	}
	return sqrt(quadroSum);
}

template<class T>
void vector<T>::expand(int addLen) {
	T* tArr = new T[len + addLen];
	for (int i = 0; i < len; i++) {
		tArr[i] = arr[i];
	}
	delete[] arr;
	arr = tArr;
	len += addLen;
}

template<class T>
void vector<T>::show() {
	for (int i = 0; i < len; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

template<class T>
T vector<T>::max() {
	T max = 0;
	for (int i = 0; i < len; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	return max;
}

template<class T>
T vector<T>::absSum() {
	T sum = 0;
	for (int i = 0; i < len; i++) {
		sum += abs(arr[i]);
	}
	return sum;
}

template<class T>
T vector<T>::sum() {
	T sum = 0;
	for (int i = 0; i < len; i++) {
		sum += arr[i];
	}
	return sum;
}