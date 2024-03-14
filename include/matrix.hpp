#include "someFunc.hpp"
#include <cmath>
using namespace std;

class matrix{
    vector<vector<double>> data;
public:
    matrix();
    matrix(const matrix&);
    matrix(vector<vector<double>>);
    ~matrix();

    matrix& operator=(const matrix&);
    matrix operator+(const matrix&);
    matrix operator-(const matrix&);
    matrix operator*(const double&);
    vector<double> operator*(const vector<double>);
    matrix operator*(const matrix&);

    vector<double> getLambda();
    double getNorm1();
    double getNorm2();
    double getNorm3();

    vector<matrix> getLUD();
    matrix getReverse();
    double getDet();
    matrix getTranspose();
};

matrix::matrix():data(){}
matrix::matrix(const matrix& m):data(m.data){}
matrix::matrix(vector<vector<double>> d):data(d){}
matrix::~matrix(){data.clear();}

matrix& matrix::operator=(const matrix& m){
    data = m.data;
    return *this;
}
matrix matrix::operator+(const matrix& m){
    matrix res;
    for(int i = 0; i < data.size(); i++){
        for(int j = 0; j < m.data[0].size(); j++){
            res.data[i][j] = data[i][j] + m.data[i][j];
        }
    }
    return res;
}
matrix matrix::operator-(const matrix& m){
    matrix res;
    for(int i = 0; i < data.size(); i++){
        for(int j = 0; j < m.data[0].size(); j++){
            res.data[i][j] = data[i][j] - m.data[i][j];
        }
    }
    return res;
}
matrix matrix::operator*(const double& d){
    matrix res;
    for(int i = 0; i < data.size(); i++){
        for(int j = 0; j < data[0].size(); j++){
            res.data[i][j] = data[i][j] * d;
        }
    }
    return res;
}
vector<double> matrix::operator*(const vector<double> v){
    vector<double> res;
    for(int i = 0; i < data.size(); i++){
        res.push_back(0);
        for(int j = 0; j < data[0].size(); j++){
            res[i] += data[i][j] * v[j];
        }
    }
    return res;
}
matrix matrix::operator*(const matrix& m){
    matrix res;
    for(int i = 0; i < data.size(); i++){
        for(int j = 0; j < m.data[0].size(); j++){
            res.data[i][j] = 0;
            for(int k = 0; k < data[0].size(); k++){
                res.data[i][j] += data[i][k] * m.data[k][j];
            }
        }
    }
    return res;
}

vector<double> matrix::getLambda(){
    return findEigenvalues(data);
}
double matrix::getNorm1(){
    vector<double> lam = getLambda();
    double max = (lam[0] > 0) ? lam[0] : -lam[0];
    for(int i = 1; i < lam.size(); i++){
        double temp = (lam[i] > 0)? lam[i] : -lam[i];
        max = (temp > max)? temp : max;
    }
    return sqrt(max);
}
double matrix::getNorm2(){
    vector<double> sum;
    int dim = data[0].size();
    for(int i = 0; i < dim; i++){
        sum[i] = 0;
        for(int j = 0; j < dim; j++){
            sum[i] += (data[i][j] > 0)? data[i][j] : -data[i][j];
        }
    }
    double max = sum[0];
    for(int i = 1; i < dim; i++){
        max = (max > sum[i])? max : sum[i];
    }
}
double matrix::getNorm3(){
    return getTranspose().getNorm2();
}

vector<matrix> matrix::getLUD(){
    vector<matrix> res;
    for(int i = 0; i < data.size(); i++){
        res.push_back(matrix());
        for(int j = 0; j < data.size(); j++){
            for(int k = 0; k < 3; k++){
                res[k].data.resize(data.size());
            }
            if(j < i){
                res[0].data[i].push_back(data[i][j]);
                res[1].data[i].push_back(0);
                res[2].data[i].push_back(0);
            }
            else if (j == i) {
                res[0].data[i].push_back(0);
                res[1].data[i].push_back(data[i][j]);
                res[2].data[i].push_back(0);
            }
            else if (j > i) {
                res[0].data[i].push_back(0);
                res[1].data[i].push_back(0);
                res[2].data[i].push_back(data[i][j]);
            }
        }
    }
    return res;
}
matrix matrix::getReverse(){
    matrix result;
    int dim = data.size();
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            matrix temp;
            int counter = 0;
            for(int _i = 0; _i < dim; _i++){
                for(int _j = 0; _j < dim; _j++){
                    if(_i!= i && _j!= j){
                        temp.data[int(counter/(dim-1))][int(counter%dim)] = data[_i][_j];
                        counter++;
                    }
                }
            }
            result.data[i][j] = power(-1,i+j)*temp.getDet();
        }
    }
    return result;
}
double matrix::getDet(){
    if(data.size() == 2){
        return data[0][0] * data[1][1] - data[0][1] * data[1][0];
    }
    int d = data.size();
    double det = 0;
    for(int k = 0; k < d; k++){
        matrix temp;
        int counter = 0;
        for(int i = 0; i < d; i++){
            for(int j = 0; j < d; j++){
                if(i!= k && j!= k){
                    temp.data[int(counter/(d-1))][int(counter%d)] = data[i][j];
                    counter++;
                }
            }
        }
        det+= data[0][k] * power(-1,k) * temp.getDet();
    }
    return det;
}
matrix matrix::getTranspose(){
    matrix res;
    for(int i = 0; i < data[0].size(); i++){
        for(int j = 0; j < data.size(); j++){
            res.data[i][j] = data[j][i];
        }
    }
    return res;
}