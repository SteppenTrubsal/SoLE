#include "methods.h"
#include "src.h"
using namespace std;

int main() {
	matrix<int> test(createA(), 4);
	vector<int> b(_b);
	vector<int> x0(_x0);
	test.show();

	cout << fixedPointIter(test, b, x0, _tau, 0.01) << endl;
}