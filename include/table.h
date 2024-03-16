#include <vector>
struct table
{
	std::vector<double> num;
	std::vector<double> diffNorm;
	double eps = 0;
	std::vector<double> roots;
	std::string methodName;
};