//methods.hpp
//include <table.h>
#include <CustomMatrix.h>
#include <someFunc.h>

using namespace std;

bool sufficientSimpleCheck(CustomMatrix A) {
    CustomMatrix E(A.getDim());
    E.EFill();
    if ((E - A * (A.getTau())).getNorm1() < 1) { return 1; }
    return 0;
}
bool convergenceSimpleCheck(CustomMatrix A) {
    CustomMatrix E(A.getDim());
    E.EFill();
    vector<double> lam = (E - A * (A.getTau())).getLambda();
    double max = 0;
    for (int i = 0; i < lam.size(); i++) {
        double temp = (lam[i] > 0) ? lam[i] : -lam[i];
        max = (temp > max) ? temp : max;
    }
    if (max < 1) { return 1; }
    return 0;
}
static void SimpleIterations(CustomMatrix A, vector<double> b, vector<double> x, double eps, table& debug) {
    int counter = 0;
    double tau = A.getTau();
    CustomMatrix E(x.size());
    E.EFill();
    CustomMatrix temp = E - A * tau;
    vector<double> x1(x.size());
    vector<double> diff;
    tableClear(debug);

    do {
        vector<double> xtemp = temp * x;
        for (int i = 0; i < b.size(); i++) {
            x1[i] = xtemp[i] + b[i] * tau;
        }
        diff.clear();
        for (int i = 0; i < x1.size(); i++) {
            diff.push_back(x[i] - x1[i]);
        }
        x.clear();
        x = x1;
        debug.diffNorm.push_back(getEucleadeanNorm(diff));
        
        counter++;
        debug.num.push_back(counter);
    } while (getEucleadeanNorm(diff) > eps);

    debug.eps = eps;
    debug.roots = x;
    debug.methodName = "SimpleIterations";
}

bool sufficientJacobiCheck(CustomMatrix A) {
    return A.diagonalPrevail();
}
bool convergenceJacobiCheck(CustomMatrix A) {
    vector<CustomMatrix> LUD = A.getLUD();
    vector<double> lamb = ((LUD[2].getReverse()
        * (LUD[0] + LUD[1])) * (-1)
        ).getLambda();
    for (int i = 0; i < lamb.size(); i++) {
        if (((lamb[i] > 0) ? lamb[i] : -lamb[i]) > 1) { return 0; }
    }
    return 1;
}
static void Jacobi(CustomMatrix A, vector<double> b,vector<double> x, double eps, table& debug){
    vector<CustomMatrix> LUD = A.getLUD();
    vector<double> diff;
    int counter = 0;
    tableClear(debug);
    do{
        vector<double> temp1((LUD[0]+LUD[1])*x);
        vector<double> temp2(x.size());
        for(int i = 0; i < x.size(); i++){
            temp2[i] = b[i] - temp1[i];
        }
        vector<double> x1 = LUD[2].getReverse() * temp2;
        diff.clear();
        for(int i = 0; i < x1.size(); i++){
            diff.push_back(x[i] - x1[i]);
        }
        x.clear();
        x= x1;
        debug.diffNorm.push_back(getEucleadeanNorm(diff));
        debug.num.push_back(counter);
        counter++;
    }while(getEucleadeanNorm(diff) > eps);
    
    debug.eps = eps;
    debug.roots = x;
    debug.methodName = "Jacobi";
}

bool sufficientGaussSeidelCheck(CustomMatrix A) {
    vector<double> lamb = A.getLambda();
    for (int i = 0; i < lamb.size(); i++) {
        if (lamb[i] < 0) { return 0; }
    }
    return A.simmetrical();
}
bool convergenceGaussSeidelCheck(CustomMatrix A) {
    vector<CustomMatrix> LUD = A.getLUD();
    vector<double> lamb = (((LUD[0] + LUD[2]).getReverse() * LUD[1]) * (-1)).getLambda();
    for (int i = 0; i < lamb.size(); i++) {
        if (((lamb[i] > 0) ? lamb[i] : -lamb[i]) > 1) { return 0; }
    }
    return 1;
}
static void GaussSeidel(CustomMatrix A, vector<double> b, vector<double> x, double eps, table& debug) {
    vector<CustomMatrix> LUD = A.getLUD();
    vector<double> diff;
    int counter = 0;

    CustomMatrix temp1 = (LUD[0] + LUD[2]).getReverse();
    CustomMatrix temp2 = temp1 * LUD[1];

    tableClear(debug);
    do {
        vector<double> temp3 = temp1 * b;
        vector<double> temp4 = temp2 * x;
        vector<double> x1(b.size());
        for (int i = 0; i < b.size(); i++) {
            x1[i] = temp3[i] - temp4[i];
        }
        diff.clear();
        for (int i = 0; i < x1.size(); i++) {
            diff.push_back(x[i] - x1[i]);
        }
        x.clear();
        x = x1;
        debug.diffNorm.push_back(getEucleadeanNorm(diff));
        debug.num.push_back(counter);
        counter++;
    }while (getEucleadeanNorm(diff) > eps);
   
    debug.eps = eps;
    debug.roots = x;
    debug.methodName = "GaussSeidel";
}