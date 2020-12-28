#include <bits/stdc++.h>
using i64 = int64_t;

constexpr int N = 2, P = 1e9 + 7;

void upd(int &x, int y) { x = x + y - P; x += x >> 31 & P; }

struct Matrix {
	int a[N][N], n, m;
	
	Matrix() { std::memset(a, 0, sizeof a); }
	
	Matrix(int R, int C) {
		n = R, m = C;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j) a[i][j] = 0;
	}
	
	Matrix operator*(const Matrix &o) const {
		assert(m == o.n);
		Matrix ans(n, o.m);
		for (int k = 0; k < m; ++k)
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < m; ++j)
					upd(ans.a[i][j], int64_t(a[i][k]) * o.a[k][j] % P);
		return ans;
	}
};

Matrix unit(int n) {
	Matrix ans(n, n);
	for (int i = 0; i < n; ++i) ans.a[i][i] = 1;
	return ans;
}

template <typename T>
Matrix matPower(Matrix A, T n) {
	assert(A.n == A.m);
	Matrix ans = unit(A.n);
	for (; n; n >>= 1, A = A * A)
		if (n & 1) ans = ans * A;
	return ans;
}

int main() {
	Matrix F(2, 1);
	F.a[0][0] = 1;
	F.a[1][0] = 0;
	Matrix A(2, 2);
	A.a[0][0] = 1, A.a[0][1] = 1;
	A.a[1][0] = 1, A.a[1][1] = 0;

	int tt;
	std::cin >> tt;
	while (tt--) {
		i64 n; 
		std::cin >> n;

		Matrix Fn = matPower(A, n * 2 - 1) * F;
		std::cout << (Fn.a[0][0] - n + P) % P << '\n';
	}
	return 0;
}