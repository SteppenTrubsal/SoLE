double _A[4][4] = {
	{18,8,6,1},
	{4,13,8,1},
	{0,9,14,5},
	{6,4,4,12}
};

double _b[] = { 17,5,21,0 };

double _x0[] = {1,1,1,1};

double** createA(int dim = 4) {
	double** A = new double* [dim];
	for (int i = 0; i < dim; i++) {
		A[i] = new double[dim];

		for (int j = 0; j < dim; j++) {
			A[i][j] = _A[i][j];
		}
	}

	return A;
}

double* createX0(int len = 4){
	double* x = new double[len];
    for (int i = 0; i < len; i++) {
        x[i] = _x0[i];
    }

    return x;
}

double* createB(int len = 4){
	double* b = new double[len];
    for (int i = 0; i < len; i++) {
        b[i] = _b[i];
    }

    return b;
}