int _b[] = { 17,5,21,0 };

int _A[4][4] = {
	{18,8,6,1},
	{4,13,8,1},
	{0,9,14,5},
	{6,4,4,12}
};

int** createA(int dim = 4) {
	int** A = new int* [dim];
	for (int i = 0; i < dim; i++) {
		A[i] = new int[dim];

		for (int j = 0; j < dim; j++) {
			A[i][j] = _A[i][j];
		}
	}

	return A;
}