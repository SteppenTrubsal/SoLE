#include <table.h>
using namespace std;

void tableClear(table& init) {
	init.num.clear();
	init.diffNorm.clear();
	init.eps = 0;
	init.roots.clear();
}