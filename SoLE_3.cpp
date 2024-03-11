#include "methods.hpp"
#include "src.hpp"
using namespace std;

int main() {
	cout << "1" << endl;
	matrix<int> test(createA(), 4);
	//vector<int> b(_b);
	//vector<int> x0(_x0);
	cout << "2" << endl;
	test.show();
	cout << "3" << endl;
	//cout << fixedPointIter(test, b, x0, _tau, 0.01) << endl;

	int gg = 3;
	matrix<int> test2 = test * gg;
	test2.show();
}