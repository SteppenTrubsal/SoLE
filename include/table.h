#include <vector>
#include <set>
struct table
{
	std::vector<double> num;
	std::vector<double> diffNorm;
	double eps = 0;
	std::vector<double> roots;
};