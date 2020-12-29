#include <bits/stdc++.h>
using i64 = int64_t;

constexpr int N = 15, P = 1e9 + 7;

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
					upd(ans.a[i][j], i64(a[i][k]) * o.a[k][j] % P);
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

int C[N][N];

int main() {
	C[0][0] = 1;
	for (int i = 1; i < N; ++i) {
		C[i][0] = 1;
		for (int j = 1; j <= i; ++j)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
	}
	i64 n;
	int k;
	std::cin >> n >> k;
	
	Matrix A(k + 2, k + 2), F(k + 2, 1);
	
	F.a[0][0] = 0;
	F.a[1][0] = 1;
	for (int i = 2; i < k + 2; ++i)
		F.a[i][0] = 0;
	
	A.a[0][0] = 2;
	for (int i = 1; i < k + 2; ++i)
		A.a[0][i] = C[k][i - 1];
	for (int i = 1; i < k + 2; ++i) {
		for (int j = 1; j - 1 <= i - 1; ++j)
			A.a[i][j] = C[i - 1][j - 1];
	}

	Matrix F1 = matPower(A, n - 1) * F;
	Matrix F2 = matPower(A, n) * F;
	std::cout << (F2.a[0][0] - F1.a[0][0] + P) % P << '\n';
	return 0;
}