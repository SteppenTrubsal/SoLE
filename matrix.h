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

	void show();
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
matrix<T>::matrix(T** initArr, int dimensions) {

}

template<class T>
matrix<T>::~matrix() { dim = 0; }

template<class T>
void matrix<T>::show() {
	for (int i = 0; i < dim; i++) {
		data[i].show();
	}
}