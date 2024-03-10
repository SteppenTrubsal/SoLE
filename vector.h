#include <iostream>
using namespace std;

template <class T>
class vector {
	T* arr;
	int len;
public:
	vector();
	explicit vector(T*);
	explicit vector(int);
	~vector();

	T& operator[](int);
	vector<T>& operator=(const T&);
	vector<T>& operator=(const vector<T>&);

	void show();
	void expand(int addLen = 1);
};

template<class T>
vector<T>::vector(): arr(nullptr), len(0){}

template<class T>
vector<T>::vector(T* staticArr) : len(sizeof(staticArr) / sizeof(staticArr[0])), arr(new T[len]) {
	for (int i = 0; i < len; i++) {
		arr[i] = staticArr[i];
	}
}

template<class T>
vector<T>::vector(int lenght) : len(lenght), arr(new T[len]) {}

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