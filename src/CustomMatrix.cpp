#include <CustomMatrix.h>

CustomMatrix::CustomMatrix() :data() {}
CustomMatrix::CustomMatrix(const CustomMatrix& m) :data(m.data) {}
CustomMatrix::CustomMatrix(vector<vector<double>> d) :data(d) {}
CustomMatrix::~CustomMatrix() {}
CustomMatrix::CustomMatrix(int d) :data(d, vector<double>(d, 0)) {


}

CustomMatrix& CustomMatrix::operator=(const CustomMatrix& m) {
    data = m.data;
    return *this;
}
CustomMatrix CustomMatrix::operator+(const CustomMatrix& m) {
    CustomMatrix res(data.size());
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < m.data.size(); j++) {
            res.data[i][j] = data[i][j] + m.data[i][j];
        }
    }
    return res;
}
CustomMatrix CustomMatrix::operator-(const CustomMatrix& m) {
    CustomMatrix res(data.size());
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < m.data[0].size(); j++) {
            res.data[i][j] = data[i][j] - m.data[i][j];
        }
    }
    return res;
}
CustomMatrix CustomMatrix::operator*(const double& d) {
    CustomMatrix res(data.size());
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[0].size(); j++) {
            res.data[i][j] = data[i][j] * d;
        }
    }
    return res;
}
CustomMatrix CustomMatrix::operator/(const double& d) {
    CustomMatrix res(data.size());
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[0].size(); j++) {
            res.data[i][j] = data[i][j] / d;
        }
    }
    return res;
}
vector<double> CustomMatrix::operator*(const vector<double> v) {
    vector<double> res(data.size());
    for (int i = 0; i < data.size(); i++) {
        res[i] = 0;
        for (int j = 0; j < data[0].size(); j++) {
            res[i] += data[i][j] * v[j];
        }
    }
    return res;
}
CustomMatrix CustomMatrix::operator*(const CustomMatrix& m) {
    CustomMatrix res(data.size());
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < m.data[0].size(); j++) {
            res.data[i][j] = 0;
            for (int k = 0; k < data[0].size(); k++) {
                res.data[i][j] += data[i][k] * m.data[k][j];
            }
        }
    }
    return res;
}

vector<double> CustomMatrix::getLambda() {
    return findEigenvalues(data);
}
double CustomMatrix::getNorm1() {
    vector<double> lam = (getTranspose() * (*this)).getLambda();
    double max = (lam[0] > 0) ? lam[0] : -lam[0];
    for (int i = 1; i < lam.size(); i++) {
        double temp = (lam[i] > 0) ? lam[i] : -lam[i];
        max = (temp > max) ? temp : max;
    }
    return sqrt(max);
}
double CustomMatrix::getNorm2() {
    vector<double> sum(data.size());
    int dim = data[0].size();
    for (int i = 0; i < dim; i++) {
        sum[i] = 0;
        for (int j = 0; j < dim; j++) {
            sum[i] += (data[i][j] > 0) ? data[i][j] : -data[i][j];
        }
    }
    double max = sum[0];
    for (int i = 1; i < dim; i++) {
        max = (max > sum[i]) ? max : sum[i];
    }
    return max;
}
double CustomMatrix::getNorm3() {
    return getTranspose().getNorm2();
}
double CustomMatrix::getConditionNumber(int param) {
    if (param == 1) { return ((*this).getReverse()).getNorm1() * (*this).getNorm1(); }
    if (param == 2) { return ((*this).getReverse()).getNorm2() * (*this).getNorm2(); }
    if (param == 3) { return ((*this).getReverse()).getNorm3() * (*this).getNorm3(); }
}
int CustomMatrix::getDim() {
    return data.size();
}

vector<CustomMatrix> CustomMatrix::getLUD() {
    vector<CustomMatrix> res(3, data.size());
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data.size(); j++) {
            if (j < i) {
                res[0].data[i][j] = data[i][j];
                res[1].data[i][j] = 0;
                res[2].data[i][j] = 0;
            }
            else if (j > i) {
                res[0].data[i][j] = 0;
                res[1].data[i][j] = data[i][j];
                res[2].data[i][j] = 0;
            }
            else if (j == i) {
                res[0].data[i][j] = 0;
                res[1].data[i][j] = 0;
                res[2].data[i][j] = data[i][j];
            }
        }
    }
    return res;
}
CustomMatrix CustomMatrix::getReverse() {
    int dim = data.size();
    CustomMatrix result(dim);
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            CustomMatrix temp(dim - 1);
            int counter = 0;
            for (int _i = 0; _i < dim; _i++) {
                for (int _j = 0; _j < dim; _j++) {
                    if (_i != i && _j != j) {
                        temp.data[int(counter / (dim - 1))][int(counter % (dim - 1))] = data[_i][_j];
                        counter++;
                    }
                }
            }
            result.data[i][j] = pow(double(-1), double(i + j)) * temp.getDet();
        }
    }
    result = result.getTranspose() / getDet();
    return result;
}
double CustomMatrix::getDet() {
    if (data.size() == 2) {
        return data[0][0] * data[1][1] - data[0][1] * data[1][0];
    }
    int d = data.size();
    double det = 0;
    for (int k = 0; k < d; k++) {
        CustomMatrix temp(d - 1);
        int counter = 0;
        for (int i = 0; i < d; i++) {
            for (int j = 0; j < d; j++) {
                if (i != 0 && j != k) {
                    temp.data[int(counter / (d - 1))][int(counter % (d - 1))] = data[i][j];
                    counter++;
                }
            }
        }
        det += data[0][k] * pow(double(-1), double(k)) * temp.getDet();
    }
    return det;
}
CustomMatrix CustomMatrix::getTranspose() {
    CustomMatrix res(data.size());
    for (int i = 0; i < data[0].size(); i++) {
        for (int j = 0; j < data.size(); j++) {
            res.data[i][j] = data[j][i];
        }
    }
    return res;
}

void CustomMatrix::EFill() {
    int d = data.size();
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            if (i == j) {
                data[i][j] = 1;
            }
        }
    }
}
double CustomMatrix::getTau() {
    double tau = 1;
    double temp = 2;
    CustomMatrix E(data.size());
    E.EFill();

    do {
        tau -= 0.001;
        temp = (E - (*this) * tau).getNorm1();
    } while (temp > 1);
    return tau;
}