struct matrix
{
	vvd mat;
	int n, m;
	matrix(int _n, int _m) {
		n = _n, m = _m;
		mat = vvd(n, vd(m, 0.0));
	}
	double& operator()(int i, int j) {
		return mat[i][j];
	}
	void rref() {
		int i, j, k, t; 
		double p;
		for (i = 0; i < n; i++) {
			t = -1;
			while (++t < m && fabs(mat[i][t]) < EPS);
			if (t == m) continue;
			p = mat[i][t];
			for (j = t; j < m; j++) mat[i][j] = mat[i][j]/p;
			for (j = 0; j < n; j++) {
				if (i != j) {
					p = mat[j][t];
					for (k = t; k < m; k++)
						mat[j][k] = mat[j][k] - mat[i][k]*p;
				}
			}
		}
	}
};
// field tested: equationsolver, equationsolverplus, arcade, lostinthewood
