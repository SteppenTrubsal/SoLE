#include <cmath>
using namespace std;

double absolut(const double& x){
    double temp;
    temp = (x < 0? -x : x);
    return temp;
}

double getEucleadeanNorm(double* arr, int len = 4){
    double sum = 0;
    for(int i = 0; i < len; i++){
        sum += arr[i] * arr[i];
    }
    return sqrt(sum);
}