#include <bits/stdc++.h>
using i64 = int64_t;

constexpr int N = 110, LOG = 55;
constexpr i64 INF = 1e18;

struct Matrix {
	i64 a[N][N];
	int n, m;
	
	Matrix() { }
	
	Matrix(int R, int C) {
		n = R, m = C;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j) a[i][j] = INF;
	}
	
	Matrix operator*(const Matrix &o) const {
		assert(m == o.n);
		Matrix ans(n, o.m);
		for (int k = 0; k < m; ++k)
			for (int i = 0; i < ans.n; ++i)
				for (int j = 0; j < ans.m; ++j)
					ans.a[i][j] = std::min(ans.a[i][j], a[i][k] + o.a[k][j]);
		return ans;
	}
	
	void debug() {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j)
				std::cerr << a[i][j] << " ";
			std::cerr << '\n';
		}
	}
};

Matrix pw[LOG], F;
int n; i64 T;
bool chk(i64 d) {
	Matrix Fn = F;

	for (int i = 0; i < LOG; ++i)
		if (d >> i & 1) Fn = pw[i] * Fn;
	
	for (int i = 0; i < n; ++i)
		if (Fn.a[i][0] <= T) return true;
	return false;
}

int types[1010], rs[1010];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	std::cin >> n >> T;
	
	F = Matrix(n, 1);
	for (int i = 0; i < n; ++i)
		F.a[i][0] = 0;
	Matrix &G = pw[0];
	G = Matrix(n, n);
	for (int i = 0; i < n; ++i) {
		int k; i64 y;
		std::cin >> k >> y;
		
		for (int j = 0; j < k; ++j) {
			std::cin >> types[j];
		}
		for (int j = 0; j < k; ++j) {
			std::cin >> rs[j];
		}
		for (int j = 0; j < k; ++j) {
			int type = types[j]; i64 r = rs[j];
			--type;
			G.a[type][i] = std::min(G.a[type][i], y + r);
		}
	}

	for (int i = 1; i < LOG; ++i)
		pw[i] = pw[i - 1] * pw[i - 1];
	
	i64 lo = 0, hi = T, ans = 0;
	while (lo <= hi) {
		i64 mid = (lo + hi) >> 1;
		if (chk(mid)) ans = mid, lo = mid + 1;
		else hi = mid - 1;
	}
	std::cout << ans << '\n';
	return 0;
}